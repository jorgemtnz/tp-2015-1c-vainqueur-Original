#include <stdlib.h>
#include <stdio.h>
#include <string.h>

//bloque
typedef struct bloq {
	char nombre[25];
	char nombreDirectorio[25];
	char nombreArchivo[25];
	int tamanio;
	struct bloq* ptrSgt;
} bloq;
// Archivo
typedef struct archiv {
	int estado;
	int tamanio;
	char nombre[25];
	char directorioPadre[25];
	bloq listaBloques;
	int estado;
	int tamanio;
	struct archiv* ptrSgt;
} archiv;
//directorio
typedef struct direct {
	char nombre[25];
	char directorioPadre[25];
	int index;
	archiv listaArchivos;
	struct direct* ptrSgt;
} direct;
//nodo
typedef struct nod {
	char nombre[25];
	int estado;
	int tamanio;
	bloq listaBloques;
	struct nod* ptrSgt;
} nod;
//fylesystem Estructura principal
typedef struct fs {
	int estado;
	nod listaNodos;
	direct listaDirectorios;
} fs;
// persistencia del estado del filesystem se hará en un archivo, piente usar commons/list.h para manejar listas
//pendiente usar funciones para manejar archivos, se deben crear. No estan en las commons.
