#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "funciones.h"
#define MAXSTRING 1024

int main() {
	int  fd, puerto;
	char ip[16];
	char buffer[MAXSTRING];
	char enviarMsg[MAXSTRING];

	printf("Ingrese la IP del servidor:");
	scanf("%s",ip);

	printf("Ingrese el puerto de conexion: ");
	scanf("%d",&puerto);

	fd = do_socket();
	// Conectarse al servidor
	do_connect(fd,ip,puerto);

	// Recibe ------CLIENTE CONECTADO------
	do_recv(fd,buffer,MAXSTRING);
	printf("%s\n",buffer);

	while(1){
		printf("\nEnviar mensaje: ");
		scanf("%*c%[^\n]",enviarMsg);

		do_send(fd,enviarMsg,1024);

		// Si se manda salir, se cierra la sesion
		if(strcmp(enviarMsg,"salir")==0){
			exit(1);					}

		//El cliente recibe el mensaje del servidor
		do_recv(fd,buffer,1024);

		// Si se manda salir, se cierra la sesion
		if(strcmp(buffer,"salir")==0){
			exit(1);				  }

		printf("Mensaje recibido: %s\n",buffer);
}
	do_close(fd);
	return 0;
}
