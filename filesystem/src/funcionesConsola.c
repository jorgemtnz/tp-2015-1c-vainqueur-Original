#include "filesystem.h"

/*------------------- CONSOLA------------------------*/

// s	formatearMDFS                prueba minima
// s    eliminarArchiv
// s 	renombrarArchivo
// s	moverArchivo
// s	crearDirectorio               prueba minima
// s    eliminarDirectorio
// s    renombrarDirectorio
// s	moverDirectorio
// s	copiarArchivoLocalAlMDFS      prueba minima
// n	copiarArchivoDelMDFSAlFSLocal , esta no se encuentra en las condiciones mínimas
// n	solicitarMD5deUnArchivoenMDFS   prueba minima
// s	verUbicacionBloque              prueba minima
// s    verBloque                       prueba minima solo pendiente tema socket
// s	borrarBloque
// s	copiarBloque                    prueba minima
// s	agregarNodo  			        prueba minima    // No debe recibir argumentos // Falta sockets
// s	eliminarNodo                    prueba minima
// s	mostrarComandos
// s 	mostrarElementos 		// Yapa
void renombrarElemento(element* ptrElemento, char* nuevoNombreElemento) {
	strcpy(ptrElemento->nombre, nuevoNombreElemento);
}
void moverElemento(element* elementoOrigen, element* directorioDestino) { // Valido que no se quiera mover dentro de un archivo
	if (directorioDestino->tipoElemento == ESDIRECTORIO) { // Hago el cambio de directorio padre con el index del directorio padre
		elementoOrigen->directorioPadre = directorioDestino->index;
	} else {
		perror(
				"[ERROR]no se puede mover. El directorio destino no es un tipo directorio");
		exit(-1);
	}
}
void eliminarElemento(char* nombreElemento) {
	int i;
	int elementosEnLista = FILESYSTEM->listaElementos->elements_count;
	int sonIguales;

	for (i = 0; i <= elementosEnLista; i++) {
		element* elementoi;
		elementoi = list_get(FILESYSTEM->listaElementos, i);
		sonIguales = string_equals_ignore_case(elementoi->nombre,
				nombreElemento);
// Si las cadenas son iguales => encontro string => lo elimino

		if (sonIguales) {
			list_remove(FILESYSTEM->listaElementos, i);
		}

		// Si las cadenas son distintas => Sigue el for
	}
} // Sirve para archivos y directorios

void formatearMDFS() {
	liberaMemoriaFS();
	inicializarFilesystem();
}

void eliminarArchivo() {
	char nombreArchivo[LONGITUD_STRINGS];
	printf("Ingrese el nombre del archivo que desea eliminar: ");
	fflush(stdin);
	scanf("%s", nombreArchivo);
	eliminarElemento(nombreArchivo);
}

void renombrarArchivo() {
	char nombreArchivo[LONGITUD_STRINGS], nuevoNombreArchivo[LONGITUD_STRINGS];
	element* ptrArchivo;

	printf("Ingrese nombre de archivo a renombrar");
	fflush(stdin);
	scanf("%s", nombreArchivo);

	printf("Ingrese nuevo nombre para el archivo");
	fflush(stdin);
	scanf("%s", nuevoNombreArchivo);

	ptrArchivo = buscarElementoPorNombre(nombreArchivo);
	if (ptrArchivo == NULL) {
		perror("[ERROR] No existe el archivo");
		exit(-1);
	}
	renombrarElemento(ptrArchivo, nuevoNombreArchivo);
}

void moverArchivo() {
	char nombreArchivo[LONGITUD_STRINGS];
	char nombreDirectorioDestino[LONGITUD_STRINGS];
	element* ptrArchivo;
	element* directorioDestino;

	printf("Ingrese nombre de archivo que desea mover:");
	fflush(stdin);
	scanf("%s", nombreArchivo);

	printf("Ingrese el nombre del directorio destino");
	fflush(stdin);
	scanf("%s", nombreDirectorioDestino);

	directorioDestino = buscarElementoPorNombre(nombreDirectorioDestino);
	ptrArchivo = buscarElementoPorNombre(nombreArchivo);
	if ((directorioDestino == NULL) || (ptrArchivo == NULL)) {
		perror("[ERROR] No se puede mover el archivo");
		exit(-1);
	} else {
		moverElemento(ptrArchivo, directorioDestino);
	}
}

void crearDirectorio() {
	element* carpetaNueva;
	element* padre;
	int indexPadre;
	char dirPadre[LONGITUD_STRINGS];
	char nombre[LONGITUD_STRINGS];
	char* nombrePadre;

	carpetaNueva = crearElemento();

	printf("Ingrese el nombre de la carpeta a crear: ");
	fflush(stdin);
	scanf("%s", nombre);

	printf("Ingrese la ruta donde desea crear [ %s ]: ", nombre);
	scanf("%s", dirPadre);

	nombrePadre = strdup(sacarUltimaParte(dirPadre));
	padre = buscarElementoPorNombre(nombrePadre);

	if (padre == NULL) {
		perror("Numero invalido de directorio padre\n");
		exit(-1);
	}
	indexPadre = padre->index;

	// Seteo la carpeta creada
	carpetaNueva->nombre = strdup(nombre);
	carpetaNueva->estado = DISPONIBLE;
	carpetaNueva->tipoElemento = ESDIRECTORIO;
	if (!list_is_empty(FILESYSTEM->listaElementos)) {
		carpetaNueva->index = FILESYSTEM->listaElementos->elements_count += 1;
	} else { // Primera vez
		carpetaNueva->index = 1;
	}
	carpetaNueva->directorioPadre = indexPadre;
	carpetaNueva->tamanio = TAMANIO_DIRECTORIO;
	// Fin: carpetaNueva seteada

	list_add(FILESYSTEM->listaElementos, carpetaNueva);
}

void eliminarDirectorio() {
	char nombreDirectorio[LONGITUD_STRINGS];

	printf("Ingrese el nombre del Directorio: ");
	fflush(stdin);
	scanf("%s", nombreDirectorio);
	eliminarElemento(nombreDirectorio);
}

void renombrarDirectorio() {
	element* ptrDirectorio;
	char nombreDirectorio[LONGITUD_STRINGS],
			nuevoNombreDirectorio[LONGITUD_STRINGS];

	printf("Ingrese nombre de directorio a renombrar");
	fflush(stdin);
	scanf("%s", nombreDirectorio);

	printf("Ingrese nuevo nombre para el directorio");
	fflush(stdin);
	scanf("%s", nuevoNombreDirectorio);

	ptrDirectorio = buscarElementoPorNombre(nombreDirectorio);
	if (ptrDirectorio == NULL) {
		perror("[ERROR] No existe el directorio");
		exit(-1);
	}
	renombrarElemento(ptrDirectorio, nuevoNombreDirectorio);
}

void moverDirectorio() {
	char nombreDirectorioOrigen[LONGITUD_STRINGS];
	char nombreDirectorioDestino[LONGITUD_STRINGS];
	element* directorioOrigen;
	element* directorioDestino;

	printf("Ingrese nombre de Directorio Origen");
	fflush(stdin);
	scanf("%s", nombreDirectorioOrigen);

	printf("Ingrese el nombre del directorio destino");
	fflush(stdin);
	scanf("%s", nombreDirectorioDestino);

	directorioDestino = buscarElementoPorNombre(nombreDirectorioDestino);
	directorioOrigen = buscarElementoPorNombre(nombreDirectorioOrigen);

	if ((directorioDestino == NULL) || (directorioOrigen == NULL)) {
		perror("[ERROR] No se puede mover el directorio");
		exit(EXIT_FAILURE);
	}

	moverElemento(directorioOrigen, directorioDestino);
}

void copiarArchivoLocalAlMDFS() {
	// La copia la crea en la raiz
	char dirArchivoLocal[LONGITUD_STRINGS];
	char* nombreArchivo;
	char* dirArchivo;
	element* archivoEntrante = malloc(sizeof(element));
	// Variables que odia Lucas
	char** buffer = NULL;
	char* ptrComienzoMemoriaMapeada = NULL;
	int* ptrTamanioDePagina = NULL;
	char** ptrAMemoriaModificado = NULL; //pendiente modificar nombre, es la que modifica la direccion del ptrAMemoria
	// Fin de variables que odia Lucas

	ptrAMemoriaModificado = &ptrComienzoMemoriaMapeada;
	//se usa para poder hacer el paso por referencia y modificar a lo que apunta ptrComienzoMemoriaMapeada.

	printf("Ingrese la ruta del nombre del archivo a copiar al MDFS \n");
	fflush(stdin);
	scanf("%s", dirArchivoLocal);

	nombreArchivo = sacarUltimaParte(dirArchivoLocal);
	dirArchivo = strdup(dirArchivoLocal);// ya probado, es simil a usar malloc y luego strcpy. Excelente aporte

	mapeoAmemoria(dirArchivo, ptrAMemoriaModificado, ptrTamanioDePagina);
	buffer = string_split(ptrComienzoMemoriaMapeada, "\n");
	desMapea(*ptrTamanioDePagina, ptrComienzoMemoriaMapeada);
	archivoEntrante = crearElemento();
	// Lo alojamos en la raiz, index de la raiz = 0. Cualquier cosa lo movemos desde consola
	// Seteo archivoEntrante
	archivoEntrante->directorioPadre = 0;
	archivoEntrante->nombre = strdup(nombreArchivo);
	archivoEntrante->estado = DISPONIBLE;
	archivoEntrante->tipoElemento = ESARCHIVO;
	archivoEntrante->tamanio = *ptrTamanioDePagina;

	divideBloques(&buffer[0], archivoEntrante);
	free(archivoEntrante);
	free(dirArchivo);
}

void copiarArchivoDelMDFSAlFSLocal() {
	// Falta iplementar,  esta implicitamente en las condiciones mínimas
	char nombreArchivo[LONGITUD_STRINGS];
	element* archivoMDFS;
	t_list* listaNodoBloque; // ya filtrada.
	int i, numeroCopia = 0;
	ubicacionDelBloqueEnNodo* nodoBLoque = NULL;
	FILE* archivoLocal; // este es el archivo que se debe crear en el Local

	bool condicion(ubicacionDelBloqueEnNodo* unaUbic) { //esta es una inner function, declarada dentro de una funcion.
		return (numeroCopia == unaUbic->numeroCopia); //quiero filtrar la lista por el numeroCopia
	}

	printf(
			"Ingrese el nombre del archivo que quiere copiar del MDFS al FSlocal");
	scanf("%s", nombreArchivo);

	archivoMDFS = buscarElementoPorNombre(nombreArchivo);
	if (archivoMDFS->estado == ESTA_DISPONIBLE) {

		//tendria que tener toda la lista, puede ser un bloque de copia 0 , otro bloque de copia1, etc
		//listaBloquesArchivo= buscaListaArchivo(ptrArchivo);
		listaNodoBloque = list_filter(
				archivoMDFS->dobleListaUbicacionDelBloqueEnNodo,
				(void*) condicion);
		//enviamos las solicitudes de bloques

		for (i = 0; i < listaNodoBloque->elements_count;) {
			nodoBLoque = list_get(listaNodoBloque, i);
			//	solicitarBloque(nodoBLoque); //aca podria usar la que muestra el bloque, solo que no quiero que se muestre sino que me lo de.
		}

		// copiar el archivo que esta en memoria al archivo creado
	} else {
		perror("[ERROR] No disponible archivo");
		exit(-1);
	}
	//debo buscar todos los bloques de este archivo. filtro la lista

	//hacer un for hasta el tamaño de la lista. e ir pidiendo elemento de la lista
	//luego para ese elemento se debe pedir a su correspondiente nodo el bloque
	//posteriormente se debe copiar a memoria este bloque eh ir armando el archivo

}
void solicitarMD5deUnArchivoenMDFS() {
// falta implementar, esta en las condiciones minimas
// se debe factorizar entre esta y la funcion copiarArchivoDelMDFSAlFSLocal();
	//una vez armado el archivo copiarlo al FS local y luego se debe aplicar el comando md5sum con la funcion system
//para obtener el numero de md5.
// se debe aplicar el mismo comando md5sum al archivo original y  se ambos numeros resultados deben ser iguales (esto es solo visual)
//se puede sacar una funcion en comun con "copiarArchivoDelMDFSAlLocal"
}

ubicacionDelBloqueEnNodo* verUbicacionBloque() {
	int numeroBloque;
	char nombreArchivo[LONGITUD_STRINGS];

	ubicacionDelBloqueEnNodo* ptrNodoBloque = malloc(
			sizeof(ubicacionDelBloqueEnNodo));

	printf("Ingrese el nombre del archivo");
	scanf("%s", nombreArchivo);

	printf("Ingrese el numero de bloque a mostrar");
	scanf("%d", &numeroBloque);

	ptrNodoBloque = devuelveBloque(nombreArchivo, numeroBloque);
	printf("El bloque %d del archivo %s se encuentra en:\n"
			"Nodo: %d  -  BloqueDelNodo: %d", numeroBloque, nombreArchivo,
			ptrNodoBloque->numeroNodo, ptrNodoBloque->numeroDeBloqueDelNodo);
	return ptrNodoBloque;
}

void verBloque() {
	ubicacionDelBloqueEnNodo* ptrNodoBloque;
	ptrNodoBloque = verUbicacionBloque();
// solicitarPorSockect() pido el bloque a este nodo y luego lo muestro por pantalla.
// hago este free porque antes se hizo un malloc en la fucion verUbicacionBloque
	free(ptrNodoBloque);
}

void solicitudCopiaDeBloque() {
//se esta desarrollando, debe solicitar un bloque a un nodo
//usando parte de la funcion de mostrar bloque
}

void copiarBloque() {

	int numeroBloque = 0, numeroNodoDest, numeroBloqDest;
	char nombreArchivo[LONGITUD_STRINGS];
	ubicacionDelBloqueEnNodo* ptrNodoBloque = malloc(
			sizeof(ubicacionDelBloqueEnNodo));
	ubicacionDelBloqueEnNodo* ubicacionDestino = malloc(
			sizeof(ubicacionDelBloqueEnNodo));
	printf("Ingrese el nombre del archivo");
	scanf("%s", nombreArchivo);

	printf("Ingrese el numero de bloque a mostrar");
	scanf("%d", &numeroBloque);

	ptrNodoBloque = devuelveBloque(nombreArchivo, numeroBloque);

	printf("Ingrese el numero del nodo ");
	scanf("%d", &numeroNodoDest);

	printf("Ingrese el numero del bloque a ubicar");
	scanf("%d", &numeroBloqDest);
	ubicacionDestino->numeroDeBloqueDelNodo = numeroBloqDest;
	ubicacionDestino->numeroNodo = numeroNodoDest;
	ubicacionDestino->numeroCopia = ptrNodoBloque->numeroCopia + 1;
	solicitudCopiaDeBloque(); // se quiere pedir al nodo que tiene el bloque, dicho bloque
//se encuentra en desarrollo, no terminado

	free(ubicacionDestino);
	free(ptrNodoBloque);
// se implementa segun lo que diga el ayudante.
}

void actualizarListaDeArchivos(ubicacionDelBloqueEnNodo* unaUbicacion,
		element* unArchivo) {
	int nodoABuscar = unaUbicacion->numeroNodo;
	int bloqueABuscar = unaUbicacion->numeroDeBloqueDelNodo;
	nod* unNodo = NULL;
	bool condicion(ubicacionDelBloqueEnNodo* ubicacionDeLista) {
		if (ubicacionDeLista->numeroNodo == nodoABuscar
				&& ubicacionDeLista->numeroDeBloqueDelNodo == bloqueABuscar) {
			return true;
		}
		return false;
	}
	list_remove_by_condition(unArchivo->dobleListaUbicacionDelBloqueEnNodo,
			(void*) condicion);	// Es una lista doble!!
	unNodo = list_find(FILESYSTEM->listaNodos, (void*) condicion);
	unNodo->estado = ESTA_DISPONIBLE;
}

void borrarBloque() {
	int numBloque, numeroNodo;
	char nombreArchivo[LONGITUD_STRINGS];
	element* ptrArchivo = malloc(sizeof(element));
	ubicacionDelBloqueEnNodo* miUbicacion = malloc(
			sizeof(ubicacionDelBloqueEnNodo));
	ubicacionDelBloqueEnNodo* ubicacionNodoBloqueTemp = malloc(
			sizeof(ubicacionDelBloqueEnNodo));
//se declaran las inner function

	printf("Ingrese el nombre del archivo: ");
	fflush(stdin);
	scanf("%s", nombreArchivo);

	printf("Ingrese el numero de bloque a borrar: ");
	fflush(stdin);
	scanf("%d", &numBloque);

	bool condicion3(ubicacionDelBloqueEnNodo* unaUbic) { //esta es una inner function, declarada dentro de una funcion.
		return (numBloque == unaUbic->bloqueArchivo); //quiero buscar el bloque del archivo que me pidieron
	}

	ptrArchivo = buscarElementoPorNombre(nombreArchivo);
	ubicacionNodoBloqueTemp = list_find(
			ptrArchivo->dobleListaUbicacionDelBloqueEnNodo, (void*) condicion3);

	numBloque = ubicacionNodoBloqueTemp->numeroDeBloqueDelNodo;
	numeroNodo = ubicacionNodoBloqueTemp->numeroNodo;

	if (ptrArchivo == NULL) {
		perror("[ERROR] No se puede borrar el bloque archivo invalido");
		exit(-1);
	} else {
		bool condicion(nod* nodo) { //esta es una inner function, declarada dentro de una funcion.
			return (nodo->numero == numeroNodo); //quiero buscar el numero del Nodo que tiene el bloqueArchivo
		}
		nod* nodo = malloc(sizeof(nod));
		nodo = list_find(FILESYSTEM->listaNodos, (void*) condicion);

		bool condicion2(bloq* unBloque) { //esta es una inner function, declarada dentro de una funcion.
			return (numBloque == unBloque->numero); // quiero el bloque del nodo que contiene al bloque del archivo
		}
		bloq* bloque = malloc(sizeof(bloq));
		bloque = list_find(nodo->listaBloques, (void*) condicion2);

		bloque->estaOcupado = ESTA_DISPONIBLE;
		free(nodo);
		free(bloque);
	}

// Seteo miUbicacion
	miUbicacion->numeroNodo = numeroNodo;
	miUbicacion->numeroDeBloqueDelNodo = numBloque;
// Fin seteo

	actualizarListaDeArchivos(miUbicacion, ptrArchivo);
	free(ptrArchivo);
	free(miUbicacion);
	free(ubicacionNodoBloqueTemp);
}

void agregarNodo() { //FALTA VER EL TEMA DE SOCKETS

	nod* nodo;
	nodo = crearNodo(); // la funcion constructora no recibe ningun parametro

//	buscarPorsocketNodo(nodo->numero);// se le manda el numero identificatorio de ese nodo, que el nodo debe guardar
//  implementame Santiago
// por lo que aca debe haber otra funcion que envie ese numero al nodo.

	list_add(FILESYSTEM->listaNodos, nodo);
// Agrega al nodo a la lista de nodos del FS
}

void eliminarNodo() { //falta implementar lo de sockets
	int numero;

	printf("ingrese el numero de nodo a eliminar \n");
	scanf("%d", &numero);
	marcaNodoDesconectado(numero);
}

void mostrarComandos() {
	char* funcionesConsola[] = { "formatearMDFS", "eliminarArchivo",
			"renombrarArchivo",
			"moverArchivos",	 // Archivos
			"crearDirectorio", "eliminarDirectorio", "renombrarDirectorio",
			"moverDirectorio",  // Directorios
			"copiarArchivoLocalAlMDFS", "copiarArchivoDelMDFSAlFSLocal",
			"solicitarMD5deUnArchivoenMDFS", "verBloque", "borrarBloque",
			"copiarBloque",	// Bloques
			"agregarNodo", "eliminarNodo", // Nodos
			"mostrarComandos", "mostrarElementos" };

	char* descripcionesConsola[] = { "Descrpcion de la funcion 1",
			"Descripcion de la funcion 2", "Descripcion de la funcion 3",
			"Descripcion de la funcion 4", "Descripcion de la funcion 5",
			"Descripcion de la funcion 6", "Descripcion de la funcion 7",
			"Descripcion de la funcion 8", "Descripcion de la funcion 9",
			"Descripcion de la funcion 10", "Descripcion de la funcion 11",
			"Descripcion de la funcion 12", "Descripcion de la funcion 13",
			"Descripcion de la funcion 14", "Descripcion de la funcion 15",
			"Descripcion de la funcion 16", "Descripcion de la funcion 17",
			"Descripcion de la funcion 18" };

	int contador = 0;
	while (contador <= NUMEROFUNCIONESCONSOLA - 1) {
		printf("*------------------------------------------*\n");
		printf("COMANDO 	= %s\n", funcionesConsola[contador]);
		printf("DESCRIPCION = %s\n", descripcionesConsola[contador]);
		printf("*------------------------------------------*\n");
		contador += 1;
	}
}

// ---------CONSOLA IMPLEMENTACION------
void mostrarElementos() {
	int elementosEnLista = FILESYSTEM->listaElementos->elements_count;
	int i;
	for (i = 0; i < elementosEnLista; i++) {
		element* elementoi;
		elementoi = list_get(FILESYSTEM->listaElementos, i);
		printf("Index:%d   Elemento:%s\n", elementoi->index, elementoi->nombre);
	}
}

int idFuncion(char* funcion) {
	int i;

	char* funcionesConsola[] = { "formatearMDFS", "eliminarArchivo",
			"renombrarArchivo",
			"moverArchivos",	 // Archivos
			"crearDirectorio", "eliminarDirectorio", "renombrarDirectorio",
			"moverDirectorio",  // Directorios
			"copiarArchivoLocalAlMDFS", "copiarArchivoDelMDFSAlFSLocal",
			"solicitarMD5deUnArchivoenMDFS", "verUbicacionBloque",
			"borrarBloque", "copiarBloque",	// Bloques
			"agregarNodo", "eliminarNodo", // Nodos
			"mostrarComandos", "mostrarElementos" };

	for (i = 0;
			(i < NUMEROFUNCIONESCONSOLA)
					&& (strcmp(funcion, funcionesConsola[i]) != 0); i++)
		;
	return (i <= NUMEROFUNCIONESCONSOLA - 1) ? (i + 1) : -1;
}

void aplicarFuncion(int idFuncion) { //selecciona un case en base al numero que llevaba el contador y aplica la funcion recibe el dir
	switch (idFuncion) {

	enum nomFun {
		FORMATEAR_MDFS = 1,
		ELIMINAR_ARCHIVO,
		RENOMBRAR_ARCHIVO,
		MOVER_ARCHIVOS,
		CREAR_DIRECTORIO,
		ELIMINAR_DIRECTORIO,
		RENOMBRAR_DIRECTORIO,
		MOVER_DIRECTORIO,
		COPIAR_ARCHIVO_LOCAL_AL_MDFS,
		COPIAR_ARCHIVO_DEL_MDFS_AL_FS_LOCAL,
		SOLICITAR_MD5_DE_UN_ARCHIVO_EN_MDFS,
		VER_BLOQUE,
		BORRAR_BLOQUE,
		COPIAR_BLOQUE,
		AGREGAR_NODO,
		ELIMINAR_NODO,
		MOSTRAR_COMANDOS,
		MOSTRAR_ELEMENTOS
	};
// Lo que hace el enum es convertirme lo que dice en enteros

case FORMATEAR_MDFS:
	formatearMDFS();
	break;

case ELIMINAR_ARCHIVO:
	eliminarArchivo();
	break;

case RENOMBRAR_ARCHIVO:
	renombrarArchivo();
	break;

case MOVER_ARCHIVOS:
	moverArchivo();
	break;

case CREAR_DIRECTORIO:
	crearDirectorio();
	break;

case ELIMINAR_DIRECTORIO:
	eliminarDirectorio();
	break;

case RENOMBRAR_DIRECTORIO:
	renombrarDirectorio();
	break;

case MOVER_DIRECTORIO:
	moverDirectorio();
	break;

case COPIAR_ARCHIVO_LOCAL_AL_MDFS:
	copiarArchivoLocalAlMDFS();
	break;

case COPIAR_ARCHIVO_DEL_MDFS_AL_FS_LOCAL:
	copiarArchivoDelMDFSAlFSLocal();
	break;

case SOLICITAR_MD5_DE_UN_ARCHIVO_EN_MDFS:
	solicitarMD5deUnArchivoenMDFS();
	break;

case VER_BLOQUE:

	break;

case BORRAR_BLOQUE:
	borrarBloque();
	break;

case COPIAR_BLOQUE:
	copiarBloque();
	break;

case AGREGAR_NODO:
	agregarNodo();
	break;

case ELIMINAR_NODO:
	eliminarNodo();
	break;

case MOSTRAR_COMANDOS:
	mostrarComandos();
	break;

case MOSTRAR_ELEMENTOS:
	mostrarElementos();
	break;

case -1:
	printf("--Ojo ese comando no existe!! proba con mostrarComandos\n");
	break;

	}
}

void levantarConsola() {
	char comando[50];
	int idFunc;

	mostrarComandos();

	while (1) {

		printf("Ingrese un comando >> ");
		fgets(comando, 50, stdin);

		idFunc = idFuncion(comando);
		aplicarFuncion(idFunc);
	}
}
