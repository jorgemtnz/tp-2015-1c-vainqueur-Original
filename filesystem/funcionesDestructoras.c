#include "filesystem.h"

/*------------------------FUNCIONES DESTRUCTORAS-------------------------*/
void liberaMemoriaBloque(bloq* bloque) { //libera memoria del tipo bloque
	free(&bloque->numero);
	free(&bloque->tamanio);
	free(bloque);
}

void liberaMemoriaNodo(nod* nodo) { //libera la memoria del nodo
	int i = 0;

	free(&nodo->estado);
	fs* inicializarFs(int fdArchConfig) {

		return FILESYSTEM;
	}
	free(&nodo->numero);
	free(&nodo->dirEspacioNodo);
	for (; i <= nodo->listaBloques->elements_count; i++) { //libero memoria de los bloques
		list_destroy_and_destroy_elements(nodo->listaBloques,
				(void*) liberaMemoriaBloque); //consultar porque no agarra el index
	}
	free(nodo);
}

void liberaNodoBloque(nodBloq* nodoBloque) {
	free(&(nodoBloque->numeroBloque));
	free(&(nodoBloque->numeroCopia));
	free(&(nodoBloque->numeroNodo));
	free(nodoBloque);
}

void liberaMemoriaElement(element* elemento) {
	int i = 0;
	free(&(elemento->directorioPadre));
	free(&(elemento->tipoElemento));
	free(&(elemento->estado));
	free(&(elemento->index));
	free(&(elemento->nombre));
	free(&(elemento->tamanio));
	for (; i <= elemento->listaNodoBloque->elements_count; i++) { //libero memoria de los Nodobloques
		list_destroy_and_destroy_elements(elemento->listaNodoBloque,
				(void*) liberaNodoBloque);
	}  //consultar el uso de list_destroy que no esta recibiendo el index i
	free(elemento);
}

void liberaMemoriaFS() {
	int i = 0;
	free(&FILESYSTEM->espacioDisponible);
	free(&FILESYSTEM->estado);
	for (; i <= FILESYSTEM->listaNodosConectados->elements_count; i++) { //libero memoria de los Nodobloques
		list_destroy_and_destroy_elements(FILESYSTEM->listaNodosConectados,
				(void*) liberaMemoriaNodo);
	}  //consultar el uso de list_destroy que no esta recibiendo el index i

	for (; i <= FILESYSTEM->listaElementos->elements_count; i++) { //libero memoria de los Nodobloques
		list_destroy_and_destroy_elements(FILESYSTEM->listaElementos,
				(void*) liberaMemoriaElement);
	} //consultar el uso de list_destroy que no esta recibiendo el index i
	free(FILESYSTEM);
}
