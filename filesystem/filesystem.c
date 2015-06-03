#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <commons/collections/list.h>
#include "filesystem.h"
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

int main( ){
	char * archivoEstructura;
	int fdArchivoEstructura;
	char* dirArchivo = "estructura.txt";

	fdArchivoEstructura = open(dirArchivo, O_RDWR | O_CREAT);
	return 0;
}
