#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <commons/string.h>
#include <commons/txt.h>
#include "filesystem.h"
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <commons/propias/mapeoAmemoria.h>

int  main(int argc, char **argv) {

	char * archivoEstructura;
		int fdArchivo;
		char* dirArchivo = "/tmp/archivoProcesar.txt";
		char* contenidoBloque;

		fdArchivo = open(dirArchivo, O_RDWR);


		 contenidoBloque = string_n_split(fdArchivo, 1, "/n");

		return 0;

}


