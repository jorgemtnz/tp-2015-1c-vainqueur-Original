#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <src/commons/string.h>
#include <src/commons/collections/list.h>
#include <src/commons/txt.h>
#include "filesystem.h"
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include "mapeoAMemoria.h"

int  main(int argc, char **argv) {

	char * archivoEstructura;
		int fdArchivo;
		int fdEstructura;
		char* dirArchivo = "/tmp/archivoProcesar.txt";
		char* dirArchivoEstructura = "/tmp/archivoEstructura.txt";
		char* ptrContenidoBloques;

		fdArchivo = open(dirArchivo, O_RDWR);
		fdEstructura = open(dirArchivoEstructura, O_RDWR | O_CREAT);



		 ptrContenidoBloques = string_split(fdArchivo, "/n");

		return 0;

}



/*-------------------FUNCIONES DE CONSOLA------------------------*/

void agregarN(fs* fileSystem ,char* nombre){
	 nod* nodo;
	 nodo = crearNodo(nombre);//se usa el constructor para crear el nodo
	list_add(fileSystem.listaNodos,nodo);//agrega al nodo a la lista de nodos del FS
	agregarDir(fileSystem->listaDirectorios,nodo->nombre);//se agrega un dir con el nombre del nodo

}

void eliminarN(fs* fileSystem, char* nombre){//faltaria la condicion pero nose como ponerla
	list_remove_by_condition(fileSystem->listaNodos));//remueve de la lista el nodo que concuerda con el nombre ingresado eso creo
}

fs formatear(fs* fileSystem){//recive una entidad FS , libera su memoria y despues la crea devuelta, habia que ver sino inicilizarla
	free(fileSystem);
	fs* fileSystem;
	inicilizarFs(fileSystem);
return fileSystem;
}

/*---------------------------------------------------------------*/

/*------------------FUNCIONES CONSTRUCTORAS----------------------*/

nod* crearNodo(char* nombre){//constructor del nodo
	nod* nodo = malloc(sizeof(nod));
	strcpy(nodo->nombre,nombre);//le pongo nombre al nodo
	nodo->estado = 0; // pongo en estado operativo
	nodo->tamanio = 2;
	nodo->listaBloques = bloq* list_create();//creamos lista de bloques
	cargarBloques(nodo->listaBloques);//carga 102 bloques
	nodo->ptrSgt;//nose si hay que ponerle =NULL
return nodo;
}

bloq* crearBloque(){//constructor del bloque
	bloq* bloque = malloc(sizeof(bloq));
	bloque->nombre = NULL;
	bloque->nombreArchivo = NULL;
	bloque->nombreDirectorio = NULL;
	bloque->tamanio = 20971520;//20 mb
	bloque->ptrSgt;
return bloque;
}

element* crearElemento(int identificadorCarpetaOArchivo){

	if (identificadorCarpetaOArchivo==0){//carga los parametros en NULL menos elemento y le asigan el que corresponde (FALTA)
		element* archivo = malloc(sizeof(element));
		archivo->elemento = 0;//es el identificador que se lo reconoce como archivo
		archivo->directorioPadre = NULL;
		archivo->index = NULL;



	}
}
fs* inicilizarFS(int archivoConfig){//entra como parametro el fd del archivo config(CONSTRUCTOR DEL FS)
	fs* fileSystem = malloc(sizeof(fs));
	fileSystem->estado = 0;//creo que 0 era disponible sino lo cambiamos
	fileSystem->listaNodos = nod* list_create();
return fileSystem;//retorna el fs
}

/*-----------------------------------------------------------------------*/

/*------------------------FUNCIONES DESTRUCTORAS-------------------------*/
void destruirBloque(bloq* bloque){//libera memoria del tipo bloque
	free(bloque->nombre);
	free(bloque->nombreArchivo);
	free(bloque->nombreDirectorio);
	free(bloque->tamanio);
	free(bloque->ptrSgt);
}

void destruirNodo(nod* nodo){//libera la memoria del nodo
	free(nodo->estado);
	free(nodo->nombre);
	free(nodo->tamanio);
	list_clean_and_destroy_elements(nodo->listaBloques,(bloq* bloque));//falta ver bien como se escribe esta funcion pero tendria que vaciar la lista de blqoues de un nodo
}



/*-----------------------------------------------------------------------*/

/*------------------------FUNCIONES AUXILIARES---------------------------*/
void cargarBloques(bloq* listaBloques){
	for(int i=0;i<=102;i++){//ciclo de for para cargar los 102 bloques
		bloq* bloque;//varaible para almacenar el bloque creado
		bloque = crearBloque();//crea el bloque
		list_add(listaBloques, bloque);//lo agrega a la lista
	}

}

void leerRegistro(int arch, fs* fileSystem){
  read(arch,fileSystem,sizeof(fs));//lee el archivo y pone la estructura en la estructura fs

}

void guardarRegistro(int arch,fs* fileSystem){//esto mientras este el archivo abierto sino lo abrimos aca

  write(arch,fileSystem,sizeof(fs));//le paso el registro fileSystem,y el archivo y lo escribe
}

/*----------------------------------------------------------------------*/
