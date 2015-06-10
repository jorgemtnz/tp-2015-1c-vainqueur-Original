#include "funcionesJob.h"

// Me robo codigo de las commons
char*   string_substring(char* text, int start, int length) {
	char* new_string = calloc(1, length + 1);
	strncpy(new_string, text + start, length);
	return new_string;
}

char *string_substring_from(char *text, int start) {
	return string_substring(text, start, strlen(text) - start);
}

// Propia
char* buscar(FILE* archi,char cadenaABuscar[MAXLINE]){
	char* subcadenaUtil;
	char  lineaDeArchivo[MAXLINE];

	while( ! feof(archi) )
	{
		fgets(lineaDeArchivo,MAXLINE,archi);
		char* subcadenaUtil = strstr(lineaDeArchivo,cadenaABuscar);

		if(subcadenaUtil != NULL)  // Si la encuentra
		{
			char* respuesta = string_substring_from(subcadenaUtil, strlen(cadenaABuscar));
			//fclose(archi);
			return respuesta;
		}
	}
		// Si la encontro ya sale por el exit de arriba. Si llega aca
		// es porque NO encontro la cadena => Lanzo error
		perror("Cadena no encontrada\n");
		exit(-1);
}

// TERMINADO!
