#include"job.h"

void liberaMemoriaSolicitudDeTrabajo(t_solicitudDeTrabajo* ptrSolicitudDeTrabajo) {

	free(&ptrSolicitudDeTrabajo->archvATrabajar);
	free(&ptrSolicitudDeTrabajo->combiner);
	free(&ptrSolicitudDeTrabajo->t_mapper);
	free(&ptrSolicitudDeTrabajo->t_reduce);
	free(ptrSolicitudDeTrabajo);
}

void liberaMemoriaRelacionNodoBloque(t_relacionNodoBloque* ptrRelacionNodoBloque) {

	free(&ptrRelacionNodoBloque->numeroBloque);
	free(&ptrRelacionNodoBloque->numeroNodo);
	free(ptrRelacionNodoBloque);
}

void liberaMemoriaRelacionNodoArchTemp(t_relacionNodoArchTemp* ptrRelacionNodoArchTemp) {

	free(&ptrRelacionNodoArchTemp->nombreArchvTemp);
	free(&ptrRelacionNodoArchTemp->numeroNodo);
	free(ptrRelacionNodoArchTemp);
}

void liberaMemoriaTareaMap(t_tareaMap* ptrTareaMap) {

	free(&ptrTareaMap->dirMapExec);
	free(&ptrTareaMap->fdHilo);
	liberaMemoriaLista(ptrTareaMap->listaRelacionNodoBloque,
			&(ptrTareaMap->listaRelacionNodoBloque->elements_count),
			liberaMemoriaRelacionNodoBloque);
	free(ptrTareaMap);
}

void liberaMemoriaTareaReduce(t_tareaReduce* ptrTareaReduce) {

	free(&ptrTareaReduce->dirReduceExec);
	free(&ptrTareaReduce->fdHilo);
	liberaMemoriaLista(ptrTareaReduce->listaRelacionNodoArchTemp,
			&(ptrTareaReduce->listaRelacionNodoArchTemp->elements_count),
			liberaMemoriaRelacionNodoArchTemp);
	free(ptrTareaReduce);
}

void liberaMemoriaJob(t_job* ptrJob) {

	liberaMemoriaLista(ptrJob->listaSolicitudDeTrabajo,
			&(ptrJob->listaSolicitudDeTrabajo->elements_count),
			liberaMemoriaSolicitudDeTrabajo);
	liberaMemoriaLista(ptrJob->listasTareasMap,
			&(ptrJob->listasTareasMap->elements_count), liberaMemoriaTareaMap);
	liberaMemoriaLista(ptrJob->listasTareasReduce,
			&(ptrJob->listasTareasReduce->elements_count),
			liberaMemoriaTareaReduce);
	free(ptrJob);

}

void liberarMemoriaVG(){
	free(vg_archivos);
	free(vg_ipMarta);
	free(vg_mapperPath);
	free(vg_reducerPath);
	free(vg_resultado);
	// vg_combiner y vg_puertoMarta no lo libero porque son int
}
