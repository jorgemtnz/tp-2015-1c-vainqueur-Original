#include "filesystem.h"

/*------------------------FUNCIONES AUXILIARES---------------------------*/
void leerArchivoDeConfiguracion(char* nomArchivo){
		/* Este codigo es del nodo, pero la implementacion es la misma, solo cambia contenido
		 * del archivo de configuracion
		char * temporal;
		t_config * archivoConfig;
		archivoConfig = config_create(RUTACONFIG);
		puertoFS = config_get_int_value(archivoConfig, "PUERTO_FS");
		puertoNodo = config_get_int_value(archivoConfig, "PUERTO_NODO");
		ipFS = config_get_string_value(archivoConfig, "IP_FS");
		ipNodo = config_get_string_value(archivoConfig, "IP_NODO");
		archivoBin = config_get_string_value(archivoConfig, "ARCHIVO_BIN");
		dirTemp = config_get_string_value(archivoConfig, "DIR_TEMP");
		temporal = config_get_string_value(archivoConfig, "NODO_NUEVO");
		if (strcmp(temporal, "SI") == 0) {
			nodoNuevo = NODO_NUEVO;
		}
		if (strcmp(temporal, "NO") == 0) {
			nodoNuevo = NODO_NO_NUEVO;
		}
		config_destroy(archivoConfig);*/
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
