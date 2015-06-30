#include "filesystem.h"

/*------------------------FUNCIONES DESTRUCTORAS-------------------------*/
void liberaMemoriaBloque(bloq* bloque) { //libera memoria del tipo bloque
	free(bloque);
}

void liberaMemoriaNodo(nod* nodo) { //libera la memoria del nodo
	free(nodo->dirEspacioNodo);
	list_destroy_and_destroy_elements(nodo->listaBloques,
									  liberaMemoriaBloque);
	free(nodo);
}

void liberaNodoBloque(ubicacionDelBloqueEnNodo* nodoBloque) {
	free(nodoBloque);					// Liberad es un struct
}

void liberaMemoriaElement(element* elemento) {
	free(elemento->nombre);
list_destroy_and_destroy_elements(elemento->dobleListaUbicacionDelBloqueEnNodo,
								  liberaNodoBloque);
	free(elemento);
}

void liberaMemoriaFS() {

	free(FILESYSTEM->ipNodos);

	list_destroy_and_destroy_elements(FILESYSTEM->listaNodosConectados,
									  liberaMemoriaNodo);
	list_destroy_and_destroy_elements(FILESYSTEM->listaElementos,
									  liberaMemoriaElement);
	free(FILESYSTEM);
}
