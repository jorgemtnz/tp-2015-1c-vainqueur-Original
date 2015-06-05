#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <src/commons/string.h>
#include <src/commons/txt.h>
#include "filesystem.h"
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include "mapeoAMemoria.h"

int  main(int argc, char **argv) {

	char * archivoEstructura;
		int fdArchivo;
		int fdEstructura;
		char* dirArchivo = "/tmp/archivoProcesar.txt";
		char* dirArchivoEstructura = "/tmp/archivoEstructura.txt";
		char* ptrContenidoBloques;

		fdArchivo = open(dirArchivo, O_RDWR);
		fdEstructura = open(dirArchivoEstructura, O_RDWR | O_CREAT);



		 ptrContenidoBloques = string_split(fdArchivo, "/n");

		return 0;

}



void leerRegistro(int arch, fs* fileSystem){
  read(arch,fileSystem,sizeof(fs));//lee el archivo y pone la estructura en la estructura fs

}



void guardarRegistro(int arch,fs* fileSystem){//esto mientras este el archivo abierto sino lo abrimos aca

  write(arch,fileSystem,sizeof(fs));//le paso el registro fileSystem,y el archivo y lo escribe
}
