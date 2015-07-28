#include "filesystem.h"

/*------------------------FUNCIONES DESTRUCTORAS-------------------------*/
void liberaMemoriaBloque(bloq* bloque) { //libera memoria del tipo bloque
	free(bloque);
}

void liberaMemoriaNodo(nod* nodo) { //libera la memoria del nodo
		list_destroy_and_destroy_elements(nodo->listaBloques,
				(void*) liberaMemoriaBloque);
	free(nodo);
}

void liberaNodoBloque(ubicacionDelBloqueEnNodo* nodoBloque) {
	free(nodoBloque);					// Liberad es un struct
}

void liberaMemoriaElement(element* elemento) {
	free(elemento->nombre);
list_destroy_and_destroy_elements(elemento->dobleListaUbicacionDelBloqueEnNodo,
								  (void*)liberaNodoBloque);
	free(elemento);
}

void liberaMemoriaFS() {

		list_destroy_and_destroy_elements(FILESYSTEM->listaNodos,
			(void*) liberaMemoriaNodo);
	list_destroy_and_destroy_elements(FILESYSTEM->listaElementos,
			(void*)liberaMemoriaElement);
	free(FILESYSTEM);
}
