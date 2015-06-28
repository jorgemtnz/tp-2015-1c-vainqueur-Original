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
#include <pthread.h>
#include <semaphore.h>

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
// Funciones Constructoras hace el malloc de la estrutura e inicializa
t_nodo* crearNodo();

// Funciones Destructoras  libera con free la estructura solamente
void liberaMemoriaNodo();

// Funciones Auxiliares recorre la lista y va liberando elemento por elemento mediante la func_destructura
void liberaMemoriaLista(t_list* lista, int* cantElementos,
		void (*funcionLiberaElemento)(void*)) ;

//nodoFunciones
void levantarArchivoConfiguracion(); //levanta configuración y se lo pasa a las variables globales
int informarEjecucionAJob(t_nodo* datosDelNodo,
		char* ipJob, int puertoJob,	int comoTerminoLaEjecucion);//le contesta al job como fue el trabajo realizado
int ejecutarReduce(int soportaCombiner); // Falta implementar
int ejecutarMap(char * nombreArchivoTemporal, char * ptrDireccionMapeo);// esta función ejecuta el map sobre un <<--ver observacion en .c
void conectarNodo(t_nodo* datosDelNodo); //se conecta el nodo al filesystem
bufferVeinteMegas* getBloque(int numeroDeBloque); // devuelve un bloque determinado devuelve un puntero al buffer echo con malloc, se debe hacer luego el free
int setBloque(int numeroDeBloque, bufferVeinteMegas buffer) ;//pone un la info de un bloque en el archivo
char* getFileContent(char* nombreDelArchivo) ; //devuelve archivo del tmp

// +++++++++++++++++++++++++++++++++++ Variables Globales +++++++++++++++++++++++++++++++++++
int vg_puerto_FS,
	vg_nodo_Nuevo,
	vg_puerto_Nodo;

char *vg_ip_FS;
char *vg_archivo_Bin;
char	 *vg_dirTemp;
char	 *vg_ip_Nodo;

#endif /* NODO2_SRC_NODO_H_ */
