#include"job.h"

t_solicitudDeTrabajo* crearSolicitudDeTrabajo() {
	t_solicitudDeTrabajo* ptrSolicitudDeTrabajo;
	ptrSolicitudDeTrabajo = malloc(sizeof(t_solicitudDeTrabajo));

	if (ptrSolicitudDeTrabajo == NULL) {
		perror(
				"[ERROR] No se aloco memoria para SolicitudDeTrabajo pertenece a la estructura "
						"Job>..>SolicitudDeTrabajo");
		exit(-1);
	} else {

		ptrSolicitudDeTrabajo->combiner = NO;
		ptrSolicitudDeTrabajo->archvATrabajar = '\0';
		ptrSolicitudDeTrabajo->t_mapper = "mapper";
		ptrSolicitudDeTrabajo->t_reduce = "reduce";
	}
	return ptrSolicitudDeTrabajo;

}

t_relacionNodoBloque* crearRelacionNodoBloque() {
	t_relacionNodoBloque* ptrRelacionNodoBloque;
	ptrRelacionNodoBloque = malloc(sizeof(t_relacionNodoBloque));

	if (ptrRelacionNodoBloque == NULL) {
		perror(
				"[ERROR] No se aloco memoria para RelacionNodoBloque pertenece a la estructura "
						"Job>..>RelacionNodoBloque");
		exit(-1);
	} else {

		ptrRelacionNodoBloque->numeroBloque = 0;
		ptrRelacionNodoBloque->numeroNodo = 0;

	}
	return ptrRelacionNodoBloque;
}

t_relacionNodoArchTemp* crearRelacionNodoArchTemp() {

	t_relacionNodoArchTemp* ptrRelacionNodoArchTemp;
	ptrRelacionNodoArchTemp = malloc(sizeof(t_relacionNodoBloque));

	if (ptrRelacionNodoArchTemp == NULL) {
		perror(
				"[ERROR] No se aloco memoria para RelacionNodoArchTemp pertenece a la estructura "
						"Job>..>RelacionNodoArchTemp");
		exit(-1);
	} else {
		ptrRelacionNodoArchTemp->numeroNodo = 0;
		ptrRelacionNodoArchTemp->nombreArchvTemp = '\0';

	}
	return ptrRelacionNodoArchTemp;

}

t_tareaMap* crearTareaMap() {
	t_tareaMap* ptrTareaMap;
	ptrTareaMap = malloc(sizeof(t_tareaMap));
	if (ptrTareaMap == NULL) {
		perror(
				"[ERROR] No se aloco memoria para TareaMap pertenece a la estructura "
						"Job>..>TareaMap");
		exit(-1);

	} else {
		ptrTareaMap->fdHilo = 0;
		ptrTareaMap->dirMapExec = DIR_MAPP;
		ptrTareaMap->listaRelacionNodoBloque = list_create();
	}
	return ptrTareaMap;
}

t_tareaReduce* creaTareaReduce() {
	t_tareaReduce* ptrTareaReduce;
	ptrTareaReduce = malloc(sizeof(t_tareaReduce));
	if (ptrTareaReduce == NULL) {
		perror(
				"[ERROR] No se aloco memoria para TareaReduce pertenece a la estructura "
						"Job>..>TareaReduce");
		exit(-1);
	} else {
		ptrTareaReduce->dirReduceExec = DIR_REDUCE;
		ptrTareaReduce->fdHilo = 0;
		ptrTareaReduce->listaRelacionNodoArchTemp = list_create();
	}
	return ptrTareaReduce;
}

t_job* crearJob() {
	t_job* ptrJob;
	ptrJob = malloc(sizeof(t_job));
	if (ptrJob == NULL) {
		perror(
				"[ERROR] No se aloco memoria para Job pertenece a la estructura "
						"Job");
		exit(-1);
	} else {
		ptrJob->dirArchvConfig = DIR_ARCH_CONFIG;
		ptrJob->listasTareasMap = list_create();
		ptrJob->listasTareasReduce = list_create();
		ptrJob->listaSolicitudDeTrabajo = list_create();
	}
	return ptrJob;

}
