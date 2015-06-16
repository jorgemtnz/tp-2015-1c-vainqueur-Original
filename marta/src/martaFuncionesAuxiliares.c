#include "marta.h"

void liberaMemoriaLista(t_list* lista, int* cantElementos,
		void (*funcionLiberaElemento)(void*)) {
	int posicion;
	for (posicion = 0; posicion <= *cantElementos; posicion++) {
		list_remove_and_destroy_element(lista, posicion, funcionLiberaElemento);
	}

}

