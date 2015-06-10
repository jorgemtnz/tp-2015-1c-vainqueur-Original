#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#define NUMERODEFUNCIONES 16

char* funciones[] = { "formatearMDFS",
					  "eliminarArchivo","renombrarArchivo","moverArchivos",							    // Archivos
					  "crearDirectorio","eliminarDirectorio","renombrarDirectorio","moverDirectorio",   // Directorios
					  "copiarArchivoLocalAlMDFS",
					  "copiarArchivoDelMDFSAlFSLocal",
					  "solicitarMD5deUnArchivoenMDFS",
					  "verBloque","borrarBloque","copiarBloque",										// Bloques
					  "agregarNodo","eliminarNodo" };													// Nodos

//Completar descripciones
char* descripciones[] = {   "Descrpcion de la funcion 1",
							"Descrpcion de la funcion 2",
							"Descrpcion de la funcion 3",
							"Descrpcion de la funcion 4",
							"Descrpcion de la funcion 5",
							"Descrpcion de la funcion 6",
							"Descrpcion de la funcion 7",
							"Descrpcion de la funcion 8",
							"Descrpcion de la funcion 9",
							"Descrpcion de la funcion 10",
							"Descrpcion de la funcion 11",
							"Descrpcion de la funcion 12",
							"Descrpcion de la funcion 13",
							"Descrpcion de la funcion 14",
							"Descrpcion de la funcion 15",
							"Descrpcion de la funcion 16",};

int idFuncion(char* funcion){
	int i;
	for(i = 0; (i < NUMERODEFUNCIONES) && (strcmp(funcion,funciones[i]) != 0); i++);
	return (i <= NUMERODEFUNCIONES-1)? (i+1): -1;
}

void mostrarTodasLasFunciones() {
	int contador = 0;
	do {
		contador += 1;
		printf("*------------------------------------------*\n");
		printf("COMANDO 	= %s\n", funciones[contador]);
		printf("DESCRIPCION = %s\n", descripciones[contador]);
		printf("*------------------------------------------*\n");
	} while (contador <= NUMERODEFUNCIONES);
}

void man(char* funcion){
	int id = idFuncion(funcion);

	if(id == -1){
		printf("La funcion ingresada no existe\n");
		exit(-1);
	}
	else{
		printf("*------------------------------------------*\n");
		printf("COMANDO 	= %s\n", funciones[id-1]);
		printf("DESCRIPCION = %s\n", descripciones[id-1]);
		printf("*------------------------------------------*\n");	}
}
