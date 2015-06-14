#include"job.h"

t_solicitudDeTrabajo* crearSolicitudDeTrabajo() {
	t_solicitudDeTrabajo* ptrSolicitudDeTrabajo;
	ptrSolicitudDeTrabajo = malloc(sizeof(t_solicitudDeTrabajo));

	if (ptrSolicitudDeTrabajo == NULL) {
		perror("[ERROR] No se aloco memoria para SolicitudDeTrabajo pertenece a la estructura "
						"Job>..>SolicitudDeTrabajo");
		exit(-1);
	}

	ptrSolicitudDeTrabajo->combiner = NO;
	ptrSolicitudDeTrabajo->archvATrabajar = '\0';
	ptrSolicitudDeTrabajo->funcion = '\0';
	return ptrSolicitudDeTrabajo;

}

t_relacionNodoBloque* crearRelacionNodoBloque() {
	t_relacionNodoBloque* ptrRelacionNodoBloque;
	ptrRelacionNodoBloque = malloc(sizeof(t_relacionNodoBloque));

	if (ptrRelacionNodoBloque == NULL) {
		perror("[ERROR] No se aloco memoria para RelacionNodoBloque pertenece a la estructura "
						"Job>..>RelacionNodoBloque");
		exit(-1);
	}

	ptrRelacionNodoBloque->numeroBloque = 0;
	ptrRelacionNodoBloque->numeroNodo   = 0;
	return ptrRelacionNodoBloque;
	}

t_relacionNodoArchTemp* crearRelacionNodoArchTemp() {
	t_relacionNodoArchTemp* ptrRelacionNodoArchTemp;
	ptrRelacionNodoArchTemp = malloc(sizeof(t_relacionNodoBloque));

	if(ptrRelacionNodoArchTemp == NULL){
		perror("[ERROR] No se aloco memoria para RelacionNodoArchTemp pertenece a la estructura "
				"Job>..>RelacionNodoArchTemp");
		exit(-1);
	}
}

