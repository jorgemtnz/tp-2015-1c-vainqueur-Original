#include "nodo.h"



t_nodo* crearNodo() {
	t_nodo* ptrNodo;
	ptrNodo = malloc(sizeof(t_nodo));
	if (ptrNodo == NULL) {
		perror(
				"[ERROR] No se aloco memoria para Nodo pertenece a la estructura "
						"Nodo");
		exit(-1);
	} else {
		ptrNodo->esNuevo = NODO_NUEVO;
		ptrNodo->idNodo = 0;
	}

	return ptrNodo;
}

