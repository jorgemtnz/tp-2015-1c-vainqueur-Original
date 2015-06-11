#include "filesystem.h"

/*------------------FUNCIONES CONSTRUCTORAS----------------------*/

nod* crearNodo(char* nombre) {	//constructor del nodo
	nod* nodo = malloc(sizeof(nod));
	strcpy(nodo->nombre, nombre);	//le pongo nombre al nodo
	nodo->estado = NODOOPERATIVO; // pongo en estado operativo
	nodo->tamanio = 2;
	nodo->listaBloques = list_create(); // bloq * creamos lista de bloques
	cargarBloques(nodo->listaBloques); //carga 102 bloques

	return nodo;
}

bloq* crearBloque() { //constructor del bloque
	bloq* bloque = malloc(sizeof(bloq));
	bloque->nombre = 0;
	bloque->nombreArchivo[25] = "\0";
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
	elemento->nombre[25] = "\0";
	elemento->tamanio = 0;
	return elemento;
}

fs* crearFileSystem() { //entra como parametro el fd del archivo config(CONSTRUCTOR DEL FS)[EN CONSTRUCCION]
	fs* fileSystem = malloc(sizeof(fs));
	fileSystem->estado = 0; //creo que 0 era disponible sino lo cambiamos
	fileSystem->listaNodos = list_create(); //nod*
	fileSystem->listaDirectorios = list_create(); // crea lista de elementos element *
	fileSystem->espacioDisponible = 0;
	return fileSystem; //retorna el fs
}

/*-----------------------------------------------------------------------*/

/*------------------------FUNCIONES DESTRUCTORAS-------------------------*/
void destruirBloque(bloq* bloque) { //libera memoria del tipo bloque
	free(bloque->nombre);
	free(bloque->nombreArchivo);
	free(bloque->nombreDirectorio);
	free(bloque->tamanio);
}

void destruirNodo(nod* nodo) { //libera la memoria del nodo
	free(nodo->estado);
	free(nodo->nombre);
	free(nodo->tamanio);
//list_clean_and_destroy_elements(nodo->listaBloques,(bloq* bloque));//falta ver bien como se escribe esta funcion pero tendria que vaciar la lista de blqoues de un nodo
}

/*-----------------------------------------------------------------------*/

/*------------------------FUNCIONES AUXILIARES---------------------------*/
void cargarBloques(t_list *listaBloques) {
	int i = 0;
	for (i; i <= NUMEROBLOQUES; i++) { //ciclo de for para cargar los 102 bloques
		bloq* bloque;  //varaible para almacenar el bloque creado
		bloque = crearBloque();  //crea el bloque
		list_add(listaBloques, bloque);  //lo agrega a la lista
	}
}

void leerRegistro(int arch, fs* fileSystem) {
	read(arch, fileSystem, sizeof(fs)); //lee el archivo y pone la estructura en la estructura fs

}

void guardarRegistro(int arch, fs* fileSystem) { //esto mientras este el archivo abierto sino lo abrimos aca

	write(arch, fileSystem, sizeof(fs)); //le paso el registro fileSystem,y el archivo y lo escribe
}

/*----------------------------------------------------------------------*/

/*-------------------FUNCIONES DE CONSOLA------------------------*/

void agregarN(fs* fileSystem, char* nombre) { //FALTA VER EL TEMA DE SOCKETS
	nod* nodo;
	nodo = crearNodo(nombre); //se usa el constructor para crear el nodo
	list_add(fileSystem->listaNodos, nodo); //agrega al nodo a la lista de nodos del FS
//agregarDir(fileSystem->listaDirectorios,nodo->nombre);//se agrega un dir con el nombre del nodo[EN PROCESO]-quizas no se haría

}

void eliminarN(fs* fileSystem, char* nombre) { //faltaria la condicion pero nose como ponerla
//list_remove_by_condition(fileSystem->listaNodos), bool(condicion(nombre)) );//remueve de la lista el nodo que concuerda con el nombre ingresado eso creo
}

fs* inicializarFs(int fdArchConfig){
	fs* filesystem;

return filesystem;
}

fs* formatear(int fdArchConfig) {	//recive una entidad FS , libera su memoria y despues la crea devuelta, habia que ver sino inicilizarla[EN PROCESO TODAVIA LE FALTA]
//free(fileSystem);

	FILESYSTEM = inicializarFs(fdArchConfig);
	return FILESYSTEM;
}

void crearCarpeta( int dirPadre, char* nombre) {
	element* carpeta;
	carpeta = crearElemento();
	carpeta->directorioPadre = dirPadre;
	carpeta->index;	// = habira que generar una funcion que devuelva el index correspondiente en base al directorio padre en el que se agrega la carpeta
FILESYSTEM->listaDirectorios = list_add(FILESYSTEM->listaDirectorios, carpeta);
}

/*---------------------------------------------------------------*/


int main(int argc, char **argv) {

	char * archivoEstructura;
	int fdArchivo;
	int fdEstructura;
	int fdArchConfig;
	char* dirArchivo = "/tmp/archivoProcesar.txt";
	char* dirArchivoEstructura = "/tmp/archivoEstructura.txt";
	char* ptrContenidoBloques;
	char* dirArchivoConfig;

    fdArchConfig = open(dirArchivoConfig, O_RDONLY);
	fdArchivo = open(dirArchivo, O_RDWR);
	fdEstructura = open(dirArchivoEstructura, O_RDWR | O_CREAT);

     inicializarFS(fdArchConfig);
	ptrContenidoBloques = string_split(fdArchivo, "/n");

	return 0;

}
