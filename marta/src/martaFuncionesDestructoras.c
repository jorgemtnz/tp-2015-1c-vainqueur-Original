#include "marta.h"

void liberaMemoriaArchivoProcesado(t_archivoProcesado* ptrArchivoProcesado) {
	free(ptrArchivoProcesado->ubicacion);
	free(ptrArchivoProcesado->nombreArchProcesado);
	free(ptrArchivoProcesado);
}

void liberaMemoriaRelacionNodoBloque(t_relacionNodoBloque* ptrRelacionNodoBloque) {
	free(ptrRelacionNodoBloque);
}

void liberaMemoriaUbicacionBloque(t_ubicacionBloque* ptrUbicacionBloque) {

	list_destroy_and_destroy_elements(ptrUbicacionBloque->listaRelacionesNodoBloque,
									  liberaMemoriaRelacionNodoBloque);
	free(ptrUbicacionBloque);
}

void liberaMemoriaInformacionArchivo(t_informacionDelArchivo* ptrInformacionArchivo) {
		free(ptrInformacionArchivo->nombreArchivo);
	list_destroy_and_destroy_elements(ptrInformacionArchivo->listaUbicacionBloques,
									  liberaMemoriaInformacionArchivo);
	free(ptrInformacionArchivo);
}

void liberaMemoriaNombreFuncion(t_nombreFuncion ptrNombreFuncion) {
	free(ptrNombreFuncion);
}

void liberaMemoriaSolicitud(t_solicitud* ptrSolicitud) {
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
