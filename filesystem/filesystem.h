/*
 * filesystem.h
 *
 *  Created on: 11/5/2015
 *      Author: utnso
 */

#ifndef FILESYSTEM_H_
#define FILESYSTEM_H_

#endif /* FILESYSTEM_H_ */

//bloque
typedef struct bloq {
	int nombre;
	int nombreDirectorio;
	char nombreArchivo[25];
	int tamanio;
	struct bloq* ptrSgt; //[LAS FUNCIONES DE LISTAS DE LAS COMMONS SE VAN A ENCARGAR DE CREAR LOS PUNTEROS]
} bloq;
// Archivo

//nodo
typedef struct nod {
	char nombre[25];
	int estado;
	int tamanio;
	bloq* listaBloques; //del nodo
	//char* ptrdirEspacioNodo;[LAS FUNCIONES DE LISTAS DE LAS COMMONS SE VAN A ENCARGAR DE CREAR LOS PUNTEROS]
	struct nod* ptrSgt;
} nod;
typedef struct nodBloq {
	int numeroCopia;
	int numeroNodo;
	int numeroBloque;
} nodBloq;

typedef struct element {
	char nombre[25];
	int estado;
	int index;
	int tamanio;
	int directorioPadre;
	int elemento; //1 para directorio, 0 para archivo o documento.
	nodBloq* listaNodoBloque; //hacer lista nodo/bloque(ponerle si en el nombre si es copia:int 0-n o no)
//struct element* ptrSgt;[LAS FUNCIONES DE LISTAS DE LAS COMMONS SE VAN A ENCARGAR DE CREAR LOS PUNTEROS]
} element;
//fylesystem Estructura principal
typedef struct fs {
	int estado;
	nod* listaNodos; //lista nodos conectados
	element* listaDirectorios;
	int espacioDisponible;
} fs;
// persistencia del estado del filesystem se hará en un archivo, piente usar commons/list.h para manejar listas
//pendiente usar funciones para manejar archivos, se deben crear. No estan en las commons.
