#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <fcntl.h>
#include "mapeoAMemoria.h"

int main() {
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
	return 0;
}
