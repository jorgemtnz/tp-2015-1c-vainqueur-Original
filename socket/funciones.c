/*
 ** FILE:  Funciones.C
 ** AUTOR: Lucas Voboril
 ** FECHA: /05/2015
 **
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>     //memset
#include <sys/types.h>
#include <sys/socket.h>
#include <errno.h>      //perror
#include <arpa/inet.h>  //INADDR_ANY
#include <unistd.h>     //close


int  do_socket(){
	int c = socket(AF_INET, SOCK_STREAM, 0);
	if(c == -1){
		perror("[ERROR] Funcion socket\n");
		exit(-1);
	}
	printf("[OK] Funcion SOCKET: Descriptor creado \n");
	return c;
}

void do_bind_to_port(int sockfd, int puerto){
	struct sockaddr_in miDireccion;
	// Seteamos los valores a la estructura miDireccion
	miDireccion.sin_family      = AF_INET;
	miDireccion.sin_port        = htons(puerto);
	miDireccion.sin_addr.s_addr = 0; // htonl(INADDR_ANY); // Usa mi direccion IP
	memset(&(miDireccion.sin_zero), '\0', 8);

	// Resolvemos el ADDRES already in use
	int reuse = 1;

	    if(setsockopt(sockfd,SOL_SOCKET, SO_REUSEADDR, (char*)&reuse, sizeof(int)) == -1){
	      perror("[ERROR] No es posible reusar el socket\n");
	      exit(1);
	    }
	// Funcion bind
	int c = bind(sockfd, (struct sockaddr *)&miDireccion, sizeof(struct sockaddr));

	if(c == -1){
		perror("[ERROR] Funcion BIND: No se pudo asociar con el puerto\n");
		exit(-1);
	}

	printf("[OK] Funcion BIND. Vinculada al puerto [ %d ]\n",puerto);
}

void do_connect(int sockfd,char* DEST_IP, int puerto){
	struct sockaddr_in servidor;
	// Seteo estructura dest_addr
	servidor.sin_family      = AF_INET;
	servidor.sin_port        = htons(puerto);
	servidor.sin_addr.s_addr = inet_addr(DEST_IP);
	memset(&(servidor.sin_zero), '\0', 8);

	int c = connect(sockfd, (struct sockaddr *)&servidor, sizeof(struct sockaddr));
	if(c==-1){
		perror("[ERROR] Funcion connect\n");
		exit(-1);
	}
	printf("[OK] Funcion CONNECT\n");
}

void  do_listen(int sockfd, int conexionesEntrantesPermitidas){
	int c = listen(sockfd,conexionesEntrantesPermitidas);
	if(c == -1){
		perror("[ERROR] Funcion listen\n");
		exit(-1);
	}
	printf("[OK] Funcion LISTEN. Admite [ %d ] conexiones entrantes\n",conexionesEntrantesPermitidas);
}


int  do_accept(int sockfd){
	struct sockaddr_storage cliente;
	unsigned int addres_size = sizeof(cliente);

	int otroFD = accept(sockfd,(struct sockaddr*) &cliente, &addres_size);

	if(otroFD == -1){
		perror("[ERROR] Funcion accept");
		exit(-1);
	}
	printf("[OK] Funcion ACCEPT\n");

	return otroFD;
}

void do_send(int sockfd,const void *msg, int len){
	int bytes_enviados = send(sockfd, msg, len, 0);

	if(bytes_enviados == -1){
		perror("[ERROR] Funcion recv\n");
		exit(1);}

	if(bytes_enviados != len){
		perror("[ERROR] No se envio la cadena entera\n");
	}
}

void do_recv(int sockfd, void *buf, int len){
	int bytes_recibidos = recv(sockfd, buf,len, 0);

	if(bytes_recibidos == -1){
		perror("[ERROR] Funcion recv\n");
		exit(1);}
}

void do_close(int sockfd){
	// Esto impedirá más lecturas y escrituras al socket. Cualquiera que intente leer o
	// escribir sobre el socket en el extremo remoto recibirá un error.
	close(sockfd);
}
