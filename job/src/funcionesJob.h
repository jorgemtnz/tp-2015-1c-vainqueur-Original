#ifndef FUNCIONESJOB_H_
#define FUNCIONESJOB_H_

// Librerias
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <sockets/sockets.h>

#define MAXLINE 100

// Estructura del archivo.config
//	char  ipMarta[25];
//	int   puertoMarta;
//	void* mapper;
//	void* reducer;
//	int   aceptaCombiner;
//	FILE* listaDeArchivos;
//	char* nombreDelArchivoDondeAlmacenarResultado[50];

// Prototipos
char* buscar(FILE* archi,char cadenaABuscar[MAXLINE]);	// Leer archivo de Configuracion
void  conectarConMarta(char* ipMarta, int puertoMarta);

#endif /* FUNCIONESJOB_H_ */
