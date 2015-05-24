#ifndef FUNCIONES_H_
#define FUNCIONES_H_

int  do_socket();
void do_connect(int ,char* , int );
void do_bind_to_port(int , int );
void do_listen(int , int );
int  do_accept(int);
void do_send(int,const void *, int);
void do_recv(int , void *, int );
void do_close(int);

#endif /* FUNCIONES_H_ */
