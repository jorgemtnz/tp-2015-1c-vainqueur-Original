#include <stdio.h>
#include "/home/utnso/TPOperativos/filesystem/src/filesystem.h"
element* crearElemento(char* nombre);

element* crearElemento(char* nombre) { //crea un elemento generico para despues configurarlo como archivo o carpeta
	element* elemento = malloc(sizeof(element)); //creamos espacio para el elemnto
	if (elemento == NULL) {
		perror(
				"[ERROR] No se reservo memoria para el Filesystem>..>elemento directorio o archivo ");
		exit(-1);
	}
	elemento->nombre = nombre;
	elemento->estado = DISPONIBLE;

		elemento->index =0;// asigno el que tiene +1
		 // actualizo el id

	elemento->tamanio = 0; // Si es directorio siempre pesa 0. Si es archivo va a engordar
	elemento->directorioPadre = 0; // este es el directorio raiz.
	elemento->dobleListaUbicacionDelBloqueEnNodo = list_create();

	elemento->idUbicacionDelBloqueEnNodo = 0; //se modifica desde el que llama
	return elemento;
}

int  main(int argc, char **argv) {
	element* elemento=NULL;
	element* encontrado =NULL;
	t_list* lista = list_create();
	elemento = crearElemento("maxi");

elemento->index = 4;
	list_add(lista, elemento);

	bool buscaElement(element* unElement){
		return ( unElement->index==4);
	}
encontrado = list_find(lista, (void*)buscaElement);
if (encontrado !=NULL)
printf("encontrado el index %d \n", encontrado->index);

	return 0;
}

