#include "nodo.h"

sem_t semCliAFS;
sem_t semServAJob;
sem_t semCliANodo;
sem_t semServANodo;

//prototipos
void* clienteAFS();
void* servidorAJob();
void* clienteANodo();
void* servidorANodo();

//se deben crear 4 hilos uno clienteAFilesystem y otro servidorAJob, y uno ServidorANodo y otro clienteANodo
//cada uno debe manejar sus respectivas interacciones
//clienteAFIlesystem
//servidorAJob - recibe el pedido e inicia los dos hilos mapper y reducer
//servidorANodo -
//clienteANodo -
int main(int argc, char **argv) {
	int i, error[4];
	pthread_t tidClienteAFS;
	pthread_t tidServidorAJob;
	pthread_t tidServidorANodo;
	pthread_t tidClienteANodo;
	pthread_attr_t atributos[4];

	error[0] = sem_init(&semCliAFS, 0, 0);
	error[1] = sem_init(&semServAJob, 0, 0);
	error[2] = sem_init(&semCliANodo, 0, 0);
	error[3] = sem_init(&semServANodo, 0, 0);
	if ((error[0] < 0) || (error[1] < 0) || (error[2] < 0) || (error[3] < 0)) {
		perror("[ERROR]: inicializando semaforo");
		exit(-1);
	}
//hilos
	for (i = 0; i < 4; i++) {
		pthread_attr_init(&atributos[i]);
	}

	pthread_create(&tidClienteAFS, &atributos[0], clienteAFS, NULL);
	pthread_create(&tidServidorAJob, &atributos[1], servidorAJob, NULL);
	pthread_create(&tidServidorANodo, &atributos[2], clienteANodo, NULL);
	pthread_create(&tidClienteANodo, &atributos[3], servidorANodo, NULL);

	pthread_join(tidClienteAFS, NULL);
	pthread_join(tidServidorAJob, NULL);
	pthread_join(tidServidorANodo, NULL);
	pthread_join(tidClienteANodo, NULL);

	return 0;
}

void* clienteAFS() {
	int sockTranferencia;
	int retorno = -1;
	void* buffer = "hola desde el nodo";
	sockTranferencia = crearSocket();
	while (retorno < 0) {
		retorno = conectarSocket(sockTranferencia, "127.0.0.1", 9756);
	}
	//comienza la comunicacion se usa sockTranferencia para comunicarse. se debe implementar
	enviarPorSocket(sockTranferencia, buffer, strlen(buffer));

	cerrarSocket(sockTranferencia);
	return NULL;
}
void* servidorAJob() {
//	int sockEscucha;
//	int sockTranferencia;
//
//	sockEscucha = crearSocket();
//	asociarSocket(sockEscucha, 7990);
//	escucharSocket(sockEscucha, 1);
//	sockTranferencia = aceptarConexionSocket(sockEscucha);
////sockTranferencia se puede usar para send y recv
////aca se debe implementar
//
//	cerrarSocket(sockEscucha);
//	cerrarSocket(sockTranferencia);

	return NULL;
}

void* clienteANodo() {
//	int sockTranferencia;
//	int retorno = -1;
//	sockTranferencia = crearSocket();
//	while (retorno < 0) {
//		retorno = conectarSocket(sockTranferencia, vg_ip_Nodo, vg_puerto_Nodo);
//	}
//	//comienza la comunicacion se usa sockTranferencia para comunicarse. se debe implementar
//	cerrarSocket(sockTranferencia);
	return NULL;
}
void* servidorANodo() {

//	int sockEscucha;
//	int sockTranferencia;
//
//	sockEscucha = crearSocket();
//	asociarSocket(sockEscucha, 6890);
//	escucharSocket(sockEscucha, 1);
//	sockTranferencia = aceptarConexionSocket(sockEscucha);
////sockTranferencia se puede usar para send y recv
////aca se debe implementar
//
//	cerrarSocket(sockEscucha);
//	cerrarSocket(sockTranferencia);

	return NULL;
}
