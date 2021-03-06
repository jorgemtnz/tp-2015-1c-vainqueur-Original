#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <semaphore.h>
#include "../sockets/sockets.h"

#define PUERTO 7000
#define CONECCIONES_ENTRANTES_PERMITIDAS 4

sem_t semaforoServidor;
sem_t semaforoCliente;

// Prototipos
void * servidorHilo();
void * clienteHilo();

int demo() { // Cambiar el nombre de demo por main y ejecutar en caso de prueba
	// Inicializo semaforos en 0
	int error;
	error = sem_init(&semaforoCliente, 0, 0);
	if (error<0)
	{
		perror("[ERROR]: Funcion sem_init : Error al inicializar el semaforo");
		return -1;
	}
	error = sem_init(&semaforoServidor, 0, 0);
	if (error<0)
		{
			perror("[ERROR]: Funcion sem_init : Error al inicializar el semaforo");
			return -1;
		}
	pthread_t tidServidor, tidCliente;

	pthread_attr_t atributos1, atributos2;

	pthread_attr_init(&atributos1);
	pthread_attr_init(&atributos2);

	pthread_create(&tidServidor, &atributos1, servidorHilo, NULL);
	pthread_create(&tidCliente , &atributos2, clienteHilo, NULL);

	pthread_join(tidServidor, NULL);
	pthread_join(tidCliente, NULL);

	return 0;
}

void * servidorHilo() {
	int fdSocketEscucha, fdSocketNuevasConecciones; // Escuchar sobre fdSocketEscucha, nuevas conexiones sobre fdSocketNuevasConecciones
	char buffer[100];

	fdSocketEscucha = crearSocket();
	asociarSocket(fdSocketEscucha, PUERTO);
	escucharSocket(fdSocketEscucha, CONECCIONES_ENTRANTES_PERMITIDAS);

	sem_post(&semaforoCliente);
	sem_wait(&semaforoServidor);

	fdSocketNuevasConecciones = aceptarConexionSocket(fdSocketEscucha);

	sem_post(&semaforoCliente);
	sem_wait(&semaforoServidor);

	recibirPorSocket(fdSocketNuevasConecciones, buffer, sizeof(buffer));
	printf("Mensaje Recibido por el servidor : %s \n", buffer);
	strcpy(buffer, "Mensaje Para Cliente \n");

	enviarPorSocket(fdSocketNuevasConecciones, buffer, sizeof(buffer));

	sem_post(&semaforoCliente);
	sem_wait(&semaforoServidor);

	cerrarSocket(fdSocketEscucha);

	pthread_exit(0);
}

void * clienteHilo() {
	int fdCliente;
	char buffer[100] = "Mensaje Para Servidor \n";

	fdCliente = crearSocket();

	sem_wait(&semaforoCliente);
	conectarSocket(fdCliente, "127.0.0.1", PUERTO);

	sem_post(&semaforoServidor);
	sem_wait(&semaforoCliente);

	enviarPorSocket(fdCliente, buffer, sizeof(buffer));

	sem_post(&semaforoServidor);
	sem_wait(&semaforoCliente);

	recibirPorSocket(fdCliente, buffer, sizeof(buffer));
	printf("Mensaje Recibido por el Cliente: %s \n", buffer);

	sem_post(&semaforoServidor);
	sem_wait(&semaforoCliente);

	cerrarSocket(fdCliente);
	pthread_exit(0);
}
