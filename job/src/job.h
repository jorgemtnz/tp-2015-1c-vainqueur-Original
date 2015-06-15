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
#include <src/commons/collections/list.h>
#include <src/commons/temporal.h>
#include <src/commons/string.h>
#include <src/commons/txt.h>
#include <src/commons/config.h>
#include <src/commons/collections/list.h>

// +++++++++++++++++++++++++++++++++++++++ Define +++++++++++++++++++++++++++++++++++++
#define SI 1
#define NO 0
#define RUTACONFIGJOB "/"
#define ACEPTA_COMBINER 1
#define NO_ACEPTA_COMBINER 0

// +++++++++++++++++++++++++++++++++++++++ Estructuras +++++++++++++++++++++++++++++++++++++
typedef struct SolicitudDeTrabajo{
	char* archvATrabajar;
	char* funcion;
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
}r_tareaMap;

typedef struct TareaReduce{
	int fdHilo;
	t_list* listaRelacionNodoArchTemp;
	char* dirReduceExec;
}t_tareaReduce;

typedef struct Job {
	t_list* listasTareasMap;
	t_list* listasTareasReduce;
	t_solicitudDeTrabajo* solicitud;
	char* dirArchvConfig;
}t_job;

// +++++++++++++++++++++++++++++++++++++++ Prototipos +++++++++++++++++++++++++++++++++++++
// Funciones Constructoras
t_solicitudDeTrabajo* crearSolicitudDeTrabajo();
t_relacionNodoBloque* crearRelacionNodoBloque();
t_relacionNodoArchTemp* crearRelacionNodoArchTemp(); // Falta implementar

// Funciones Destructoras

// Funciones Auxiliares
void leerArchivoDeConfiguracion(char* nomArchivo);
void liberaMemoriaLista(t_list* lista, int* cantElementos, void (*funcionLiberaElemento)(void*));

// +++++++++++++++++++++++++++++++++++ Variables Globales +++++++++++++++++++++++++++++++++++
// El archivo config de job tiene IP_MARTA PUERTO_MARTA MAPPER REDUCE COMBINER ARCHIVOS RESULTADO
char* vg_ipMarta;
int vg_puertoMarta;
int vg_combiner;
char** vg_archivos; 	// Array de strings
char* vg_resultado; 	// String de ruta del archivo resultante
char* vg_mapperPath; 	// Ruta del archivo mapper
char* vg_reducerPath; 	// Ruta del reducer


#endif /* JOB_H_ */





















