#include "filesystem.h"

/*------------------FUNCIONES CONSTRUCTORAS----------------------*/

nod* crearNodo(char* nombre) {	//constructor del nodo
	nod* nodo = malloc(sizeof(nod));
	strcpy(nodo->nombre, nombre);	//le pongo nombre al nodo
	nodo->estado = NODOOPERATIVO; // pongo en estado operativo
	//nodo->tamanio = TAMANIONODO; consultar, posiblemente no sea necesario
	nodo->listaBloques = list_create(); // bloq * creamos lista de bloques
	cargarBloques(nodo->listaBloques); //carga 102 bloques

	return nodo;
}

bloq* crearBloque() { //constructor del bloque
	bloq* bloque = malloc(sizeof(bloq));
	bloque->nombre = 0;
	bloque->nombreArchivo[25] = '\0';
	bloque->nombreDirectorio = 0;
	bloque->tamanio = 20971520; //20 mb
	return bloque;
}

element* crearElemento() { //crea un elemento generico para despues configurarlo como archivo o carpeta
	element* elemento = malloc(sizeof(element)); //liberamos espacio para el elemnto
	elemento->elemento = 0;
	elemento->directorioPadre = 0;
	elemento->index = 0;
	elemento->estado = 0;
	elemento->listaNodoBloque = '\0';
	elemento->nombre[25] = '\0';
	elemento->tamanio = 0;
	return elemento;
}

fs* crearFileSystem() { //entra como parametro el fd del archivo config(CONSTRUCTOR DEL FS)[EN CONSTRUCCION]
	fs* fileSystem = malloc(sizeof(fs));
	fileSystem->estado = 0; //creo que 0 era disponible sino lo cambiamos
	fileSystem->listaNodos = list_create(); //nod*
	fileSystem->listaElementos = list_create(); // crea lista de elementos element *
	fileSystem->espacioDisponible = 0;
	return fileSystem; //retorna el fs
}

/*-----------------------------------------------------------------------*/

/*------------------------FUNCIONES DESTRUCTORAS-------------------------*/
void liberaMemoriaBloque(bloq* bloque) { //libera memoria del tipo bloque
	free(&bloque->nombre);
	free(&bloque->nombreArchivo);
	free(&bloque->nombreDirectorio);
	free(&bloque->tamanio);
	free(bloque);
}
void liberaMemoriaNodo(nod* nodo) { //libera la memoria del nodo
	int i = 0;

	free(&nodo->estado);fs* inicializarFs(int fdArchConfig) {

		return FILESYSTEM;
	}
	free(&nodo->nombre);
	free(&nodo->ptrdirEspacioNodo);
	free(&nodo->tamanio);
	for (; i <= nodo->listaBloques->elements_count; i++) { //libero memoria de los bloques
		list_destroy_and_destroy_elements(nodo->listaBloques,
				(void*) liberaMemoriaBloque); //consultar porque no agarra el index
	}
	free(nodo);
}

void liberaNodoBloque(nodBloq* nodoBloque) {
	free(&(nodoBloque->numeroBloque));
	free(&(nodoBloque->numeroCopia));
	free(&(nodoBloque->numeroNodo));
	free(nodoBloque);
}

void liberaMemoriaElement(element* elemento) {
	int i = 0;
	free(&(elemento->directorioPadre));
	free(&(elemento->elemento));
	free(&(elemento->estado));
	free(&(elemento->index));
	free(&(elemento->nombre));
	free(&(elemento->tamanio));
	for (; i <= elemento->listaNodoBloque->elements_count; i++) { //libero memoria de los Nodobloques
		list_destroy_and_destroy_elements(elemento->listaNodoBloque, (void*)liberaNodoBloque);
	}  //consultar el uso de list_destroy que no esta recibiendo el index i
	free(elemento);
}
void liberaMemoriaFS(){
	int i=0;
	free(&FILESYSTEM->espacioDisponible);
	free(&FILESYSTEM->estado);
	for (; i <= FILESYSTEM->listaNodos->elements_count; i++) { //libero memoria de los Nodobloques
			list_destroy_and_destroy_elements(FILESYSTEM->listaNodos, (void*)liberaMemoriaNodo);
		}  //consultar el uso de list_destroy que no esta recibiendo el index i

	for (; i <= FILESYSTEM->listaElementos->elements_count; i++) { //libero memoria de los Nodobloques
			list_destroy_and_destroy_elements(FILESYSTEM->listaElementos, (void*)liberaMemoriaElement);
		} //consultar el uso de list_destroy que no esta recibiendo el index i
	free(FILESYSTEM);
}

/*-----------------------------------------------------------------------*/

/*------------------------FUNCIONES AUXILIARES---------------------------*/
void cargarBloques(t_list *listaBloques) {
	int i = 0;
	for (; i <= NUMEROBLOQUES; i++) { //ciclo de for para cargar los 102 bloques
		bloq* bloque;  //varaible para almacenar el bloque creado
		bloque = crearBloque();  //crea el bloque
		list_add(listaBloques, bloque);  //lo agrega a la lista
	}
}

void leerRegistro(int arch) {
	read(arch, FILESYSTEM, sizeof(fs)); //lee el archivo y pone la estructura en la estructura fs

}

void guardarRegistro(int arch) { //esto mientras este el archivo abierto sino lo abrimos aca

	write(arch, FILESYSTEM, sizeof(fs)); //le paso el registro fileSystem,y el archivo y lo escribe
}

/*----------------------------------------------------------------------*/

/*-------------------FUNCIONES DE CONSOLA------------------------*/

void agregarN(char* nombre) { //FALTA VER EL TEMA DE SOCKETS
	nod* nodo;
	nodo = crearNodo(nombre); //se usa el constructor para crear el nodo
	list_add(FILESYSTEM->listaNodos, nodo); //agrega al nodo a la lista de nodos del FS
//agregarDir(fileSystem->listaDirectorios,nodo->nombre);//se agrega un dir con el nombre del nodo[EN PROCESO]-quizas no se haría

}

void eliminarN(char* nombre) { //faltaria la condicion pero nose como ponerla
//list_remove_by_condition(FILESYSTEM->listaNodos), condicion(nombre) );//remueve de la lista el nodo que concuerda con el nombre ingresado eso creo
}

void formatear(int fdArchConfig) { //recive una entidad FS , libera su memoria y despues la crea devuelta, habia que ver sino inicilizarla[EN PROCESO TODAVIA LE FALTA]
//free(fileSystem);

	FILESYSTEM = inicializarFs(fdArchConfig);
}

void crearCarpeta(int dirPadre, char* nombre) {
	element* carpeta;
	carpeta = crearElemento();
	carpeta->nombre = nombre;
	carpeta->directorioPadre = dirPadre;
	carpeta->index = malloc(sizeof(int));	// int = habira que generar una funcion que devuelva el index correspondiente en base al directorio padre en el que se agrega la carpeta
	FILESYSTEM->listaElementos = list_add(FILESYSTEM->listaElementos,
			carpeta);
}

void inicializarFS(int fdArchConfig) {


}
/*---------------------------------------------------------------*/

