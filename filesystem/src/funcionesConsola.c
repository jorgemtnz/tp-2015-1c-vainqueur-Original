#include "filesystem.h"

/*------------------- CONSOLA------------------------*/

// s	formatearMDFS
// s    eliminarArchiv
// s 	renombrarArchivo
// s	moverArchivo
// s	crearDirectorio
// s    eliminarDirectorio
// s    renombrarDirectorio
// s	moverDirectorio
// s	copiarArchivoLocalAlMDFS
// n	copiarArchivoDelMDFSAlFSLocal
// n	solicitarMD5deUnArchivoenMDFS
// s	verUbicacionBloque
// s	borrarBloque
// s	copiarBloque
// s	agregarNodo  			// No debe recibir argumentos // Falta sockets
// n	eliminarNodo
// s	mostrarComandos
// s 	mostrarElementos 		// Yapa

void renombrarElemento(element* ptrElemento, char* nuevoNombreElemento)
{
	strcpy(ptrElemento->nombre, nuevoNombreElemento);
}
void moverElemento(element* elementoOrigen, element* directorioDestino)
{ // Valido que no se quiera mover dentro de un archivo
	if (directorioDestino->tipoElemento == ESDIRECTORIO)
	{ // Hago el cambio de directorio padre con el index del directorio padre
		elementoOrigen->directorioPadre = directorioDestino->index;
	}
	else
	{
		perror(
				"[ERROR]no se puede mover. El directorio destino no es un tipo directorio");
		exit(-1);
	}
}
void eliminarElemento(char* nombreElemento)
{
	int i;
	int elementosEnLista = FILESYSTEM->listaElementos->elements_count;
	int sonIguales;

	for (i = 0; i <= elementosEnLista; i++)
	{
		element* elementoi;
		elementoi = list_get(FILESYSTEM->listaElementos, i);
		sonIguales = string_equals_ignore_case(elementoi->nombre,
				nombreElemento);
// Si las cadenas son iguales => encontro string => lo elimino

		if (sonIguales)
		{
			list_remove(FILESYSTEM->listaElementos, i);
		}

		// Si las cadenas son distintas => Sigue el for
	}
} // Sirve para archivos y directorios

void formatearMDFS()
{
	liberaMemoriaFS();
	inicializarFilesystem();
}

void eliminarArchivo()
{
	char nombreArchivo[LONGITUD_STRINGS];
	printf("Ingrese el nombre del archivo que desea eliminar: ");
	fflush(stdin);
	scanf("%s", nombreArchivo);
	eliminarElemento(nombreArchivo);
}

void renombrarArchivo()
{
	char nombreArchivo[LONGITUD_STRINGS], nuevoNombreArchivo[LONGITUD_STRINGS];
	element* ptrArchivo;

	printf("Ingrese nombre de archivo a renombrar");
	fflush(stdin);
	scanf("%s", nombreArchivo);

	printf("Ingrese nuevo nombre para el archivo");
	fflush(stdin);
	scanf("%s", nuevoNombreArchivo);

	ptrArchivo = buscarElementoPorNombre(nombreArchivo);
	if (ptrArchivo == NULL)
	{
		perror("[ERROR] No existe el archivo");
		exit(-1);
	}
	renombrarElemento(ptrArchivo, nuevoNombreArchivo);
}

void moverArchivo()
{
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
	if ((directorioDestino == NULL) || (ptrArchivo == NULL))
	{
		perror("[ERROR] No se puede mover el archivo");
		exit(-1);
	}
	else
	{
		moverElemento(ptrArchivo, directorioDestino);
	}
}

void crearDirectorio()
{
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

	if (padre == NULL)
	{
		perror("Numero invalido de directorio padre\n");
		exit(-1);
	}
	indexPadre = padre->index;

	// Seteo la carpeta creada
	carpetaNueva->nombre = strdup(nombre);
	carpetaNueva->estado = DISPONIBLE;
	carpetaNueva->tipoElemento = ESDIRECTORIO;
	if (!list_is_empty(FILESYSTEM->listaElementos))
	{
		carpetaNueva->index = FILESYSTEM->listaElementos->elements_count += 1;
	}
	else
	{ // Primera vez
		carpetaNueva->index = 1;
	}
	carpetaNueva->directorioPadre = dirPadre;  // Contemplar observacion
	carpetaNueva->tamanio = TAMANIO_DIRECTORIO;
	// Fin: carpetaNueva seteada

	list_add(FILESYSTEM->listaElementos, carpetaNueva);
}

void eliminarDirectorio()
{
	char nombreDirectorio[LONGITUD_STRINGS];

	printf("Ingrese el nombre del Directorio: ");
	fflush(stdin);
	scanf("%s", nombreDirectorio);
	eliminarElemento(nombreDirectorio);
}

void renombrarDirectorio()
{
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
	if (ptrDirectorio == NULL)
	{
		perror("[ERROR] No existe el directorio");
		exit(-1);
	}
	renombrarElemento(ptrDirectorio, nuevoNombreDirectorio);
}

void moverDirectorio()
{
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

	if ((directorioDestino == NULL) || (directorioOrigen == NULL))
	{
		perror("[ERROR] No se puede mover el directorio");
		exit(EXIT_FAILURE);
	}

	moverElemento(directorioOrigen, directorioDestino);
}

char* sacarUltimaParte(char* dirArchivoLocal)
{
	char* nombreArchivo;
	nombreArchivo = strdup(strrchr(dirArchivoLocal, '/'));
	sscanf(nombreArchivo,"/%s",nombreArchivo); // Le borro el primer char
	return nombreArchivo;
}

void copiarArchivoLocalAlMDFS()
{
	// La copia la crea en la raiz
	char* dirArchivoLocal;
	char* nombreArchivo;
	char* dirArchivo;
	element* archivoEntrante;
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

	dirArchivo = strdup(dirArchivoLocal);

	mapeoAmemoria(dirArchivo, ptrAMemoriaModificado, ptrTamanioDePagina);
	buffer = string_split(ptrComienzoMemoriaMapeada, "\n");
	desMapea(*ptrTamanioDePagina, ptrComienzoMemoriaMapeada);

	// Lo alojamos en la raiz, index de la raiz = 0. Cualquier cosa lo movemos
	// Seteo archivoEntrante
	archivoEntrante->directorioPadre = 0;
	archivoEntrante->nombre = strdup(nombreArchivo);
	archivoEntrante->estado = DISPONIBLE;
	archivoEntrante->tipoElemento = ESARCHIVO;
	archivoEntrante->tamanio = *ptrTamanioDePagina;

	divideBloques(&buffer[0], nombreArchivo);
}

void copiarArchivoDelMDFSAlFSLocal()
{
	// Falta iplementar
}
void solicitarMD5deUnArchivoenMDFS()
{
	// falta implementar
}

void verUbicacionBloque()
{
	int numeroBloque;
	char nombreArchivo[LONGITUD_STRINGS];

	element* ptrArchivo;
	ubicacionDelBloqueEnNodo* ptrNodoBloque;

	printf("Ingrese el nombre del archivo");
	scanf("%s", nombreArchivo);

	printf("Ingrese el numero de bloque a mostrar");
	scanf("%d", &numeroBloque);

	ptrNodoBloque = devuelveBloque(nombreArchivo, numeroBloque);
	printf("El bloque %d del archivo %s se encuentra en:\n"
			"Nodo: %d  -  BloqueDelNodo: %d", numeroBloque, nombreArchivo,
			ptrNodoBloque->numeroNodo, ptrNodoBloque->numeroDeBloqueDelNodo);
}

void copiarBloque()
{
	int numeroBloque = 0;
	char nombreArchivo[LONGITUD_STRINGS];
	ubicacionDelBloqueEnNodo* ptrNodoBloque;

	printf("Ingrese el nombre del archivo");
	scanf("%s", nombreArchivo);

	printf("Ingrese el numero de bloque a mostrar");
	scanf("%d", &numeroBloque);

	ptrNodoBloque = devuelveBloque(nombreArchivo, numeroBloque);
	// se implementa segun lo que diga el ayudante.
}

/*
 void borrarBloque() {
 int numeroBloque = 0;
 char nombreArchivo[300];
 element* ptrArchivo;
 //defino aqui para que numeroBloque pueda ser usada y pueda comparar
 bool compNumeroBloque(nodBloq* elemento) {
 return (numeroBloque == elemento->numeroBloque);
 }
 printf("Ingrese el nombre del archivo");
 scanf("%c", nombreArchivo);
 printf("Ingrese el nombre de bloque a borrar");
 scanf("%d", &numeroBloque);

 ptrArchivo = buscarElementoPorNombre(nombreArchivo);

 if (ptrArchivo == NULL) {
 perror("[ERROR] No se puede borrar el bloque archivo invalido");
 exit(-1);
 } else { //se castea con (void*) cuandole paso las funciones
 list_remove_and_destroy_by_condition(ptrArchivo->listaNodoBloque,
 (void*) compNumeroBloque, (void*) liberaNodoBloque);
 }
 }
 */
void agregarNodo(char* nombre)
{ //FALTA VER EL TEMA DE SOCKETS
	nod* nodo;
	nodo = crearNodo(nombre);
	list_add(FILESYSTEM->listaNodosConectados, nodo);
// Agrega al nodo a la lista de nodos del FS
}

void eliminarNodo(char* nombre)
{
//list_remove_by_condition(FILESYSTEM->listaNodos), condicion(nombre) );//remueve de la lista el nodo que concuerda con el nombre ingresado eso creo
}

void mostrarComandos()
{
	char* funcionesConsola[] =
	{ "formatearMDFS", "eliminarArchivo", "renombrarArchivo",
			"moverArchivos",	 // Archivos
			"crearDirectorio", "eliminarDirectorio", "renombrarDirectorio",
			"moverDirectorio",  // Directorios
			"copiarArchivoLocalAlMDFS", "copiarArchivoDelMDFSAlFSLocal",
			"solicitarMD5deUnArchivoenMDFS", "verBloque", "borrarBloque",
			"copiarBloque",	// Bloques
			"agregarNodo", "eliminarNodo", // Nodos
			"mostrarComandos", "mostrarElementos" };

	char* descripcionesConsola[] =
	{ "Descrpcion de la funcion 1", "Descripcion de la funcion 2",
			"Descripcion de la funcion 3", "Descripcion de la funcion 4",
			"Descripcion de la funcion 5", "Descripcion de la funcion 6",
			"Descripcion de la funcion 7", "Descripcion de la funcion 8",
			"Descripcion de la funcion 9", "Descripcion de la funcion 10",
			"Descripcion de la funcion 11", "Descripcion de la funcion 12",
			"Descripcion de la funcion 13", "Descripcion de la funcion 14",
			"Descripcion de la funcion 15", "Descripcion de la funcion 16",
			"Descripcion de la funcion 17", "Descripcion de la funcion 18" };

	int contador = 0;
	while (contador <= NUMEROFUNCIONESCONSOLA - 1)
	{
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
	for (i = 0; i <= elementosEnLista; i++) {
		element* elementoi;
		elementoi = list_get(FILESYSTEM->listaElementos, i);
		printf("Index:%d   Elemento:%s\n", elementoi->index, elementoi->nombre);
	}
}

int idFuncion(char* funcion)
{
	int i;

	char* funcionesConsola[] =
	{ "formatearMDFS", "eliminarArchivo", "renombrarArchivo",
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

void aplicarFuncion(int idFuncion)
{ //selecciona un case en base al numero que llevaba el contador y aplica la funcion recibe el dir
	switch (idFuncion)
	{

	enum nomFun
	{
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
	break;

case MOVER_ARCHIVOS:
	break;

case CREAR_DIRECTORIO:
	crearDirectorio();
	break;

case ELIMINAR_DIRECTORIO:
	eliminarDirectorio();
	break;

case RENOMBRAR_DIRECTORIO:
	break;

case MOVER_DIRECTORIO:
	break;

case COPIAR_ARCHIVO_LOCAL_AL_MDFS:
	break;

case COPIAR_ARCHIVO_DEL_MDFS_AL_FS_LOCAL:
	break;

case SOLICITAR_MD5_DE_UN_ARCHIVO_EN_MDFS:
	break;

case VER_BLOQUE:
	break;

case BORRAR_BLOQUE:
	break;

case COPIAR_BLOQUE:
	break;

case AGREGAR_NODO:
	break;

case ELIMINAR_NODO:
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

void levantarConsola()
{
	char comando[50];
	int idFunc;

	mostrarComandos();

	while (1)
	{

		printf("Ingrese un comando >> ");
		fgets(comando, 50, stdin);

		idFunc = idFuncion(comando);
		aplicarFuncion(idFunc);
	}
}
