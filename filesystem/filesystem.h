/*
 * filesystem.h
 *
 *  Created on: 11/5/2015
 *      Author: utnso
 */

#ifndef FILESYSTEM_H_
#define FILESYSTEM_H_

#include <commons/collections/list.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <src/commons/string.h>
#include <src/commons/txt.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define FILESYSTEM_H_
#define ESDIRECTORIO 1
#define ESARCHIVO 0
#define FSOPERATIVO 1
#define FSNOOPERATIVO 0
#define NODOOPERATIVO 1
#define NODONOOPERATIVO 0
#define NUMEROBLOQUES 102


//bloque
typedef struct bloq {
	int nombre;
	int nombreDirectorio;
	char nombreArchivo[25];
	int tamanio;
	 //	struct bloq* ptrSgt;[LAS FUNCIONES DE LISTAS DE LAS COMMONS SE VAN A ENCARGAR DE CREAR LOS PUNTEROS]
} bloq;
// Archivo

//nodo
typedef struct nod {
	char* nombre;
	int estado;
	int tamanio;
	t_list* listaBloques; //del nodo
	char* ptrdirEspacioNodo;
	// struct nod* ptrSgt; [LAS FUNCIONES DE LISTAS DE LAS COMMONS SE VAN A ENCARGAR DE CREAR LOS PUNTEROS]
} nod;
typedef struct nodBloq {
	int numeroCopia;
	int numeroNodo;
	int numeroBloque;
} nodBloq;

typedef struct element {
	char* nombre;
	int estado;
	int index;
	int tamanio;
	int directorioPadre;
	int elemento; //1 para directorio, 0 para archivo o documento.
	t_list* listaNodoBloque; //hacer lista nodo/bloque(ponerle si en el nombre si es copia:int 0-n o no)
//struct element* ptrSgt;[LAS FUNCIONES DE LISTAS DE LAS COMMONS SE VAN A ENCARGAR DE CREAR LOS PUNTEROS]
} element;
//fylesystem Estructura principal
typedef struct fs {
	int estado;
	t_list* listaNodos; //lista nodos conectados
	t_list* listaDirectorios;
	int espacioDisponible;
} fs;

fs* FILESYSTEM;
// persistencia del estado del filesystem se hará en un archivo, piente usar commons/list.h para manejar listas
//pendiente usar funciones para manejar archivos, se deben crear. No estan en las commons.
void formatear(int fdArchConfig);
void crearCarpeta( int dirPadre, char* nombre);
void eliminarN(char* nombre) ;
void agregarN(char* nombre) ;
void guardarRegistro(int arch);
void leerRegistro(int arch) ;
void cargarBloques(t_list *listaBloques);
void destruirNodo(nod* nodo) ;
void destruirBloque(bloq* bloque) ;
fs* crearFileSystem() ;
element* crearElemento();
bloq* crearBloque();
nod* crearNodo(char* nombre) ;

#endif /* FILESYSTEM_H_ */
