#ifndef NODO2_SRC_NODO_H_
#define NODO2_SRC_NODO_H_

// +++++++++++++++++++++++++++++++++++++++ Includes +++++++++++++++++++++++++++++++++++++
#include <stdio.h>
#include <stdlib.h>
#include <sockets/sockets.h>
#include <redireccionIO/redireccionIO.h>
#include <string.h>
#include <src/commons/config.h>

// +++++++++++++++++++++++++++++++++++++++ Define +++++++++++++++++++++++++++++++++++++
#define RUTACONFIGNODO "/home/utnso/TPOperativos/nodo/Adicionales/CONFIGURACION.cfg"
#define RUTAMAP "blabl/blabla"
#define EJECUCIONOK 1
#define EJECUCIONFALLO -1
#define NODO_NUEVO 1
#define NODO_NO_NUEVO 0

// +++++++++++++++++++++++++++++++++++++++ Estructuras +++++++++++++++++++++++++++++++++++++
typedef struct nodo {
	int idNodo;
	int esNuevo; 	// 1 si es nuevo, 0 si no;
	short estado; 	//1 disponible, 0 ocupado;
	void * bloques;
} nodo_t;

// +++++++++++++++++++++++++++++++++++++++ Prototipos +++++++++++++++++++++++++++++++++++++
void* getBloque(int numeroBloque);	// Falta implementar
void* setBloque();					// Falta implementar
void* getFileContent();				// Falta implementar

// Nodo.c
void levantarArchivoConfiguracion();
int informarEjecucionAJob(nodo_t* datosDelNodo,
		char* ipJob, int puertoJob,	int comoTerminoLaEjecucion);
int ejecutarReduce(int soportaCombiner); // Falta iplementar
int ejecutarMap(char * nombreArchivoTemporal, char * ptrDireccionMapeo);
void conectarNodo(nodo_t* datosDelNodo);
//main

// Funciones Constructoras

// Funciones Destructoras

// Funciones Auxiliares

// +++++++++++++++++++++++++++++++++++ Variables Globales +++++++++++++++++++++++++++++++++++
int vg_puerto_FS,
	vg_nodo_Nuevo,
	vg_puerto_Nodo;

char *vg_ip_FS;
char *vg_archivo_Bin;
char	 *vg_dirTemp;
char	 *vg_ip_Nodo;

#endif /* NODO2_SRC_NODO_H_ */
