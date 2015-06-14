#include"job.h"

void liberaMemoriaLista(t_list* lista, int* cantElementos,
		void (*funcionLiberaElemento)(void*)) {
	int i = 0;
	for (; i <= *cantElementos; i++) {
		list_destroy_and_destroy_elements(lista, (void*) funcionLiberaElemento);
	}

}
