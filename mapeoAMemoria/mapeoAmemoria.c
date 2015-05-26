
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
	int mapper;

	if ((mapper = open(dirArchivo, O_RDONLY)) == -1) {
		//Si no se pudo abrir, imprimir el error y abortar;
		fprintf(stderr, "Error al abrir el archivo '%s': %s\n", dirArchivo,
				strerror(errno));
		abort();
	}
	return mapper;
}

char* mapeaAMemoria(int tamanio, int fdArchivo, char* ptrDirArchivo) {
	char* ptrMapeo;
	if ((ptrMapeo = mmap( NULL, tamanio, PROT_READ, MAP_SHARED, fdArchivo, 0))
			== MAP_FAILED) {
		//Si no se pudo ejecutar el MMAP, imprimir el error y abortar;
		fprintf(stderr,
				"Error al ejecutar MMAP del archivo '%s' de tamaño: %d: %s\n",
				ptrDirArchivo, tamanio, strerror(errno));
		abort();
	}
	return ptrMapeo;

}
void imprimeMapeo(int tamanio, char* mapeo) {
//for (int i=0; i< 2; i ++ ){

	printf("Tamaño del archivo: %d\nContenido:'%s'\n", tamanio, mapeo);
//}

}

void desMapea(int tamanio, char* mapeo) {
	munmap(mapeo, tamanio);

}

void cierraArchivo(int ptrArchivo)

{
	close(ptrArchivo);

}
void mapeoAmemoria(char* dirArchivo, char* ptrmapeo, int* ptrtamanio) {
	int archivo;
	int tamanio;
	char* mapeo;
	archivo = abreArchivo(dirArchivo);
	tamanio = tamanio_archivo(archivo);
	mapeo = mapeaAMemoria(tamanio, archivo, dirArchivo);
	cierraArchivo(archivo);
	*ptrtamanio = tamanio;
	ptrmapeo = mapeo;

}

int  main()
{
return 0;
}

