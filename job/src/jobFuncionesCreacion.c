#include"job.h"

t_solicitudDeTrabajo* crearSolicitudDeTrabajo() {
	t_solicitudDeTrabajo* ptrSolicitudDeTrabajo;

	if (malloc(sizeof(t_solicitudDeTrabajo)) == NULL) {
		perror(
				"No se aloco memoria para SolicitudDeTrabajo pertenece a la estructura "
						"Job>..>SolicitudDeTrabajo");
		exit(-1);
	} else {
		ptrSolicitudDeTrabajo->combiner = NO;
		ptrSolicitudDeTrabajo->archvATrabajar = '\0';
		ptrSolicitudDeTrabajo->funcion = '\0';
		return ptrSolicitudDeTrabajo;
	}
}

t_relacionNodoBloque* crearRelacionNodoBloque() {
	t_relacionNodoBloque* ptrRelacionNodoBloque;

	if (malloc(sizeof(t_relacionNodoBloque)) == NULL) {
		perror(
				"No se aloco memoria para RelacionNodoBloque pertenece a la estructura "
						"Job>..>RelacionNodoBloque");
		exit(-1);
	} else {
		ptrRelacionNodoBloque->numeroBloque = 0;
		ptrRelacionNodoBloque->numeroNodo = 0;
		return ptrRelacionNodoBloque;
	}

}

t_relacionNodoArchTemp* crearRelacionNodoArchTemp() {
	t_relacionNodoArchTemp relacionNodoArchTemp;
	if(malloc(sizeof(t_relacionNodoBloque))==NULL){

	}
}

