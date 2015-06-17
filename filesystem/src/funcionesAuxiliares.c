#include "filesystem.h"

/*------------------------FUNCIONES AUXILIARES---------------------------*/
void leerArchivoDeConfiguracion(char* nomArchivo) {
	// El archivo config de FS tiene PUERTO_LISTEN Y LISTA_NODOS
	t_config * archivoConfig;

	archivoConfig = config_create(RUTACONFIGFS);
	vg_puerto_listen = config_get_int_value(archivoConfig, "PUERTO_LISTEN");
	vg_lista_nodos = config_get_array_value(archivoConfig, "LISTA_NODOS");

	config_destroy(archivoConfig);
}

int comparaNumeroBloque(nodBloq* elemento) {
	int numeroBloque;
	printf("Ingrese el nombre de bloque a borrar");
	scanf("%d", &numeroBloque);

	return (numeroBloque == elemento->numeroBloque);
}

void cargarBloques(t_list *listaBloques) {
	int i = 0;
	for (; i <= NUMEROBLOQUES; i++) { //ciclo de for para cargar los 102 bloques
		bloq* bloque;  //varaible para almacenar el bloque creado
		bloque = crearBloque();  //crea el bloque
		list_add(listaBloques, bloque);  //lo agrega a la lista
	}
}

void leerRegistro(int arch) {
	read(arch, FILESYSTEM, sizeof(fs)); //lee el archivo y pone la estructura en la estructura fs
}

void guardarRegistro(int arch) { //esto mientras este el archivo abierto sino lo abrimos aca

	write(arch, FILESYSTEM, sizeof(fs)); //le paso el registro fileSystem,y el archivo y lo escribe
}

element* buscarElementoPor(char* nombre) {
	int i, elementosEnLista;
	element *elementoBuscado;
	element* elementoi;
	elementosEnLista = FILESYSTEM->listaElementos->elements_count;

	for (i = 0; i <= elementosEnLista; i++) {
		elementoi = list_get(FILESYSTEM->listaElementos, i);
		if (string_equals_ignore_case(elementoi->nombre, nombre)) {
			elementoBuscado = elementoi;
		} else {
			return NULL;
		}
	}

	return elementoBuscado;
}

void renombrarElemento(element* ptrElemento, char* nuevoNombreElemento) {
		strcpy(ptrElemento->nombre, nuevoNombreElemento);
}

void moverElemento(element* elementoOrigen, element* directorioDestino) {

	// Valido que no se quiera mover dentro de un archivo
	if (directorioDestino->tipoElemento == ESDIRECTORIO) {

		// Hago el cambio de directorio padre con el index del directorio padre
		elementoOrigen->directorioPadre = directorioDestino->index;
	} else {
		perror("[ERROR]no se puede mover. El directorio destino no es un tipo directorio");
		exit(-1);

	}
}
void eliminarElemento(char* nombreElemento) {
	int i;
	int elementosEnLista = FILESYSTEM->listaElementos->elements_count;
	int sonIguales;

	for (i = 0; i <= elementosEnLista; i++) { // Recorremos la lista
		element* elementoi;
		elementoi = list_get(FILESYSTEM->listaElementos, i);
		sonIguales = string_equals_ignore_case(elementoi->nombre,
				nombreElemento);
		// Si las cadenas son iguales => encontro string => lo elimino

		if (sonIguales) {
			list_remove(FILESYSTEM->listaElementos, i);
		}//ojo no se libera memoria, corregir...

		// Si las cadenas son distintas => Sigue el for
	}
} // Generica, sirve para archivos y directorios

void mostrarElementos() {
	int elementosEnLista = FILESYSTEM->listaElementos->elements_count;
	int i;
	for (i = 0; i <= elementosEnLista; i++) {
		element* elementoi;
		elementoi = list_get(FILESYSTEM->listaElementos, i);
		printf("Index:%d   Elemento:%s\n", elementoi->index, elementoi->nombre);
	}
}

