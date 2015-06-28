#include"job.h"

void liberaMemoriaSolicitudDeTrabajo(t_solicitudDeTrabajo* ptrSolicitudDeTrabajo) {
	//free(&ptrSolicitudDeTrabajo->combiner); Es un int
	free(&ptrSolicitudDeTrabajo->archvATrabajar);
	free(&ptrSolicitudDeTrabajo->t_mapper);
	free(&ptrSolicitudDeTrabajo->t_reduce);
	free(ptrSolicitudDeTrabajo);
}

void liberaMemoriaRelacionNodoBloque(t_relacionNodoBloque* ptrRelacionNodoBloque) {
	free(ptrRelacionNodoBloque);				// Libero, es un struct
}

void liberaMemoriaRelacionNodoArchTemp(t_relacionNodoArchTemp* ptrRelacionNodoArchTemp) {
	free(&ptrRelacionNodoArchTemp->nombreArchvTemp);
	free(ptrRelacionNodoArchTemp);
}

void liberaMemoriaTareaMap(t_tareaMap* ptrTareaMap) {
	free(&ptrTareaMap->dirMapExec);
	list_destroy_and_destroy_elements(ptrTareaMap->listaRelacionNodoBloque,
									  (void*) liberaMemoriaRelacionNodoBloque);
	free(ptrTareaMap);
}

void liberaMemoriaTareaReduce(t_tareaReduce* ptrTareaReduce) {
	free(&ptrTareaReduce->dirReduceExec);
	list_destroy_and_destroy_elements(ptrTareaReduce->listaRelacionNodoArchTemp,
									  (void*) liberaMemoriaRelacionNodoArchTemp);
	free(ptrTareaReduce);
}

void liberaMemoriaJob(t_job* ptrJob) {

	list_destroy_and_destroy_elements(ptrJob->listaSolicitudDeTrabajo,
									  (void*) liberaMemoriaSolicitudDeTrabajo);
	list_destroy_and_destroy_elements(ptrJob->listasTareasMap,
								      (void*) liberaMemoriaTareaMap);
	list_destroy_and_destroy_elements(ptrJob->listasTareasReduce,
									  (void*) liberaMemoriaTareaReduce);
	free(ptrJob);
}

void liberarMemoriaVG(){
	// vg_combiner y vg_puertoMarta no lo libero porque son int
	free(vg_archivos);
	free(vg_ipMarta);
	free(vg_mapperPath);
	free(vg_reducerPath);
	free(vg_resultado);
}//  <<---- consulta, porque se hace un free si no se hizo antes un malloc
