#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sockets/sockets.h>

#define PUERTO 9000
#define IP 0
#define CONECCIONES_ENTRANTES_PERMITIDAS 4

void * servidorHilo() {
	int fdSocketEscucha, fdSocketNuevasConecciones; // Escuchar sobre fdSocketEscucha, nuevas conexiones sobre fdSocketNuevasConecciones
	fdSocketEscucha = doSocket();
	do_bind_to_port(fdSocketEscucha,PUERTO);
	do_listen(fdSocketEscucha,CONECCIONES_ENTRANTES_PERMITIDAS);

	while(1)
	{
		fdSocketNuevasConecciones = do_accept(fdSocketEscucha);
	}
}

void * clienteHilo() {
	int fdCliente;
	fdCliente = doSocket();
	do_connect(fdCliente,IP,PUERTO);

}

int main(void) {
	pthread_t tidServidor, tidCliente;
	tidServidor = pthread_create(tidServidor, NULL, servidorHilo, NULL);
	tidCliente = pthread_create(tidServidor, NULL, clienteHilo, NULL);
	pthread_join(tidServidor, NULL);
	pthread_join(tidCliente, NULL);
}
