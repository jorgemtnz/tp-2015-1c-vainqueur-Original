#include "filesystem.h"

/*------------------------FUNCIONES AUXILIARES---------------------------*/
void leerArchivoDeConfiguracion()
{	// El archivo config de FS tiene PUERTO_LISTEN Y LISTA_NODOS

	// Interaccion por consola para ingresar la ruta del archivo.config
	char nombreArchivoConfigFS[LONGITUD_STRINGS];
	printf("Ingrese la ruta del archivo de configuracion del fileSystem: ");
	fflush(stdin);
	scanf("%s", nombreArchivoConfigFS);
	// Fin de interaccion con el usuario

	t_config* archivoConfig = config_create(nombreArchivoConfigFS);

	vg_puerto_listen = config_get_int_value(archivoConfig, "PUERTO_LISTEN");
	vg_lista_nodos   = config_get_array_value(archivoConfig, "LISTA_NODOS");

	config_destroy(archivoConfig);
}

void inicializarMatriz()
{
	int incrementadorFilas;
	int incrementadorColumnas;

	for (incrementadorFilas = 0; incrementadorFilas < CANT_FILAS;
			incrementadorFilas++)
	{
		for (incrementadorColumnas = 0; incrementadorColumnas < CANT_COLUMNAS;
				incrementadorColumnas++)
		{
			vg_matrizUbicacion[incrementadorFilas][incrementadorColumnas] =	NULL;
		}

	}
}

element* buscarElementoPorNombre(char* nombre)
{
	int i;
	int elementosEnLista = FILESYSTEM->listaElementos->elements_count;
	element * elementoBuscado;
	element * elementoi;

	for (i = 0; i <= elementosEnLista; i++)
	{
		elementoi = list_get(FILESYSTEM->listaElementos, i);
		if (string_equals_ignore_case(elementoi->nombre, nombre))
		{
			elementoBuscado = elementoi;
		}
	}

	return (i <= elementosEnLista)? elementoBuscado: NULL;
}

void crearYAgregarBloquesALista(t_list *listaBloques, int cantidadBloquesACrear)
{
	int i;
	for(i=0; i <= cantidadBloquesACrear; i++)
	{
		bloq* bloque;
		bloque = crearBloque();
		list_add(listaBloques, bloque);
	}
}

void leerRegistro(int arch)
{
	read(arch, FILESYSTEM, sizeof(fs)); //lee el archivo y pone la estructura en la estructura fs
}

void guardarRegistro(int arch)
{ //esto mientras este el archivo abierto sino lo abrimos aca

	write(arch, FILESYSTEM, sizeof(fs)); //le paso el registro fileSystem,y el archivo y lo escribe
}


void distribuyeBloque(t_list* listaNodosConectados, char* bloqueListo,)
{
	int cantidadCopias;
	for (cantidadCopias = 3; cantidadCopias >= 0; cantidadCopias--)
	{
		empaquetarYMandarPorSocket(bloqueListo, listaNodosConectados->head);
		void * aux = listaNodosConectados->head;

		list_remove(listaNodosConectados, 0); //Descolo el primer nodo de la lista
		list_add(listaNodosConectados, aux); //Encolo el primer nodo de la lista
	}
	actualizaEstructura();

}

void empaquetarYMandarPorSocket(char* bloqueListo)
{

}

int devuelveCantBloquesLista(void*lista, int elementosEnLista)
{
	int cantBloques = 0;
	nod* nodoi;
	int i;
	for (i = 0; i <= elementosEnLista; i++)
	{
		nodoi = list_get(FILESYSTEM->listaNodosConectados, i);
		cantBloques += nodoi->listaBloques->elements_count;
	}
	return cantBloques;
}
bool puedoHacerCopias()
{ //algoritmo jBON OPTIMO evita duplicados en nodos y solo se hace la operacion si se puede hacer

	int cantMenorBloques = 60000;
	int cantBloquesTot = 0; //bloques originales a alojar
	nod* nodoi;
	int elementosEnLista = FILESYSTEM->listaNodosConectados->elements_count;
	int i, promedio;
	int contMenorBloques = 0;
	cantBloquesTot = devuelveCantBloquesLista(FILESYSTEM->listaNodosConectados,
			elementosEnLista); //sin copias
///-----------------son iguales a 3 nodos--------------
	if (FILESYSTEM->listaNodosConectados->elements_count == 3)
	{
		for (i = 0; i <= elementosEnLista; i++)
		{
			nodoi = list_get(FILESYSTEM->listaNodosConectados, i);
			if (nodoi->listaBloques->elements_count < cantMenorBloques)
				cantMenorBloques = nodoi->listaBloques->elements_count;

		}
		if (cantMenorBloques > cantBloquesTot)
			return true;
		else
			return false;
		//-------- son mayor a 3 nodos conectados
	}
	else
	{
		for (i = 0; i <= elementosEnLista; i++)
		{
			nodoi = list_get(FILESYSTEM->listaNodosConectados, i);
			if (nodoi->listaBloques->elements_count < cantMenorBloques)
				cantMenorBloques = nodoi->listaBloques->elements_count;

			if (nodoi->listaBloques->elements_count > cantBloquesTot)
				contMenorBloques++;
		}
		if (contMenorBloques >= 3)
			return true;
		else
		{
			promedio = cantBloquesTot
					% FILESYSTEM->listaNodosConectados->elements_count;
			if (cantMenorBloques >= promedio)
				return true;
			else
				return false;
		}
	}
}

void actualizaEstructura()
{

}

void copiaDistribuyeYEmpaqueta(char* bloqueListo)
{

	if (puedoHacerCopias())
	{ // hay que pasar bien los parametros
		distribuyeBloque(bloqueListo);
	}
	else
	{
		perror("[ERROR] no se puede copiar el archivo al MDFS");
		exit(-1); // abria que ver si conviene que solo lo diga y no hacer el exit(-1)
	}
}
int devuelveCantidadElementosArreglo(char** arregloPtrContenidoBloque)
{
	int contadorBloques = 0;
	while (arregloPtrContenidoBloque[contadorBloques] != NULL)
	{
		contadorBloques++;
	}
	return contadorBloques;
}

void divideBloques(char** ptrArregloConOracionesParaBloque)
{
	char* bloqueFinal;
	char* bloqueTemporal = '\0';
	int contadorBloques = 0;

	bloqueFinal = string_repeat('0', VEINTEMEGAS);

	while (ptrArregloConOracionesParaBloque[contadorBloques] != NULL)
	{

		while ((sizeof(bloqueTemporal)
				+ sizeof(ptrArregloConOracionesParaBloque[contadorBloques + 1]))
				< VEINTEMEGAS)
		{
			contadorBloques++;
			strcat(bloqueTemporal,
					ptrArregloConOracionesParaBloque[contadorBloques]);

		}
		strcpy(bloqueFinal, bloqueTemporal);
		copiaDistribuyeYEmpaqueta(bloqueFinal); // en esta se debe planificar a que nodo se hace el envio.

	}
}

ubicacionDelBloqueEnNodo* devuelveBloque(char* nombreArchivo, int* numeroBloque)
{
	element* ptrArchivo;
	ubicacionDelBloqueEnNodo* ptrNodoBloque;

	ptrArchivo = buscarElementoPorNombre(nombreArchivo);
	if (ptrArchivo == NULL)
	{
		perror("[ERROR]mostrarBloque: no se encuentra el archivo");
		exit(-1);
	}
	ptrNodoBloque = list_find(ptrArchivo->matrizUbicacionDelBloqueEnNodo,
			(void*) compNumeroBloque);
	if (ptrNodoBloque == NULL)
	{
		perror("[ERROR]mostrarBloque: no se encuentra el bloque");
		exit(-1);
	}
	return ptrNodoBloque;
}
