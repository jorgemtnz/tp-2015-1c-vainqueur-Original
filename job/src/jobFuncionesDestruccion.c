#include"job.h"

// Observacion General: Para todas las funciones que hay aca, no entiendo porque
// liberan memoria de elementos que no son dinamicos (por ejemplo un int).
// Con cariño Lucas

void liberaMemoriaSolicitudDeTrabajo(t_solicitudDeTrabajo* ptrSolicitudDeTrabajo) {
	//free(&ptrSolicitudDeTrabajo->combiner); Es un int
	free(&ptrSolicitudDeTrabajo->archvATrabajar);
	free(&ptrSolicitudDeTrabajo->t_mapper);
	free(&ptrSolicitudDeTrabajo->t_reduce);
	free(ptrSolicitudDeTrabajo);
}

void liberaMemoriaRelacionNodoBloque(t_relacionNodoBloque* ptrRelacionNodoBloque) {
//	free(&ptrRelacionNodoBloque->numeroBloque); Es un int
//	free(&ptrRelacionNodoBloque->numeroNodo);	Es un int
	free(ptrRelacionNodoBloque);				// Libero, es un struct
}

void liberaMemoriaRelacionNodoArchTemp(t_relacionNodoArchTemp* ptrRelacionNodoArchTemp) {
	// free(&ptrRelacionNodoArchTemp->numeroNodo); Es un int
	free(&ptrRelacionNodoArchTemp->nombreArchvTemp);
	free(ptrRelacionNodoArchTemp);
}

void liberaMemoriaTareaMap(t_tareaMap* ptrTareaMap) {
	// free(&ptrTareaMap->fdHilo); Es un int
	free(&ptrTareaMap->dirMapExec);
	list_destroy_and_destroy_elements(ptrTareaMap->listaRelacionNodoBloque,
									  liberaMemoriaRelacionNodoBloque);
	free(ptrTareaMap);
}

void liberaMemoriaTareaReduce(t_tareaReduce* ptrTareaReduce) {
	// free(&ptrTareaReduce->fdHilo); Es un int
	free(&ptrTareaReduce->dirReduceExec);
	list_destroy_and_destroy_elements(ptrTareaReduce->listaRelacionNodoArchTemp,
									  liberaMemoriaRelacionNodoArchTemp);
	free(ptrTareaReduce);
}

void liberaMemoriaJob(t_job* ptrJob) {
	free(ptrJob->dirArchvConfig);
	list_destroy_and_destroy_elements(ptrJob->listaSolicitudDeTrabajo,
									  liberaMemoriaSolicitudDeTrabajo);
	list_destroy_and_destroy_elements(ptrJob->listasTareasMap,
									  liberaMemoriaTareaMap);
	list_destroy_and_destroy_elements(ptrJob->listasTareasReduce,
									  liberaMemoriaTareaReduce);
	free(ptrJob);
}

void liberarMemoriaVG(){
	// vg_combiner y vg_puertoMarta no lo libero porque son int
	free(vg_archivos);
	free(vg_ipMarta);
	free(vg_mapperPath);
	free(vg_reducerPath);
	free(vg_resultado);
}
