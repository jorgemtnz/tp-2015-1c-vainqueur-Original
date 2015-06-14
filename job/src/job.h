#ifndef JOB_H_
#define JOB_H_
#define SI 1
#define NO 0


//----- include----
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>  // read write
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <commons/collections/list.h>
#include <commons/temporal.h>
#include <src/commons/string.h>
#include <src/commons/txt.h>
#include <commons/config.h>
#include <commons/collections/list.h>

//---funciones de creacion


//---fin funciones de creacion


//--- funciones de destruccion



//--- fin funciones de destruccion


//----funciones auxiliares
void liberaMemoriaLista(t_list* lista, int* cantElementos,
		void (*funcionLiberaElemento)(void*));

//---- fin funciones auxiliares



//-----variables globales
// no puedo tener una variable global de toda la estructura porque hay varias instancias

//----fin variables globales


//----estructura-------


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

typedef struct TareaMap{//cada tarea asemeja a un hilo (en este caso hiloMapper)
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
};


//-------fin estructura-----

#endif /* JOB_H_ */
