#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "funciones.h"
#define MAXSTRING 1024

int main() {
	int  fd,fd2,puerto;               // fd significa file descriptor
	char buffer[MAXSTRING];           // Para recibir mensaje
	char enviarMsg[MAXSTRING];        // Para enviar  mensaje
	char enviarOtroMsg[MAXSTRING];    // Para enviar  otro mensaje

	printf("IP del Servidor: 127.0.0.1\n");
	printf("Introduzca el puerto de conxion: ");
	scanf("%d",&puerto);

	fd = do_socket();

	do_bind_to_port(fd,puerto);

	do_listen(fd,1);

	fd2 = do_accept(fd);

	printf("\n------SESION INICIADA: CLIENTE CONECTADO------\n");

	strcpy(enviarMsg,"\n------SESION INICIADA: SERVIDOR CONECTADO------");
	do_send(fd2, enviarMsg,MAXSTRING); // Mandale el sesion iniciada

	while(1){
		// El servidor espera el primer mensaje
		do_recv(fd2,buffer,1024);

		// Si alguno manda salir se cierra la sesion
		if(strcmp(buffer,"salir")==0){
			exit(1);              }

		printf("\nMensaje recibido: %s\n",buffer);

		printf("Enviar mensaje: ");
		scanf("%*c%[^\n]",enviarOtroMsg);
		do_send(fd2,enviarOtroMsg,1024);

		// Si alguno manda salir se cierra la sesion
		if(strcmp(enviarOtroMsg,"salir")==0){
			exit(1);                        }
	}

	do_close(fd2);
	do_close(fd);
	return 0;
}
