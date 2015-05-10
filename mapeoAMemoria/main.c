#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <fcntl.h>
#include "mapeoAMemoria.h"
#include "CrearArchivo/crearArchivo.h"

#define FILEPATH "/home/utnso/prueba.txt" // dirección del archivo

int main(int argc, char **argv) {

	int archivo;
	int tamanio;
	char* mapeo;

	archivo = abreArchivo(FILEPATH);

	tamanio = tamanio_archivo(archivo);

	mapeo = mapeaAMemoria(tamanio, archivo, FILEPATH);

	imprimeMapeo(tamanio, mapeo);


	desMapea(tamanio, mapeo);

	cierraArchivo(archivo);

	return 1;
}


