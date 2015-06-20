#include "filesystem.h"

/*------------------- CONSOLA------------------------*/

// s	formatearMDFS
// s    eliminarArchiv
// s 	renombrarArchivo
// s	moverArchivo
// s	crearDirectorio
// s    eliminarDirectorio
// s    renombrarDirectorio 	// Es muy similar a renombrarArchivo
// s	moverDirectorio 		// Es muy similar a moverArchivo
// n	copiarArchivoLocalAlMDFS //Falta implementar
// n	copiarArchivoDelMDFSAlFSLocal
// n	solicitarMD5deUnArchivoenMDFS
// s	verBloque
// s	borrarBloque
// n	copiarBloque
// s	agregarNodo  			// No debe recibir argumentos // Falta sockets
// s	eliminarNodo			// No debe recibir argumentos
// s	mostrarComandos
// s 	mostrarElementos 		// Yapa
void formatearMDFS() {
	liberaMemoriaFS();
	inicializarFilesystem();
}

void eliminarArchivo() {
	char nombreArchivo[50];
	printf("Ingrese el nombre del archivo: ");
	scanf("%s", nombreArchivo);
	eliminarElemento(nombreArchivo);
}

void renombrarArchivo() {
	char nombreArchivo[LONGITUD_STRINGS], nuevoNombreArchivo[LONGITUD_STRINGS];
	element* ptrArchivo;
	printf("Ingrese nombre de archivo a renombrar");
	scanf("%s", nombreArchivo);
	printf("Ingrese nuevo nombre para el archivo");
	scanf("%s", nuevoNombreArchivo);
	ptrArchivo = buscarElementoPor(nombreArchivo);
	if (ptrArchivo == NULL) {
		perror("[ERROR] No existe el archivo");
		exit(-1);
	}
	renombrarElemento(ptrArchivo, nuevoNombreArchivo);

}

void moverArchivo() {
	char nombreArchivo[LONGITUD_STRINGS];
	char nombreDirectorioDestino[LONGITUD_STRINGS]; // Hacer un define
	element* ptrArchivo;
	element* directorioDestino;

	printf("Ingrese nombre de archivo");
	scanf("%s", nombreArchivo);
	printf("Ingrese el nombre del directorio destino");
	scanf("%s", nombreDirectorioDestino);

	directorioDestino = buscarElementoPor(nombreDirectorioDestino);
	ptrArchivo = buscarElementoPor(nombreArchivo);
	if ((directorioDestino == NULL) || (ptrArchivo == NULL)) {
		perror("[ERROR] No se puede mover el archivo");
		exit(-1);
	} else
		moverElemento(ptrArchivo, directorioDestino);
}

void crearDirectorio() {
	element* carpeta;
	int dirPadre;
	char nombre[50];

	printf("Ingrese el nombre de la carpeta: ");
	scanf("%s", nombre);

	printf("Ingrese directorio del padre: ");
	scanf("%d", &dirPadre);

	if (dirPadre < 0) {
		perror("Numero invalido de directorio padre\n");
		exit(-1);
	}

	carpeta = crearElemento();
	strcpy(carpeta->nombre, nombre);
	carpeta->directorioPadre = dirPadre;
	list_add(FILESYSTEM->listaElementos, carpeta);
}

void eliminarDirectorio() {
	char nombreDirectorio[50];

	printf("Ingrese el nombre del Directorio: ");
	scanf("%s", nombreDirectorio);
	eliminarElemento(nombreDirectorio);
}

void renombrarDirectorio() {
	element* ptrDirectorio;
	char nombreDirectorio[LONGITUD_STRINGS],
			nuevoNombreDirectorio[LONGITUD_STRINGS];

	printf("Ingrese nombre de directorio a renombrar");
	scanf("%s", nombreDirectorio);
	printf("Ingrese nuevo nombre para el directorio");
	scanf("%s", nuevoNombreDirectorio);
	ptrDirectorio = buscarElementoPor(nombreDirectorio);
	if (ptrDirectorio == NULL) {
		perror("[ERROR] No existe el directorio");
		exit(-1);
	}
	renombrarElemento(ptrDirectorio, nuevoNombreDirectorio);

}

void moverDirectorio() {
	char nombreDirectorioOrigen[LONGITUD_STRINGS];
	char nombreDirectorioDestino[LONGITUD_STRINGS]; // Hacer un define
	element* directorioOrigen;
	element* directorioDestino;

	printf("Ingrese nombre de Directorio Origen");
	scanf("%s", nombreDirectorioOrigen);
	printf("Ingrese el nombre del directorio destino");
	scanf("%s", nombreDirectorioDestino);
	directorioDestino = buscarElementoPor(nombreDirectorioDestino);
	directorioOrigen = buscarElementoPor(nombreDirectorioOrigen);
	if ((directorioDestino == NULL) || (directorioOrigen == NULL)) {
		perror("[ERROR] No se puede mover el directorio");
		exit(-1);
	} else
		moverElemento(directorioOrigen, directorioDestino);

}

void copiarArchivoLocalAlMDFS() {
	char* dirArchivoLocal;
	void* ptrComienzoMemoriaMapeada;
	int* ptrTamanioDePagina;
	char* ptrBloqueAEnviar;

	printf("Ingrese la ruta del nombre del archivo a copiar al MDFS");
	scanf("%s", dirArchivoLocal);

//mapea el archivo a memoria
mapeoAmemoria(dirArchivoLocal, ptrComienzoMemoriaMapeada, ptrTamanioDePagina);
ptrBloqueAEnviar = divideBloques(ptrComienzoMemoriaMapeada);

}

void verBloque() {

int numeroBloque = 0;
char nombreArchivo[300];
element* ptrArchivo;
nodBloq* ptrNodoBloque;

printf("Ingrese el nombre del archivo");
scanf("%c", nombreArchivo);
printf("Ingrese el numero de bloque a mostrar");
scanf("%d", &numeroBloque);

ptrNodoBloque = devuelveBloque(nombreArchivo, numeroBloque);
printf("EL bloque es  numero,%d,copia,%d,nodo,%d", ptrNodoBloque->numeroBloque,
		ptrNodoBloque->numeroCopia, ptrNodoBloque->numeroNodo);
}
void copiarBloque() {
int numeroBloque = 0;
char nombreArchivo[300];
nodBloq* ptrNodoBloque;

printf("Ingrese el nombre del archivo");
scanf("%c", nombreArchivo);
printf("Ingrese el numero de bloque a mostrar");
scanf("%d", &numeroBloque);

ptrNodoBloque = devuelveBloque(nombreArchivo, numeroBloque);
// se implementa segun lo que diga el ayudante.
}

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

ptrArchivo = buscarElementoPor(nombreArchivo);

if (ptrArchivo == NULL) {
	perror("[ERROR] No se puede borrar el bloque archivo invalido");
	exit(-1);
} else { //se castea con (void*) cuandole paso las funciones
	list_remove_and_destroy_by_condition(ptrArchivo->listaNodoBloque,
			(void*) compNumeroBloque, (void*) liberaNodoBloque);
}
}
void agregarNodo(char* nombre) { //FALTA VER EL TEMA DE SOCKETS
nod* nodo;
nodo = crearNodo(nombre);
list_add(FILESYSTEM->listaNodosConectados, nodo);
// Agrega al nodo a la lista de nodos del FS
}

void eliminarNodo(char* nombre) { //faltaria la condicion pero nose como ponerla
//list_remove_by_condition(FILESYSTEM->listaNodos), condicion(nombre) );//remueve de la lista el nodo que concuerda con el nombre ingresado eso creo
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
int idFuncion(char* funcion) {
int i;

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
