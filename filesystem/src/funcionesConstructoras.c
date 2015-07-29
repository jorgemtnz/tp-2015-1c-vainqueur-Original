#include "filesystem.h"

/*------------------FUNCIONES CONSTRUCTORAS----------------------*/

bloq* crearBloque() { //constructor del bloque
	bloq* bloque = malloc(sizeof(bloq));
	if (bloque == NULL) {
		perror("[ERROR] No se reservo memoria para el Filesystem>..>bloque ");
		exit(-1);
	}
	bloque->numero = 0; // cuando se cree se le va cambiando desde la funcion que llama
	bloque->tamanio = VEINTEMEGAS; //20 mb
	bloque->estaOcupado = ESTA_DISPONIBLE;
	return bloque;
}

nod* crearNodo() {  //para nodos conectados
	nod* nodo = malloc(sizeof(nod));
	if (nodo == NULL) {
		perror("[ERROR] No se reservo memoria para el Filesystem>..>nodo ");
		exit(-1);
	}
		nodo->numero=0;

    nodo->tamanioNodo=0;
	nodo->estado = DESCONECTADO;
	nodo->listaBloques = list_create();
	return nodo;
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

element* crearElemento(char* nombre) { //crea un elemento generico para despues configurarlo como archivo o carpeta
	element* elemento = malloc(sizeof(element)); //creamos espacio para el elemnto
	if (elemento == NULL) {
		perror(
				"[ERROR] No se reservo memoria para el Filesystem>..>elemento directorio o archivo ");
		exit(-1);
	}
	elemento->nombre = nombre;
	elemento->estado = DISPONIBLE;

		elemento->index = FILESYSTEM->idElemento + 1; // asigno el que tiene +1
		FILESYSTEM->idElemento = elemento->index; // actualizo el id

	elemento->tamanio = 0; // Si es directorio siempre pesa 0. Si es archivo va a engordar
	elemento->directorioPadre = 0; // este es el directorio raiz.
	elemento->dobleListaUbicacionDelBloqueEnNodo = list_create();

	elemento->idUbicacionDelBloqueEnNodo = 0; //se modifica desde el que llama
	return elemento;
}

void crearFileSystem() {
	fs* filesystem = malloc(sizeof(fs));
	element* directorioRaiz = malloc(sizeof(fs));;

	if (filesystem == NULL) {
		perror("[ERROR] No se reservo memoria para el Filesystem ");
		exit(-1);
	}
	filesystem->estado = NOOPERATIVO;
	filesystem->espacioDisponible = 0;
	filesystem->idElemento = 0;
	filesystem->idNodo = 0; // id de cada nodo se envia al nodo por socket
	filesystem->listaElementos = list_create();
	filesystem->listaNodosActivos = list_create();

	//se crea filesystem con el directorio raiz
	directorioRaiz->directorioPadre =0;
	directorioRaiz->dobleListaUbicacionDelBloqueEnNodo= list_create();
	directorioRaiz->estado = DISPONIBLE;
	directorioRaiz->idUbicacionDelBloqueEnNodo =0;
	directorioRaiz->index =0;
	directorioRaiz->nombre = "dirRaiz";
	directorioRaiz->tamanio=0;
	directorioRaiz->tipoElemento= ESDIRECTORIO;


	list_add(filesystem->listaElementos, directorioRaiz);

	FILESYSTEM = filesystem; // Modifica variable global
}

void inicializarFilesystem() {		// Se inicializa cuando se formatea
//solo debe olvidar los archivos y directorios que contenga
	FILESYSTEM->listaElementos = list_create();
	FILESYSTEM->idElemento =0;
	FILESYSTEM->espacioDisponible = 0;
}
