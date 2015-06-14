/*
 * job.h
 *
 *  Created on: 14/6/2015
 *      Author: utnso
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <commons/config.h>
#include <commons/collections/list.h>

typedef struct SolicitudDeTrabajo{
	char* archvATrabajar;
	char* funcion;
	int combiner;
}SolicitudDeTrabajo;

typedef struct RelacionNodoBloque{
	int numeroNodo;
	int numeroBloque;

}RelacionNodoBloque;

typedef struct RealcionNodoArchTemp{
	int numeroNodo;
	char* nombreArchvTemp;
}RelacionNodoArchTemp;

typedef struct TareaMap{//cada tarea asemeja a un hilo (en este caso hiloMapper)
	int fdHilo;
	t_list* listaRelacionNodoBloque;
	char* dirMapExec;
}TareaMap;

typedef struct TareaReduce{
	int fdHilo;
	t_list* listaRelacionNodoArchTemp;
	char* dirReduceExec;
}TareaReduce;

typedef struct Job {
	t_list* listasTareasMap;
	t_list* listasTareasReduce;
	SolicitudDeTrabajo* solicitud;
	char* dirArchvConfig;
};
