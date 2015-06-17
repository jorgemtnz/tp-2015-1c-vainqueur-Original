#include "nodo.h"

t_Resultado_Parcial* crearResultadoParcial() {
	t_Resultado_Parcial* ptrResultadoParcial;
	ptrResultadoParcial = malloc(sizeof(t_Resultado_Parcial));
	if (ptrResultadoParcial == NULL) {
		perror(
				"[ERROR] No se aloco memoria para ResultadoParcial pertenece a la estructura "
						"Nodo>..>ResultadoParcial");
		exit(-1);
	} else {
		ptrResultadoParcial->direccion = '\0';
		ptrResultadoParcial->nombre = '\0';
	}

	return ptrResultadoParcial;
}

t_nodo* crearNodo() {
	t_nodo* ptrNodo;
	ptrNodo = malloc(sizeof(t_nodo));
	if (ptrNodo == NULL) {
		perror(
				"[ERROR] No se aloco memoria para Nodo pertenece a la estructura "
						"Nodo");
		exit(-1);
	} else {
		ptrNodo->dirArchivoDiscoDuro = '\0';
		ptrNodo->esNuevo = NODO_NUEVO;
		ptrNodo->estado = 1;
		ptrNodo->idNodo = 0;
		ptrNodo->listaResultadosParciales = list_create();
	}

	return ptrNodo;
}

