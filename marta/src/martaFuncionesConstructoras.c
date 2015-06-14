#include "marta.h"
typedef struct archivoProcesado {
	char * nombreArchProcesado;
	int numeroNodo;
	char * ubicacion;
	int aplicoMapper; //Si = 1 / No = 0
	int estado;
} t_archivoProcesado;
t_archivoProcesado* crearArchivoProcesado() {
	t_archivoProcesado* ptrArchivoProcesado;
	if (malloc(sizeof(t_archivoProcesado)) == NULL) {
		perror(
				"No se aloco memoria para RelacionNodoBloque pertenece a la estructura "
						"Marta>..>ubicacionBloque>listaArchivoProcesado>ArchivoProcesado");
		exit(-1);
	}else{
		ptrArchivoProcesado->aplicoMapper=NO;
		ptrArchivoProcesado->estado=NO_MAPEADO;
		ptrArchivoProcesado->nombreArchProcesado='\0';
		ptrArchivoProcesado->numeroNodo=0;
		ptrArchivoProcesado->ubicacion='\0';
		return ptrArchivoProcesado;
	}
}

t_relacionNodoBloque* crearRelacionNodoBloque() {
	t_relacionNodoBloque* ptrRelacionNodoBloque;
	if (malloc(sizeof(t_ubicacionBloque)) == NULL) {
		perror(
				"No se aloco memoria para RelacionNodoBloque pertenece a la estructura "
						"Marta>..>ubicacionBloque>listaRelacionNodoBloque>RelacionNodoBloque");
		exit(-1);
	} else {
		ptrRelacionNodoBloque->estado = 0;
		ptrRelacionNodoBloque->numeroBloque = 0;
		ptrRelacionNodoBloque->numeroNodo = 0;
		return ptrRelacionNodoBloque;
	}
}

t_ubicacionBloque* crearUbicacionBloque() {
	t_ubicacionBloque* ptrUbicacionBloque;
	if (malloc(sizeof(t_ubicacionBloque)) == NULL) {
		perror(
				"No se aloco memoria para ubicacionArchivo pertenece a la estructura "
						"Marta>..>listaUbicacionBloque>ubicacionBloque");
		exit(-1);
	} else {
		ptrUbicacionBloque->numero = 0;
		ptrUbicacionBloque->listaRelacionesNodoBloque = list_create();
		return ptrUbicacionBloque;
	}
}

t_informacionDelArchivo* crearInformacionArchivo() {
	t_informacionDelArchivo* ptrInformacionArchivo;
	if (malloc(sizeof(t_informacionDelArchivo)) == NULL) {
		perror(
				"No se aloco memoria para informacionArchivo pertenece a la estructura "
						"Marta>listaInformacionArchivo");
		exit(-1);
	} else {
		ptrInformacionArchivo->enUso = NO;
		ptrInformacionArchivo->nombreArchivo = '\0';
		ptrInformacionArchivo->listaUbicacionBloques = list_create();

		return ptrInformacionArchivo;
	}
}

t_nombreFuncion* crearNombreFuncion() {

	t_nombreFuncion* ptrNombreFuncion;

	if (malloc(sizeof(t_nombreFuncion)) == NULL) {
		perror(
				"No se aloco memoria para nombreFuncion pertenece a la estructura "
						"Marta>listaSolicitudes>Solicitud>NombreFuncion");
		exit(-1);
	} else
		return ptrNombreFuncion;
}

t_solicitud* crearSolicitud() {
	t_solicitud* ptrSolicitud;
	if (malloc(sizeof(t_solicitud)) == NULL) {
		perror(
				"No se aloco memoria para estructura solicitud pertenece a la estructura "
						"Marta>listaSolicitudes>Solicitud");
		exit(-1);
	} else {
		ptrSolicitud->estado = EN_ESPERA;
		ptrSolicitud->listaNombresFunciones = list_create();
		ptrSolicitud->nombreArchivoATrabajar = '\0';
		ptrSolicitud->soportaCombiner = NO;
		return ptrSolicitud;
	}

}

t_estructuraMarta* crearMarta() {
	t_estructuraMarta* ptrMarta;
	if (malloc(sizeof(t_estructuraMarta)) == NULL) {
		perror("No se aloco memoria para estructura marta");
		exit(-1);
	} else {

		ptrMarta->listaArchivosProcesados = list_create();
		ptrMarta->listaInformacionDelArchivo = list_create();
		ptrMarta->listaSolicitudes = list_create();
		return marta;
	}

	return ptrMarta;
}

