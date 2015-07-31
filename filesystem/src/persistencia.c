#include "filesystem.h"
// debo serializar toda la información del FS y luego pasarla a un archivo. posteriormente
// debo hace otra funcion para desserialziar toda esta estructura y poder recuperarla.

char* serializarFS() {
	int todo = 0;
	char* resultadoFinal;
	char * buffer;

	todo = sizeof(int) * 4 + sizeof(FILESYSTEM->listaElementos)
			+ sizeof(FILESYSTEM->listaNodosActivos);

	buffer = malloc(sizeof(todo));

	return resultadoFinal;
}

char* deSerializarFS() {
	char* resultadoFinal;

	return resultadoFinal;
}

// otra funcion trabaje con el archivo para abrirlo y luego para mapearlo a memoria
// serializo las listas
char* serializarListaNodosActivos(char* cadena_serializada_hasta_ahora,
		size_t desplazamiento) {
	char* serializado = string_new();
	int centinela = 0;
	nod* ptrNodo;

	for (centinela = 0;
			centinela < FILESYSTEM->listaNodosActivos->elements_count;
			centinela++) {

		ptrNodo = list_get(FILESYSTEM->listaNodosActivos, centinela);
        serializarNodo(cadena_serializada_hasta_ahora, ptrNodo);
	}

	return serializado;
}
// serializo los enteros

