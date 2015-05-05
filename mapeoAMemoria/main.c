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

/* Maxi esto no lo borre, lo dejo a tu desicion, saludos.

//printf ("asdasdasdas");
//crearArchivo("ArchivoDePrueba"); //Crear Archivo Para Mapear de 190 mb

 //Variables
 const char * bloqueDeMemoria;
 int direccionArchivo;
 //
 direccionArchivo = open("archivoDePrueba/archivoDePrueba.txt", O_RDONLY);
 if (direccionArchivo == -1) {
 perror("Error opening file for reading");
 exit(EXIT_FAILURE);
 }
 bloqueDeMemoria = mmap (NULL,2e+7,PROT_WRITE, MAP_PRIVATE, direccionArchivo, 0); //2e+7 son 20mb
 //if (bloqueDeMemoria == MAP_FAILED) handle_error("mmap");
 //munmap() para desmapear

 return 1;
 }
 */
