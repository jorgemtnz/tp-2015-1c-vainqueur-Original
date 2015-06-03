#ifndef SOCKETS_CL_FUNCIONES_H_
#define SOCKETS_CL_FUNCIONES_H_

#include <sys/types.h>
/* Prototipos */
int  do_socket();
void do_bind_to_port(int sockfd, int puerto);
void do_connect(int sockfd,char* ip_destino, int puerto);
void do_listen(int sockfd, int conexionesEntrantesPermitidas);
int  do_accept(int sockfd);
void do_send(int sockfd,const void *msg, int len);
void do_recv(int sockfd, void *buf, int len);
void do_close(int sockfd);
void do_select(int maxNumDeFD, fd_set *fdListoLectura, fd_set *fdListoEscritura,fd_set *fdListoEjecucion, int segundos, int miliSegundos);

#endif /* SOCKETS_CL_FUNCIONES_H_ */
