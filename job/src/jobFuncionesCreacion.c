#include"job.h"

t_solicitudDeTrabajo* crearSolicitudDeTrabajo() {
	t_solicitudDeTrabajo* ptrSolicitudDeTrabajo;

	if (malloc(sizeof(t_solicitudDeTrabajo)) == NULL) {
		perror(
				"No se aloco memoria para SolicitudDeTrabajo pertenece a la estructura "
						"Job>..>SolicitudDeTrabajo");
		exit(-1);
	} else {
		ptrSolicitudDeTrabajo->combiner= NO;
		ptrSolicitudDeTrabajo->archvATrabajar='\0';
		ptrSolicitudDeTrabajo->funcion='\0';
		return ptrSolicitudDeTrabajo;
	}
}
