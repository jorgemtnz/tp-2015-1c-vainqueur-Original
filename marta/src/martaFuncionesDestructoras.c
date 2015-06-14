#include "marta.h"

void liberaMemoriaArchivoProcesado(t_archivoProcesado* ptrArchivoProcesado) {
	free(&ptrArchivoProcesado->aplicoMapper);
	free(&ptrArchivoProcesado->estado);
	free(&ptrArchivoProcesado->nombreArchProcesado);
	free(&ptrArchivoProcesado->numeroNodo);
	free(&ptrArchivoProcesado->ubicacion);
	free(ptrArchivoProcesado);
}

void liberaMemoriaRelacionNodoBloque(
		t_relacionNodoBloque* ptrRelacionNodoBloque) {
	free(&ptrRelacionNodoBloque->estado);
	free(&ptrRelacionNodoBloque->numeroBloque);
	free(&ptrRelacionNodoBloque->numeroNodo);
	free(ptrRelacionNodoBloque);
}

void liberaMemoriaUbicacionBloque(t_ubicacionBloque* ptrUbicacionBloque) {
	free(&ptrUbicacionBloque->numero);
	liberaMemoriaLista(ptrUbicacionBloque->listaRelacionesNodoBloque,
			ptrUbicacionBloque->listaRelacionesNodoBloque->elements_count,
			(void*)liberaMemoriaRelacionNodoBloque);
	free(ptrUbicacionBloque);
}

void liberaMemoriaInformacionArchivo(
		t_informacionDelArchivo* ptrInformacionArchivo) {
	free(&ptrInformacionArchivo->enUso);
	free(&ptrInformacionArchivo->nombreArchivo);
	liberaMemoriaLista(ptrInformacionArchivo->listaUbicacionBloques,
			ptrInformacionArchivo->listaUbicacionBloques->elements_count,
			(void*) liberaMemoriaInformacionArchivo);
	free(ptrInformacionArchivo);
}

void liberaMemoriaNombreFuncion(t_nombreFuncion* ptrInformacionArchivo) {
	free(ptrInformacionArchivo);
}

void liberaMemoriaSolicitud(t_solicitud* ptrSolicitud) {
	free(&ptrSolicitud->estado);
	free(&ptrSolicitud->nombreArchivoATrabajar);
	free(&ptrSolicitud->soportaCombiner);
	liberaMemoriaLista(ptrSolicitud->listaNombresFunciones,
			ptrSolicitud->listaNombresFunciones->elements_count,
			(void*) liberaMemoriaSolicitud);

	free(ptrSolicitud);
}

void liberaMemoriaMarta(t_estructuraMarta* ptrMarta) {
	liberaMemoriaLista(ptrMarta->listaArchivosProcesados,
			ptrMarta->listaArchivosProcesados->elements_count,
			(void*) liberaMemoriaArchivoProcesado);
	liberaMemoriaLista(ptrMarta->listaInformacionDelArchivo,
			ptrMarta->listaInformacionDelArchivo->elements_count,
			(void*) liberaMemoriaInformacionArchivo);
	liberaMemoriaLista(ptrMarta->listaSolicitudes,
			ptrMarta->listaSolicitudes->elements_count,
			(void*) liberaMemoriaSolicitud);
	free(ptrMarta);
}
