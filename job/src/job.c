#include "funcionesJob.h"

int main() {
	FILE* archConfig;
	char nombreArchivo[100];

	printf("Ingrese el nombre del archivo de configuracion: ");
	scanf("%s",nombreArchivo);

	// Abro el archivo
	archConfig = fopen(nombreArchivo,"r");
	if(archConfig == NULL){
		perror("No se pudo abrir el archivo de configuracion\n");
		exit(-1);
	}

	char* ipMarta 			= buscar(archConfig,"IP Marta: ");
	char* stringPuertoMarta = buscar(archConfig,"Puerto: ");
	int numPMart = atoi(stringPuertoMarta); // Lo convierto a un int

	printf("%s",ipMarta);
	printf("%d",numPMart);

	fclose(archConfig);

	//conectarConMarta(ipMarta,numPMart); //Se conecta con marta y continua!!
	return 0;
}

