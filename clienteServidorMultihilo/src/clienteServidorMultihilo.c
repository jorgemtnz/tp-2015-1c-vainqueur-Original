#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sockets/sockets.h>
#include <string.h>


#define PUERTO 7000
#define CONECCIONES_ENTRANTES_PERMITIDAS 4

pthread_mutex_t mutex1 = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mutex2 = PTHREAD_MUTEX_INITIALIZER;

/*	mutex1 = 0
 * 	mutex2 = 0
 *
 */
void * servidorHilo() {
	int fdSocketEscucha, fdSocketNuevasConecciones; // Escuchar sobre fdSocketEscucha, nuevas conexiones sobre fdSocketNuevasConecciones
	char buffer[100];
	fdSocketEscucha = crearSocket();
	asociarSocket(fdSocketEscucha, PUERTO);
	escucharSocket(fdSocketEscucha, CONECCIONES_ENTRANTES_PERMITIDAS);
	//signal mutex2
	pthread_mutex_unlock(&mutex2);
	//wait mutex1
	pthread_mutex_lock(&mutex1);
	pthread_mutex_lock(&mutex1);
	fdSocketNuevasConecciones = aceptarConexionSocket(fdSocketEscucha);
	//signal mutex2
	pthread_mutex_unlock(&mutex2);
	pthread_mutex_lock(&mutex1);
	recibirPorSocket(fdSocketNuevasConecciones, buffer, sizeof(buffer));
	printf("Mensaje Recibido por el servidor : %s \n", buffer);
	strcpy(buffer,"Mensaje Para Cliente \n");
	enviarPorSocket(fdSocketNuevasConecciones, buffer, sizeof(buffer));
	pthread_mutex_unlock(&mutex2);
	pthread_mutex_lock(&mutex1);
	cerrarSocket(fdSocketEscucha);
	pthread_mutex_unlock(&mutex2);
	pthread_exit(0);
}

void * clienteHilo() {
	//wait mutex2
	pthread_mutex_lock(&mutex2);
	pthread_mutex_lock(&mutex2);
	int fdCliente;
	char buffer[100] = "Mensaje Para Servidor \n";
	fdCliente = crearSocket();
	conectarSocket(fdCliente, "127.0.0.1", PUERTO);
	//signal mutex1
	pthread_mutex_unlock(&mutex1);
	//wait mutex2
	pthread_mutex_lock(&mutex2);
	enviarPorSocket(fdCliente, buffer, sizeof(buffer));
	pthread_mutex_unlock(&mutex1);
	pthread_mutex_lock(&mutex2);
	recibirPorSocket(fdCliente, buffer, sizeof(buffer));
	printf("Mensaje Recibido por el Cliente: %s \n", buffer);
	pthread_mutex_unlock(&mutex1);
	pthread_mutex_lock(&mutex2);
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
