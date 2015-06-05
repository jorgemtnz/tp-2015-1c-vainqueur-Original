#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sockets/sockets.h>


#define PUERTO 9000
#define IP 0
#define CONECCIONES_ENTRANTES_PERMITIDAS 4

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mutex2 = PTHREAD_MUTEX_INITIALIZER;

void * servidorHilo() {
	int fdSocketEscucha, fdSocketNuevasConecciones; // Escuchar sobre fdSocketEscucha, nuevas conexiones sobre fdSocketNuevasConecciones
	char buffer[100] = "Mensaje Para Cliente \n";
	fdSocketEscucha = crearSocket();
	asociarSocket(fdSocketEscucha, PUERTO);
	escucharSocket(fdSocketEscucha, CONECCIONES_ENTRANTES_PERMITIDAS);
	pthread_mutex_unlock(&mutex);
	while (1) {
		fdSocketNuevasConecciones = aceptarConexionSocket(fdSocketEscucha);
	}
	enviarPorSocket(fdSocketNuevasConecciones, buffer, sizeof(buffer));
	recibirPorSocket(fdSocketNuevasConecciones, buffer, sizeof(buffer));
	pthread_mutex_unlock(&mutex2);
	printf("Mensaje Recibido por el servidor : %s \n", buffer);
	cerrarSocket(fdSocketEscucha);
	pthread_exit(0);
}

void * clienteHilo() {
	pthread_mutex_lock(&mutex);
	int fdCliente;
	char buffer[100] = "Mensaje Para Servidor \n";
	fdCliente = crearSocket();
	conectarSocket(fdCliente, IP, PUERTO);
	pthread_mutex_lock(&mutex2);
	enviarPorSocket(fdCliente, buffer, sizeof(buffer));
	recibirPorSocket(fdCliente, buffer, sizeof(buffer));
	printf("Mensaje Recibido por el Cliente: %s \n", buffer);
	cerrarSocket(fdCliente);
	pthread_exit(0);
}

int main() {
	pthread_t tidServidor, tidCliente;
	pthread_attr_t atributos1,atributos2;
	pthread_attr_init(&atributos1);
	pthread_attr_init(&atributos2);
	tidServidor = pthread_create(&tidServidor, &atributos1, servidorHilo, NULL);
	tidCliente = pthread_create(&tidServidor, &atributos2, clienteHilo, NULL);
	pthread_join(tidServidor, NULL);
	pthread_join(tidCliente, NULL);
	return 0;
}
