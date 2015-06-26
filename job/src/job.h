#ifndef JOB_H_
#define JOB_H_

// +++++++++++++++++++++++++++++++++++++++ Includes +++++++++++++++++++++++++++++++++++++
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>  // read write
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sockets/sockets.h>
#include <src/commons/collections/list.h>
#include <src/commons/temporal.h>
#include <src/commons/string.h>
#include <src/commons/txt.h>
#include <src/commons/config.h>
#include <src/commons/collections/list.h>
#include <pthread.h>

// +++++++++++++++++++++++++++++++++++++++ Define +++++++++++++++++++++++++++++++++++++
#define SI 1
#define NO 0
#define RUTACONFIGJOB "/"
#define ACEPTA_COMBINER 1
#define NO_ACEPTA_COMBINER 0
#define PUERTO_JOB 7898
#define CONEXIONES_ACEPTA_JOB 1 // Marta
#define TAMANIOBUFFER 130
#define DIR_REDUCE "/tmp/"
#define DIR_MAPP "/tmp/"
#define DIR_ARCH_CONFIG "/tmp"
#define LONGPATH 200
#define HILOS_A_LANZAR 5

// +++++++++++++++++++++++++++++++++++++++ Estructuras +++++++++++++++++++++++++++++++++++++
typedef struct SolicitudDeTrabajo{
	char* archvATrabajar;
	char* t_mapper;  //el job le dice a marta que quiere hacer varios trabajos sobre un archivo
	char* t_reduce;
	int combiner; // SI 1 NO 0
}t_solicitudDeTrabajo;

typedef struct RelacionNodoBloque{
	int numeroNodo;
	int numeroBloque;

}t_relacionNodoBloque;

typedef struct RealcionNodoArchTemp{
	int numeroNodo;
	char* nombreArchvTemp;
}t_relacionNodoArchTemp;

typedef struct TareaMap{ //cada tarea asemeja a un hilo (en este caso hiloMapper)
	int fdHilo;
	t_list* listaRelacionNodoBloque;
	char* dirMapExec;
}t_tareaMap;

typedef struct TareaReduce{
	int fdHilo;
	t_list* listaRelacionNodoArchTemp;
	char* dirReduceExec;
}t_tareaReduce;

typedef struct Job {
	t_list* listasTareasMap;
	t_list* listasTareasReduce;
	t_list* listaSolicitudDeTrabajo;   //son solicitudes porque  job  pide a marta varias, sobre diferentes archivos
	char* dirArchvConfig;
}t_job;

// +++++++++++++++++++++++++++++++++++++++ Prototipos +++++++++++++++++++++++++++++++++++++
// Funciones Constructoras
t_solicitudDeTrabajo* crearSolicitudDeTrabajo();
t_relacionNodoBloque* crearRelacionNodoBloque();
t_relacionNodoArchTemp* crearRelacionNodoArchTemp();
t_tareaMap* crearTareaMap();
t_tareaReduce* creaTareaReduce() ;
t_job* crearJob();


// Funciones Destructoras  <<<----------- Ver Observaciones en .c
void liberaMemoriaSolicitudDeTrabajo(t_solicitudDeTrabajo* ptrSolicitudDeTrabajo) ;
void liberaMemoriaRelacionNodoBloque(t_relacionNodoBloque* ptrRelacionNodoBloque) ;
void liberaMemoriaRelacionNodoArchTemp(t_relacionNodoArchTemp* ptrRelacionNodoArchTemp) ;
void liberaMemoriaTareaMap(t_tareaMap* ptrTareaMap) ;
void liberaMemoriaTareaReduce(t_tareaReduce* ptrTareaReduce) ;
void liberaMemoriaJob(t_job* ptrJob) ;
void liberarMemoriaVG();

// Funciones Auxiliares
void leerArchivoDeConfiguracion();
void liberaMemoriaLista(t_list* lista, int* cantElementos, void (*funcionLiberaElemento)(void*));
void borrarBarraEneAString(char* cadena);

// +++++++++++++++++++++++++++++++++++ Variables Globales +++++++++++++++++++++++++++++++++++

// El archivo config de job tiene IP_MARTA PUERTO_MARTA MAPPER REDUCE COMBINER ARCHIVOS RESULTADO
int	  vg_puertoMarta;
int	  vg_combiner;		// ACEPTA_COMBINER = 1 ; NO_ACEPTA_COMBINER = 0
char* vg_ipMarta;
char* vg_archivos; 		// Array de strings
char* vg_resultado; 	// String de ruta del archivo resultante
char* vg_mapperPath; 	// Ruta del archivo mapper
char* vg_reducerPath; 	// Ruta del reducer


#endif /* JOB_H_ */
