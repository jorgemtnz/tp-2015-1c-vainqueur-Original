#include "marta.h"

void liberaMemoriaArchivoProcesado(t_archivoProcesado* ptrArchivoProcesado) {
	free(ptrArchivoProcesado->ubicacion);
	free(ptrArchivoProcesado->nombreArchProcesado);
	free(ptrArchivoProcesado);
}

void liberaMemoriaRelacionNodoBloque(
		t_relacionNodoBloque* ptrRelacionNodoBloque) {
	free(ptrRelacionNodoBloque);
}

void liberaMemoriaUbicacionBloque(t_ubicacionBloque* ptrUbicacionBloque) {

	list_destroy_and_destroy_elements(
			ptrUbicacionBloque->listaRelacionesNodoBloque,
			(void*) liberaMemoriaRelacionNodoBloque);
	free(ptrUbicacionBloque);
}

void liberaMemoriaInformacionArchivo(
		t_informacionDelArchivo* ptrInformacionArchivo) {
	free(ptrInformacionArchivo->nombreArchivo);
	list_destroy_and_destroy_elements(
			ptrInformacionArchivo->listaUbicacionBloques,
			(void*) liberaMemoriaInformacionArchivo);
	free(ptrInformacionArchivo);
}

void liberaMemoriaNombreFuncion(char* ptrNombreFuncion) {
	free(ptrNombreFuncion);
}

void liberaMemoriaSolicitud(t_solicitud* ptrSolicitud) {
	free(ptrSolicitud->nombreArchivoATrabajar);
	list_destroy_and_destroy_elements(ptrSolicitud->listaNombresFunciones,
			(void*)liberaMemoriaSolicitud);
	free(ptrSolicitud);
}

void liberaMemoriaMarta(t_estructuraMarta* ptrMarta) {
	list_destroy_and_destroy_elements(ptrMarta->listaArchivosProcesados,
			(void*)liberaMemoriaArchivoProcesado);
	list_destroy_and_destroy_elements(ptrMarta->listaInformacionDelArchivo,
			(void*)liberaMemoriaInformacionArchivo);
	list_destroy_and_destroy_elements(ptrMarta->listaSolicitudes,
			(void*)liberaMemoriaSolicitud);
	free(ptrMarta);
}

void liberaVG() {
	free(vg_ipFilesystem);
}
