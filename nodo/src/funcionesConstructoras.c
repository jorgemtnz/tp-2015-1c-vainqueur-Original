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

		int numNodo; // y luego cuando lo lo quiero agregar entonces lo pongo como nodo conectado

		printf("Ingrese el numero de nodo: ");
		fflush(stdin);
		scanf("%d", &numNodo);
		ptrNodo->esNuevo = NODO_NUEVO;
		ptrNodo->idNodo = numNodo;
		ptrNodo->dirArchivoDiscoDuro = '\0';
	}

	return ptrNodo;
}

