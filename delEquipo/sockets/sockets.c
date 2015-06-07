#include <stdio.h>
#include <stdlib.h>
#include <string.h>     //memset
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <errno.h>      //perror
#include <arpa/inet.h>  //INADDR_ANY
#include <unistd.h>     //close

int  crearSocket(){
	// Usado por servidor y por cliente
	int fileDescriptor = socket(AF_INET, SOCK_STREAM, 0);
	if(fileDescriptor == -1){
		perror("[ERROR] Funcion socket\n");
		exit(-1);
	}
	printf("[OK] Funcion SOCKET: Descriptor creado \n");
	return fileDescriptor;
}

void asociarSocket(int sockfd, int puerto){
	// Usado por el Servidor
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
	int posibleError = bind(sockfd, (struct sockaddr *)&miDireccion, sizeof(struct sockaddr));

	if(posibleError == -1){
		perror("[ERROR] Funcion BIND: No se pudo asociar con el puerto\n");
		exit(-1);
	}

	printf("[OK] Funcion BIND. Vinculada al puerto [ %d ]\n",puerto);
}

void conectarSocket(int sockfd,char* ip_Destino, int puerto){
	// Usado por el cliente
	struct sockaddr_in datosServidor;
	// Seteo estructura dest_addr
	datosServidor.sin_family      = AF_INET;
	datosServidor.sin_port        = htons(puerto);
	datosServidor.sin_addr.s_addr = inet_addr(ip_Destino);
	memset(&(datosServidor.sin_zero), '\0', 8);

	int posibleError = connect(sockfd, (struct sockaddr *)&datosServidor, sizeof(struct sockaddr));
	if(posibleError ==-1){
		perror("[ERROR] Funcion connect\n");
		exit(-1);
	}
	printf("[OK] Funcion CONNECT\n");
}

void  escucharSocket(int sockfd, int conexionesEntrantesPermitidas){
	// Usado por el Servidor
	int posibleError = listen(sockfd,conexionesEntrantesPermitidas);
	if(posibleError == -1){
		perror("[ERROR] Funcion listen\n");
		exit(-1);
	}
	printf("[OK] Funcion LISTEN. Admite [ %d ] conexiones entrantes\n",conexionesEntrantesPermitidas);
}

int  aceptarConexionSocket(int sockfd){
	// Usado por el servidor
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

void enviarPorSocket(int fdCliente,const void *msg, int len){
	// Usado por servidor y cliente
	int bytes_enviados = send(fdCliente, msg, len, 0);

	if(bytes_enviados == -1){
		perror("[ERROR] Funcion recv\n");
		exit(-1);           }

	if(bytes_enviados != len){
		perror("[ERROR] No se envio la cadena entera\n");
	}
}

int recibirPorSocket(int fdCliente, void *buf, int len){
	// Usado por servidor y cliente
	int bytes_recibidos = recv(fdCliente, buf,len, 0);

	if(bytes_recibidos == -1){
		perror("[ERROR] Funcion recv\n");
		exit(1);}
	return bytes_recibidos;
}

void cerrarSocket(int sockfd){
	// Usado por servidor y cliente
	// Esto impedirá más lecturas y escrituras al socket. Cualquiera que intente leer o
	// escribir sobre el socket en el extremo remoto recibirá un error.
	close(sockfd);
}

void seleccionarSocket(int maxNumDeFD, fd_set *fdListoLectura, fd_set *fdListoEscritura,fd_set *fdListoEjecucion, int segundos, int miliSegundos){
	struct timeval tv;
	// Esta estructura de tiempo de permite establecer un período máximo de espera.
	// Si segundos = 0 y miliSegundos = 0 => regresará inmediatamente después de interrogar
	// a todos tus file descriptor
	// Si segundos = NULL y miliSegundos = NULL => espera infinitamente
	int microsegundos = miliSegundos * 1000;
	tv.tv_sec = segundos;
	tv.tv_usec = microsegundos;

	int posibleError = select( (maxNumDeFD+1), fdListoLectura, fdListoEscritura, fdListoEjecucion,&tv);

	if(posibleError == -1){
		perror("[ERROR] Funcion select\n");
		exit(-1);
	}
}
