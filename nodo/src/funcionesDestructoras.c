#include "nodo.h"



void liberaMemoriaNodo(t_nodo* ptrNodo){
	free(&ptrNodo->esNuevo);
	free(&ptrNodo->idNodo);
	free(ptrNodo);
}
