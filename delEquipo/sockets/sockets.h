#ifndef SOCKETS_CL_FUNCIONES_H_
#define SOCKETS_CL_FUNCIONES_H_

#include <sys/types.h>
/* Prototipos */
int  crearSocket();
void asociarSocket(int sockfd, int puerto);
void conectarSocket(int sockfd,char* ip_destino, int puerto);
void escucharSocket(int sockfd, int conexionesEntrantesPermitidas);
int  aceptarConexionSocket(int sockfd);
void enviarPorSocket(int fdCliente,const void *msg, int len);
int recibirPorSocket(int fdCliente, void *buf, int len);
void cerrarSocket(int sockfd);
void seleccionarSocket(int maxNumDeFD, fd_set *fdListoLectura, fd_set *fdListoEscritura,fd_set *fdListoEjecucion, int* segundos, int* miliSegundos);

#endif /* SOCKETS_CL_FUNCIONES_H_ */
