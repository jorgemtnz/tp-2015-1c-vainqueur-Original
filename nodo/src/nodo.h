#ifndef NODO2_SRC_NODO_H_
#define NODO2_SRC_NODO_H_

// +++++++++++++++++++++++++++++++++++++++ Includes +++++++++++++++++++++++++++++++++++++
#include <stdio.h>
#include <stdlib.h>
#include <redireccionIO/redireccionIO.h>
#include <string.h>
#include <unistd.h>  // read write
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sockets/sockets.h>
#include <src/commons/temporal.h>
#include <src/commons/string.h>
#include <src/commons/txt.h>
#include <src/commons/config.h>
#include <src/commons/collections/list.h>

// +++++++++++++++++++++++++++++++++++++++ Define +++++++++++++++++++++++++++++++++++++
#define RUTACONFIGNODO "/home/utnso/TPOperativos/nodo/Adicionales/CONFIGURACION.cfg"
#define RUTAMAP "/tmp/"
#define EJECUCIONOK 1
#define EJECUCIONFALLO -1
#define NODO_NUEVO 1
#define NODO_NO_NUEVO 0
#define VEINTEMEGAS 20971520

// +++++++++++++++++++++++++++++++++++++++ Estructuras +++++++++++++++++++++++++++++++++++++

typedef struct nodo {
	int idNodo;
	int esNuevo; 	// 1 si es nuevo, 0  no;
	char* dirArchivoDiscoDuro;

} t_nodo;

typedef char bufferTemp;
typedef char bufferVeinteMegas [VEINTEMEGAS];//bufer de 20 megas que devolvera contenido del bloque
// +++++++++++++++++++++++++++++++++++++++ Prototipos +++++++++++++++++++++++++++++++++++++
bufferVeinteMegas getBloque( int nuemeroDeBloque);
int setloque(int nuemeroDeBloque, bufferVeinteMegas buffer);
bufferTemp getFileContent(char* nombreDelArchivo);

//main

// Funciones Constructoras
t_nodo* crearNodo();

// Funciones Destructoras
void liberaMemoriaNodo();

// Funciones Auxiliares
void liberaMemoriaLista(t_list* lista, int* cantElementos,
		void (*funcionLiberaElemento)(void*)) ;

//nodoFunciones
void levantarArchivoConfiguracion();
int informarEjecucionAJob(t_nodo* datosDelNodo,
		char* ipJob, int puertoJob,	int comoTerminoLaEjecucion);
int ejecutarReduce(int soportaCombiner); // Falta iplementar
int ejecutarMap(char * nombreArchivoTemporal, char * ptrDireccionMapeo);
void conectarNodo(t_nodo* datosDelNodo);

// +++++++++++++++++++++++++++++++++++ Variables Globales +++++++++++++++++++++++++++++++++++
int vg_puerto_FS,
	vg_nodo_Nuevo,
	vg_puerto_Nodo;

char *vg_ip_FS;
char *vg_archivo_Bin;
char	 *vg_dirTemp;
char	 *vg_ip_Nodo;

#endif /* NODO2_SRC_NODO_H_ */
