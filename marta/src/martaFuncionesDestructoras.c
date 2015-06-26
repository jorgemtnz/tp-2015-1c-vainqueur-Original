#include "marta.h"

void liberaMemoriaArchivoProcesado(t_archivoProcesado* ptrArchivoProcesado) {
	// free(&ptrArchivoProcesado->aplicoMapper);	Es un int
	// free(&ptrArchivoProcesado->estado);			Es un int
	// free(&ptrArchivoProcesado->numeroNodo);		Es un int
	free(ptrArchivoProcesado->ubicacion);
	free(ptrArchivoProcesado->nombreArchProcesado);
	free(ptrArchivoProcesado);
}

void liberaMemoriaRelacionNodoBloque(t_relacionNodoBloque* ptrRelacionNodoBloque) {
	// free(&ptrRelacionNodoBloque->estado);		Es un int
	// free(&ptrRelacionNodoBloque->numeroBloque);	Es un int
	// free(&ptrRelacionNodoBloque->numeroNodo);	Es un int
	free(ptrRelacionNodoBloque);
}

void liberaMemoriaUbicacionBloque(t_ubicacionBloque* ptrUbicacionBloque) {
	// free(&ptrUbicacionBloque->numero);			Es un int
	list_destroy_and_destroy_elements(ptrUbicacionBloque->listaRelacionesNodoBloque,
									  liberaMemoriaRelacionNodoBloque);
	free(ptrUbicacionBloque);
}

void liberaMemoriaInformacionArchivo(t_informacionDelArchivo* ptrInformacionArchivo) {
	// free(&ptrInformacionArchivo->enUso);		Es un int
	free(ptrInformacionArchivo->nombreArchivo);
	list_destroy_and_destroy_elements(ptrInformacionArchivo->listaUbicacionBloques,
									  liberaMemoriaInformacionArchivo);
	free(ptrInformacionArchivo);
}

void liberaMemoriaNombreFuncion(t_nombreFuncion ptrNombreFuncion) {
	free(ptrNombreFuncion);
}

void liberaMemoriaSolicitud(t_solicitud* ptrSolicitud) {
	// free(&ptrSolicitud->estado);				Es un int
	// free(&ptrSolicitud->soportaCombiner);	Es un int
	free(ptrSolicitud->nombreArchivoATrabajar);
	list_destroy_and_destroy_elements(ptrSolicitud->listaNombresFunciones,
									  liberaMemoriaSolicitud);
	free(ptrSolicitud);
}

void liberaMemoriaMarta(t_estructuraMarta* ptrMarta) {
	list_destroy_and_destroy_elements(ptrMarta->listaArchivosProcesados,
									  liberaMemoriaArchivoProcesado);
	list_destroy_and_destroy_elements(ptrMarta->listaInformacionDelArchivo,
									  liberaMemoriaInformacionArchivo);
	list_destroy_and_destroy_elements(ptrMarta->listaSolicitudes,
									  liberaMemoriaSolicitud);
	free(ptrMarta);
}

void liberaVG(){
	free(vg_ipFilesystem);
}
