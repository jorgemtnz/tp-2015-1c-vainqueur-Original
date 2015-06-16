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

// +++++++++++++++++++++++++++++++++++++++ Estructuras +++++++++++++++++++++++++++++++++++++
typedef struct {
	char* nombre;
	char* direccion;

}t_Resultado_Parcial;
typedef struct nodo {
	int idNodo;
	int esNuevo; 	// 1 si es nuevo, 0  no;
	short estado; 	//1 disponible, 0 ocupado; ->jorge:-> consulto:es disponible cuando?  yo no lo eh creado, ni liberado
	void * bloques;
	char* dirArchivoDiscoDuro;
	t_list* listaResultadosParciales;

} t_nodo;

// +++++++++++++++++++++++++++++++++++++++ Prototipos +++++++++++++++++++++++++++++++++++++
void* getBloque(int numeroBloque);	// Falta implementar
void* setBloque();					// Falta implementar
void* getFileContent();				// Falta implementar

//main

// Funciones Constructoras
t_Resultado_Parcial* crearResultado();
t_nodo* crearNodo();

// Funciones Destructoras
void liberaMemoriaResultadoParcial();
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

char *vg_ip_FS,
	 *vg_archivo_Bin,
	 *vg_dirTemp,
	 *vg_ip_Nodo;

#endif /* NODO2_SRC_NODO_H_ */
