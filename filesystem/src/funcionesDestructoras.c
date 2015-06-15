#include "filesystem.h"

/*------------------------FUNCIONES DESTRUCTORAS-------------------------*/
void liberaMemoriaLista(t_list* lista, int* cantElementos, void (*funcionLiberaElemento)(void*)) {
	int i = 0;
	for (; i <= *cantElementos; i++) {
		list_destroy_and_destroy_elements(lista, (void*) funcionLiberaElemento);
	}// Consultar el index i

}

void liberaMemoriaBloque(bloq* bloque) { //libera memoria del tipo bloque
	free(&bloque->numero);
	free(&bloque->tamanio);
	free(bloque);
}

void liberaMemoriaNodo(nod* nodo) { //libera la memoria del nodo
	free(&nodo->estado);
	free(&nodo->numero);
	free(&nodo->dirEspacioNodo);
	liberaMemoriaLista(nodo->listaBloques,nodo->listaBloques->elements_count,(void*) liberaMemoriaBloque);
	free(nodo);
}

void liberaNodoBloque(nodBloq* nodoBloque) {
	free(&(nodoBloque->numeroBloque));
	free(&(nodoBloque->numeroCopia));
	free(&(nodoBloque->numeroNodo));
	free(nodoBloque);
}

void liberaMemoriaElement(element* elemento) {
	free(&(elemento->directorioPadre));
	free(&(elemento->tipoElemento));
	free(&(elemento->estado));
	free(&(elemento->index));
	free(&(elemento->nombre));
	free(&(elemento->tamanio));
	liberaMemoriaLista(elemento->listaNodoBloque,elemento->listaNodoBloque->elements_count,(void*) liberaNodoBloque);
	free(elemento);
}

void liberaMemoriaFS() {
	free(&FILESYSTEM->espacioDisponible);
	free(&FILESYSTEM->estado);
	liberaMemoriaLista(FILESYSTEM->listaNodosConectados,FILESYSTEM->listaNodosConectados->elements_count,(void*) liberaMemoriaNodo);
	liberaMemoriaLista(FILESYSTEM->listaElementos,FILESYSTEM->listaElementos->elements_count,(void*) liberaMemoriaElement);
	free(&FILESYSTEM->ipNodos);
	free(FILESYSTEM);
}
