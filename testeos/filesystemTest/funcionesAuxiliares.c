#include "filesystem.h"
#include <protocolo/protocolo.h>

/*------------------------FUNCIONES AUXILIARES---------------------------*/
void leerArchivoDeConfiguracion() {	// El archivo config de FS tiene PUERTO_LISTEN Y LISTA_NODOS

	// Interaccion por consola para ingresar la ruta del archivo.config
	char nombreArchivoConfigFS[LONGITUD_STRINGS];
	printf("Ingrese la ruta del archivo de configuracion del fileSystem: ");
	fflush(stdin);
	scanf("%s", nombreArchivoConfigFS);
	// Fin de interaccion con el usuario

	t_config* archivoConfig = config_create(nombreArchivoConfigFS);

	vg_puerto_listen = config_get_int_value(archivoConfig, "PUERTO_LISTEN");
	vg_lista_nodos = config_get_array_value(archivoConfig, "LISTA_NODOS");

	config_destroy(archivoConfig);
}

element* buscarElementoPorNombre(char* nombre) {
	int i;
	int elementosEnLista = FILESYSTEM->listaElementos->elements_count;
	element * elementoBuscado;
	element * elementoi;

	for (i = 0; i <= elementosEnLista; i++) {
		elementoi = list_get(FILESYSTEM->listaElementos, i);
		if (string_equals_ignore_case(elementoi->nombre, nombre)) {
			elementoBuscado = elementoi;
		}
	}

	return (i <= elementosEnLista) ? elementoBuscado : NULL;
}

void crearYAgregarBloquesALista(t_list *listaBloques, int cantidadBloquesACrear) {
	int i;
	for (i = 0; i <= cantidadBloquesACrear; i++) {
		bloq* bloque;
		bloque = crearBloque();
		list_add(listaBloques, bloque);
	}
}

void leerRegistro(int arch) {
	read(arch, FILESYSTEM, sizeof(fs)); //lee el archivo y pone la estructura en la estructura fs
}

void guardarRegistro(int arch) { //esto mientras este el archivo abierto sino lo abrimos aca

	write(arch, FILESYSTEM, sizeof(fs)); //le paso el registro fileSystem,y el archivo y lo escribe
}

//void empaquetarYMandarPorSocket(char* bloqueListo,
//		ubicacionDelBloqueEnNodo* unNodoBloque) {
//
//		t_escrituraBloque* envio_bloque;
//
//		void * mensajeBloqueParaNodo;
//
//		envio_bloque->bloqueListo = bloqueListo;
//		envio_bloque->unNodoBloque.numeroCopia = unNodoBloque->numeroCopia;
//		envio_bloque->unNodoBloque.numeroDeBloqueDelNodo = unNodoBloque->numeroDeBloqueDelNodo;
//		envio_bloque->unNodoBloque.numeroNodo = unNodoBloque->numeroNodo;
//
//		(void*)envio_bloque;
//
//		//La variable mensajeBloqueParaNodo ya está lista para mandarse por socket
////		mensajeBloqueParaNodo = prepararParaEnviar(ESCRITURA_BLOQUE,envio_bloque);
//}

int devuelveCantBloquesLista(void*lista, int elementosEnLista) {
	int cantBloques = 0;
	nod* nodoi;
	int i;
	for (i = 0; i <= elementosEnLista; i++) {
		nodoi = list_get(FILESYSTEM->listaNodosConectados, i);
		cantBloques += nodoi->listaBloques->elements_count;
	}
	return cantBloques;
}

int devuelveMenorNodoConBloques() {
	int cantMenorBloques = 60000; // se le puso porque estoy buscando un valor minimo.
	int elementosEnLista = FILESYSTEM->listaNodosConectados->elements_count;
	int i;
	nod* nodoi;
	for (i = 0; i <= elementosEnLista; i++) {
		nodoi = list_get(FILESYSTEM->listaNodosConectados, i);
		if (nodoi->listaBloques->elements_count < cantMenorBloques)
			cantMenorBloques = nodoi->listaBloques->elements_count;
	}
	return cantMenorBloques;
}
// Desde aca

bool puedoHacerCopias(int cantBloquesOriginales) {
	//algoritmo jBON OPTIMO evita duplicados en nodos y solo se hace la operacion si se puede hacer

	int cantMenorBloques = 0;
	nod* nodoi;
	int elementosEnLista = FILESYSTEM->listaNodosConectados->elements_count;
	int i, promedio;
	int cantNodosSuperaBloques = 0;

///-----------------son iguales a 3 nodos--------------
	if (FILESYSTEM->listaNodosConectados->elements_count == 3) {
		cantMenorBloques = devuelveMenorNodoConBloques();
		if (cantMenorBloques > cantBloquesOriginales)
			return true;
		else
			return false;
		//-------- son mayor a 3 nodos conectados
	} else {
		for (i = 0; i <= elementosEnLista; i++) {
			nodoi = list_get(FILESYSTEM->listaNodosConectados, i);
			if (nodoi->listaBloques->elements_count > cantBloquesOriginales)
				cantNodosSuperaBloques++; //son los nodos cuyos bloques son mayores a la cantidad de bloques totales
		}
		cantMenorBloques = devuelveMenorNodoConBloques(); //devuelve el total de bloques del menor nodo

		if (cantNodosSuperaBloques >= 3)
			return true;
		else {
			promedio = (cantBloquesOriginales * 3)
					% FILESYSTEM->listaNodosConectados->elements_count;
			if (cantMenorBloques >= promedio)
				return true;
			else
				return false;
		}
	}
}

bloq* buscaBloqueDisponible(nod* unNodo) {
	bloq* primerBloqueDisponible;

	bool condicion(bloq* unBloque) {
		return (unBloque->estaOcupado != ESTA_OCUPADO);
	}

	primerBloqueDisponible = list_find(unNodo->listaBloques, (void*) condicion);
	primerBloqueDisponible->estaOcupado = ESTA_OCUPADO;	// Obligo a que el bloque pase a estar ocupado

	return primerBloqueDisponible;
}

void distribucionInicial(char* bloqueListo, element* unElemento) {
	ubicacionDelBloqueEnNodo* unNodoBloque = malloc(
			sizeof(ubicacionDelBloqueEnNodo));
	unNodoBloque = NULL;
	nod* primerNodo = NULL;

	int cantidadCopias;
	for (cantidadCopias = COPIAS_BLOQUE; cantidadCopias >= 0;
			cantidadCopias--) {
		primerNodo = list_remove(FILESYSTEM->listaNodosConectados, 0); // Descolo el primer nodo de la listaNodosConectados
		// Seteo unNodoBloque
		unNodoBloque->numeroCopia = cantidadCopias;
		unNodoBloque->numeroNodo = primerNodo->numero;
		unNodoBloque->numeroDeBloqueDelNodo =
				(buscaBloqueDisponible(primerNodo))->numero;
		// Fin seteo unNodoBloque

		list_add(FILESYSTEM->listaNodosConectados, primerNodo); // Encolo el primer nodo de la lista

		list_add(unElemento->dobleListaUbicacionDelBloqueEnNodo, unNodoBloque);	// Actualizo la estructura

	//	empaquetarYMandarPorSocket(bloqueListo, unNodoBloque);
	}
	free(unNodoBloque);
}

void copiaDistribuyeYEmpaqueta(char* bloqueListo, int cantBloques,
		element* elemento) {
	if (puedoHacerCopias(cantBloques)) {// Esta hace la simulacion para ver si
		// se pueden hacer las copias del archivo
		distribucionInicial(bloqueListo, elemento);
	} else {
		perror("[ERROR] no se puede copiar el archivo al MDFS");
		exit(-1);
	}
}

int devuelveCantidadElementosArreglo(char** arregloPtrContenidoBloque) {
	int contadorBloques = 0;
	while (arregloPtrContenidoBloque[contadorBloques] != NULL) {
		contadorBloques++;
	}
	return contadorBloques;
}

void divideBloques(char** ptrArregloConOracionesParaBloque, element* unElemento) {
	char* bloqueFinal = malloc(sizeof(char*));
	char* bloqueTemporal = string_new();
	int posicionOracion = 0;
	int posicionesParaBloque[308]; //tomado del maximo de bloques que puede haber para un archivo de 6Gb
	int cantBloque = 0;
	int i, j;
	int tamanioTemporal;
	j = 0;
	while (ptrArregloConOracionesParaBloque[posicionOracion] != NULL) { // lo hacemos porque queremos saber
		//la cantidad de bloques que se deben planificar  para luego mandarselos a la funcion que verifica si se puede hacer la copia
		tamanioTemporal =
				sizeof(ptrArregloConOracionesParaBloque[posicionOracion]);
		if (tamanioTemporal != VEINTEMEGAS) {

			while ((tamanioTemporal
					+ sizeof(ptrArregloConOracionesParaBloque[posicionOracion
							+ 1])) < VEINTEMEGAS) {
				posicionOracion++;
				tamanioTemporal +=
						sizeof(ptrArregloConOracionesParaBloque[posicionOracion]);

			}
			tamanioTemporal = 0;
			posicionesParaBloque[cantBloque] = posicionOracion;
			cantBloque++;
		}
		for (i = 0; i < cantBloque; i++) {//para que arme todos los bloques , ya tenemos las posiciones de las oraciones
			bloqueFinal = string_repeat('0', VEINTEMEGAS);

			strcpy(bloqueTemporal, ptrArregloConOracionesParaBloque[j]);
			j++;
			for (; j <= posicionesParaBloque[i]; j++)		//armar un bloque
					{
				strcat(bloqueTemporal, ptrArregloConOracionesParaBloque[j]);
			}
			strcpy(bloqueFinal, bloqueTemporal);
			copiaDistribuyeYEmpaqueta(bloqueFinal, cantBloque, unElemento);
		}
	}
	free(bloqueFinal);
}

ubicacionDelBloqueEnNodo* devuelveBloque(char* nombreArchivo, int numeroBloque) {
	element* ptrArchivo;
	ubicacionDelBloqueEnNodo* ptrNodoBloque = NULL;
	bool compNumeroBloque(ubicacionDelBloqueEnNodo* unaUbicacion) {
return (unaUbicacion->numeroDeBloqueDelNodo == numeroBloque);
	}
	ptrArchivo = buscarElementoPorNombre(nombreArchivo);
	if (ptrArchivo == NULL) {
		perror("[ERROR]mostrarBloque: no se encuentra el archivo");
		exit(-1);
	}
	ptrNodoBloque = list_find(ptrArchivo->dobleListaUbicacionDelBloqueEnNodo,
			(void*) compNumeroBloque);
	if (ptrNodoBloque == NULL) {
		perror("[ERROR]mostrarBloque: no se encuentra el bloque");
		exit(-1);
	}
	return ptrNodoBloque;
}

char* sacarUltimaParte(char* dirArchivoLocal) {
	char* nombreArchivo;
	nombreArchivo = strdup(strrchr(dirArchivoLocal, '/'));
	sscanf(nombreArchivo, "/%s", nombreArchivo); // Le borro el primer char
	return nombreArchivo;
}
