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
#include <src/commons/log.h>
#include <pthread.h>
#include <semaphore.h>
#include <mapeoAMemoria/mapeoAMemoria.h>
// +++++++++++++++++++++++++++++++++++++++ Define +++++++++++++++++++++++++++++++++++++
#define SI 1
#define NO 0
#define RUTACONFIGJOB "/"
#define ACEPTA_COMBINER 1
#define NO_ACEPTA_COMBINER 0
#define PUERTO_JOB 7898
#define CANTIDAD_JOBS_ACEPTADOS 2
#define TAMANIOBUFFER 130
#define DIR_REDUCE "/tmp/"
#define DIR_MAPP "/tmp/"
#define LONGPATH 200
#define HILOS_A_LANZAR 5
//-------tp nuevo-------
#define BUF_SIZE 50
#define BUF_ARCH 4096
#define MAPPER_SIZE 4096
t_log* logger;
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
	t_list* listaSolicitudDeTrabajo;
	// son solicitudes porque  job  pide a marta varias,
	// sobre diferentes archivos
}t_job;
//++++++++++++++++++++++++++++++++++++struct hilo mapper++++++++++++++++++++++++++++++++++++
typedef struct estructura_mapper {
	char ip_nodo[20];
	int puerto_nodo;
	int bloque;
	char nombreArchivoTemporal[100];
} __attribute__((packed)) t_mapper;
// +++++++++++++++++++++++++++++++++++++++ Prototipos +++++++++++++++++++++++++++++++++++++
// Funciones Creacion    todas ellas crean con malloc la estructura y la inicializan con valores
t_solicitudDeTrabajo* crearSolicitudDeTrabajo();
t_relacionNodoBloque* crearRelacionNodoBloque();
t_relacionNodoArchTemp* crearRelacionNodoArchTemp();
t_tareaMap* crearTareaMap();
t_tareaReduce* creaTareaReduce() ;
t_job* crearJob();


// Funciones Destruccion  se hace el free de los que ya se hizo el malloc
void liberaMemoriaSolicitudDeTrabajo(t_solicitudDeTrabajo* ptrSolicitudDeTrabajo) ;
void liberaMemoriaRelacionNodoBloque(t_relacionNodoBloque* ptrRelacionNodoBloque) ;
void liberaMemoriaRelacionNodoArchTemp(t_relacionNodoArchTemp* ptrRelacionNodoArchTemp) ;
void liberaMemoriaTareaMap(t_tareaMap* ptrTareaMap) ;
void liberaMemoriaTareaReduce(t_tareaReduce* ptrTareaReduce) ;
void liberaMemoriaJob(t_job* ptrJob) ;
void liberarMemoriaVG();

// Funciones Auxiliares
void leerArchivoDeConfiguracion();
void testleerArchivoDeConfiguracion();
void conectarConMarta();
void sendTamanioDe(char* cadena);
void* indicarArchivosAMarta();
void testleerArchivoDeConfiguracion();
//++++++++++++++++++++++funciones tp n+++++++++++++++++++++++++++++++++++++++++++++++++++++
void* hilo_mapper(t_mapper*);
char* getFileContent(char*);

// +++++++++++++++++++++++++++++++++++ Variables Globales +++++++++++++++++++++++++++++++++++

// El archivo config de job tiene IP_MARTA PUERTO_MARTA MAPPER REDUCE COMBINER ARCHIVOS RESULTADO
int	   vg_puertoMarta;
int	   vg_combiner;		// ACEPTA_COMBINER = 1 ; NO_ACEPTA_COMBINER = 0
int    vg_fdJob;
int    vg_PuertoNodo;
char* vg_ipNodo;
char*  vg_ipMarta;
char** vg_archivos; 		// Array de strings
char*  vg_resultado; 	// String de ruta del archivo resultante
char*  vg_mapperPath; 	// Ruta del archivo mapper
char*  vg_reducerPath; 	// Ruta del reducer
char*   vg_nombreArchivoConfigJob;
t_log* logger; //VG del logger

#endif /* JOB_H_ */
