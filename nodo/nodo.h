/*
 * nodo.h
 *
 *  Created on: 13/6/2015
 *      Author: utnso
 */

#ifndef NODO_H_
#define NODO_H_

#include <stdio.h>
#include <stdlib.h>
#include <sockets/sockets.h>
#include <redireccionIO/redireccionIO.h>
#include <string.h>
#include <src/commons/config.h>

#define RUTACONFIGNODO "/"
#define RUTAMAP "blabl/blabla"
#define EJECUCIONOK 1
#define EJECUCIONFALLO -1
#define NODO_NUEVO 1
#define NODO_NO_NUEVO 0



typedef struct nodo {
	int idNodo;
	int esNuevo; // 1 si es nuevo, 0 si no;
	short estado; //1 disponible, 0 ocupado;
	void * bloques;

} nodo_t;

// Variables Globales

// Archivo Config
int *vg_puerto_FS,
	*vg_nodo_Nuevo,
	*vg_puerto_Nodo;

char **vg_ip_FS,
	 **vg_archivo_Bin,
	 **vg_dirTemp,
	 **vg_ip_Nodo; // ** puntero a string
// Fin archivo config


// Prototipos
void* getBloque(int numeroBloque);
void* setBloque();
void* getFileContent();


#endif /* NODO_H_ */
