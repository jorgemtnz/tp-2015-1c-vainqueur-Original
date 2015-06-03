#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <string.h>
#include <errno.h>

// recibe un puntero a la ruta del archivo, un puntero al comienzo de la memoria mapeada, un puntero al tamaño de la pagina
// esto es asi porque necesitamos luego desmapear la memoria y para ello necesitamos el tamaño de pagina y el puntero

int tamanio_archivo(int fd) {
	struct stat buf;
	fstat(fd, &buf);
	return buf.st_size;
}

int abreArchivo(char* dirArchivo) {
	int fd;
	if ((fd = open(dirArchivo, O_RDONLY)) == -1) {
		//Si no se pudo abrir, imprimir el error y abortar;
		perror("[ERROR] Funcion OPEN: Error al abrir el archivo \n");
		exit(-1);
	}
	return fd;
}

char* mapeaAMemoria(int tamanio, int fdArchivo, char* ptrDirArchivo) {
	char* ptrMapeo;
	if ((ptrMapeo = mmap( NULL, tamanio, PROT_READ, MAP_SHARED, fdArchivo, 0))
			== MAP_FAILED) {
		perror("[ERROR] Funcion MMAP: Error al mapear el archivo\n");
		exit(-1);
	}
	return ptrMapeo;
}

void imprimeMapeo(int tamanio, char* ptrAMapeo) {
	printf("Tamaño del archivo: %d\nContenido:'%s'\n", tamanio, ptrAMapeo);
}

void desMapea(int tamanio, char* ptrAMapeo) {
	if (munmap(ptrAMapeo, tamanio) == -1) {
		perror("[ERROR] Funcion MUNMAP: Error al desmapear memoria\n");
		exit(-1);
	}
}

void cierraArchivo(int fdArchivo) {
	if (close(fdArchivo) == -1) {
		perror("[ERROR] Funcion CLOSE: Error al cerrar el archivo\n");
		exit(-1);
	}
}

void mapeoAmemoria(char* dirArchivo, char* ptrmapeo, int* ptrtamanio) {
	int archivo;
	int tamanio;
	char* ptrAMapeo;
	archivo = abreArchivo(dirArchivo);
	tamanio = tamanio_archivo(archivo);
	ptrAMapeo = mapeaAMemoria(tamanio, archivo, dirArchivo);
	cierraArchivo(archivo);
	*ptrtamanio = tamanio;
	ptrmapeo = ptrAMapeo;
}

