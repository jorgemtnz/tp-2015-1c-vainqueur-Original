#include "filesystem.h"

/*------------------FUNCIONES CONSTRUCTORAS----------------------*/
nod* crearNodo() {
	nod* nodo = malloc(sizeof(nod));
	if (nodo == NULL) {
		perror("[ERROR] No se reservo memoria para el Filesystem>..>nodo ");
		exit(-1);
	}
	nodo->estado = OPERATIVO;
	nodo->listaBloques = list_create();
	return nodo;
}

bloq* crearBloque() { //constructor del bloque
	bloq* bloque = malloc(sizeof(bloq));
	if (bloque == NULL) {
		perror("[ERROR] No se reservo memoria para el Filesystem>..>bloque ");
		exit(-1);
	}
	bloque->numero = 0;
	bloque->tamanio = VEINTEMEGAS; //20 mb
	return bloque;
}
//no borrar esta funcion
ubicacionDelBloqueEnNodo* crearUbicacionDelBloqueEnNodo() {
	ubicacionDelBloqueEnNodo* unaUbicacion = malloc(
			sizeof(ubicacionDelBloqueEnNodo));
	if (unaUbicacion == NULL) {
		perror(
				"[ERROR] No se reservo memoria para el Filesystem>..>ubicacionDelBloqueEnNodo");
		exit(-1);
	}
	unaUbicacion->numeroCopia = 0; //este valor se setea posteriormente
	unaUbicacion->numeroDeBloqueDelNodo = 0;
	unaUbicacion->numeroNodo = 0;
	unaUbicacion->bloqueArchivo = 0;
	return unaUbicacion;
}

element* crearElemento() { //crea un elemento generico para despues configurarlo como archivo o carpeta
	element* elemento = malloc(sizeof(element)); //creamos espacio para el elemnto
	if (elemento == NULL) {
		perror(
				"[ERROR] No se reservo memoria para el Filesystem>..>elemento directorio o archivo ");
		exit(-1);
	}
	elemento->directorioPadre = 0;
	if (list_is_empty(FILESYSTEM->listaElementos)) {
		elemento->index = 0;
	} else {
		elemento->index += 1;
	}
	elemento->estado = DISPONIBLE;
	elemento->dobleListaUbicacionDelBloqueEnNodo = list_create();
	elemento->nombre[25] = '\0';
	elemento->tamanio = 0; // Si es directorio siempre pesa 0. Si es archivo va a engordar
	return elemento;
}

void crearFileSystem() {
	fs* filesystem = malloc(sizeof(fs));
	if (filesystem == NULL) {
		perror("[ERROR] No se reservo memoria para el Filesystem ");
		exit(-1);
	}

	filesystem->estado = OPERATIVO;
	FILESYSTEM = filesystem; // Modifica variable global
}

void inicializarFilesystem() {		// Se inicializa cuando se formatea
	FILESYSTEM->estado = DISPONIBLE;
	FILESYSTEM->listaNodosConectados = list_create();
	FILESYSTEM->listaElementos = list_create();
	FILESYSTEM->espacioDisponible = 0;
}
