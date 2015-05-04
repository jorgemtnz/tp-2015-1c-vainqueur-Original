#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <string.h>
#include <errno.h>


int tamanio_archivo(int fd){
	struct stat buf;
	fstat(fd, &buf);
	return buf.st_size;
}

int main (int argc, char *argv[]){
	int mapper;
	char* mapeo;
	int tamanio;

	char* nombre_archivo = "arch.dat";

	if(( mapper = open (nombre_archivo, O_RDONLY) ) == -1){
		//Si no se pudo abrir, imprimir el error y abortar;
		fprintf(stderr, "Error al abrir el archivo '%s': %s\n", nombre_archivo, strerror(errno));
		abort();
	}
	tamanio = tamanio_archivo(mapper);
	if( (mapeo = mmap( NULL, tamanio, PROT_READ, MAP_SHARED, mapper, 0 )) == MAP_FAILED){
		//Si no se pudo ejecutar el MMAP, imprimir el error y abortar;
		fprintf(stderr, "Error al ejecutar MMAP del archivo '%s' de tamaño: %d: %s\n", nombre_archivo, tamanio, strerror(errno));
		abort();
	}

	printf ("Tamaño del archivo: %d\nContenido:'%s'\n", tamanio, mapeo);

	//Seamos prolijos
	munmap( mapeo, tamanio );
	close(mapper);
	return EXIT_SUCCESS;

}
