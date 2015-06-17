#include "nodo.h"

void liberaMemoriaResultadoParcial(){
	t_Resultado_Parcial* ptrResultadoParcial;
	free(&ptrResultadoParcial->direccion);
	free(&ptrResultadoParcial->nombre);
	free(ptrResultadoParcial);
}

void liberaMemoriaNodo(){
	t_nodo* ptrNodo;

	free(&ptrNodo->dirArchivoDiscoDuro);
free(&ptrNodo->esNuevo);
free(&ptrNodo->estado);
free(&ptrNodo->idNodo);
liberaMemoriaLista(ptrNodo->listaResultadosParciales,
		&(ptrNodo->listaResultadosParciales->elements_count), liberaMemoriaResultadoParcial);
free(&ptrNodo->listaResultadosParciales);
free(ptrNodo);
}
