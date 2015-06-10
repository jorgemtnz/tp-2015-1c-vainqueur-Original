#include "funcionesJob.h"

char* buscar(FILE* archi,char cadenaABuscar[MAXLINE]){
	char* subcadenaUtil;
	char  lineaDeArchivo[MAXLINE];

	while( ! feof(archi) )
	{
		fgets(lineaDeArchivo,MAXLINE,archi);
		char* subcadenaUtil = strstr(lineaDeArchivo,cadenaABuscar);

		if(subcadenaUtil != NULL)  // Si la encuentra
		{
			fclose(archi);
			return subcadenaUtil;
		}
	}
		// Si la encontro ya sale por el exit de arriba. Si llega aca
		// es porque NO encontro la cadena => Lanzo error
		perror("Cadena no enontrada\n");
		exit(-1);
}
