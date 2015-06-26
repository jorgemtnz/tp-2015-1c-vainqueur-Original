#include "filesystem.h"

/*------------------------FUNCIONES DESTRUCTORAS-------------------------*/
void liberaMemoriaBloque(bloq* bloque) { //libera memoria del tipo bloque
	// free(&bloque->numero);	Es un int
	// free(&bloque->tamanio);	Es un int
	free(bloque);
}

void liberaMemoriaNodo(nod* nodo) { //libera la memoria del nodo
	// free(&nodo->estado);		Es un int
	// free(&nodo->numero);		Es un int
	free(nodo->dirEspacioNodo);
	list_destroy_and_destroy_elements(nodo->listaBloques,
									  liberaMemoriaBloque);
	free(nodo);
}

void liberaNodoBloque(nodBloq* nodoBloque) {
	// free(nodoBloque->numeroBloque);	Es un int
	// free(nodoBloque->numeroCopia);	Es un int
	// free(nodoBloque->numeroNodo);	Es un int
	free(nodoBloque);					// Liberad es un struct
}

void liberaMemoriaElement(element* elemento) {
	// free(&(elemento->directorioPadre));	Es un int
	// free(&(elemento->tipoElemento));		Es un int
	// free(&(elemento->estado));			Es un int
	// free(&(elemento->index));			Es un int
	// free(&(elemento->tamanio));			Es un int
	free(elemento->nombre);
	list_destroy_and_destroy_elements(elemento->listaNodoBloque,
									  liberaNodoBloque);
	free(elemento);
}

void liberaMemoriaFS() {
	// free(&FILESYSTEM->espacioDisponible);	Es un int
	// free(&FILESYSTEM->estado);				Es un int
	free(FILESYSTEM->ipNodos);

	list_destroy_and_destroy_elements(FILESYSTEM->listaNodosConectados,
									  liberaMemoriaNodo);
	list_destroy_and_destroy_elements(FILESYSTEM->listaElementos,
									  liberaMemoriaElement);
	free(FILESYSTEM);
}
