#include "filesystem.h"
#include "consola.h"
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char **argv) {
	int fdArchivo, fdEstructura, fdArchConfig;
	fdArchivo = fdEstructura = fdArchConfig = 0;

	char* dirArchivo = "/tmp/archivoProcesar.txt";
	char* dirArchivoEstructura = "/tmp/archivoEstructura.txt";
	char* dirArchivoConfig = "/tmp/archivoConfig.txt";


    fdArchConfig = open(dirArchivoConfig, O_RDONLY);
	fdArchivo = open(dirArchivo, O_RDWR);
	fdEstructura = open(dirArchivoEstructura, O_RDWR | O_CREAT);

	inicializarFS();
     levantaConsola();

	return 0;

}
