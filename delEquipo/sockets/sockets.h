#ifndef SOCKETS_H_
#define SOCKETS_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>     //memset
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <errno.h>      //perror
#include <arpa/inet.h>  //INADDR_ANY
#include <unistd.h>     //close
#include <netdb.h> 		//gethostbyname

// Funciones
int  crearSocket();
void  enviarPorSocket(int fdCliente,const void *msg, int len);
void  recibirPorSocket(int fdCliente, void *buf, int len);		// Retorna la cantidad de bytes recibidos
void comprobarDesconexion(int bytes);
void cerrarSocket(int sockfd);
void seleccionarSocket(int maxNumDeFD, fd_set *fdListoLectura, fd_set *fdListoEscritura,
					   fd_set *fdListoEjecucion, int* segundos, int* miliSegundos);
// Solo para el servidor
void asociarSocket(int sockfd, int puerto);
void escucharSocket(int sockfd, int conexionesEntrantesPermitidas);
int  aceptarConexionSocket(int sockfd);
// Solo para el ciente
void conectarSocket(int sockfd,char* ip_destino, int puerto);

#endif /* SOCKETS_H_ */
