#include "funcionesJob.h"

int main() {
	char nombreArchivo[100];
	FILE* archConfig;

	printf("Ingrese el nombre del archivo de configuracion: ");
	scanf("%s",nombreArchivo);

	archConfig = fopen(nombreArchivo,"r");
	if(archConfig == NULL){
		perror("No se pudo abrir el archivo de configuracion\n");
		exit(-1);
	}

	char* ipMarta = buscar(archConfig,"IP Marta: ");

	printf("%s\n", ipMarta);

	return 0;
}

