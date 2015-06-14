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
	free(&ptrRelacionNodoBloque);
}

void liberaMemoriaUbicacionBloque(t_ubicacionBloque* ptrUbicacionBloque) {
	free(&ptrUbicacionBloque->numero);
	liberaMemoriaLista(ptrUbicacionBloque->listaRelacionesNodoBloque,
			ptrUbicacionBloque->listaRelacionesNodoBloque->elements_count,
			(void*) liberaMemoriaRelacionNodoBloque);

}

