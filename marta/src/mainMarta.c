#include "marta.h"

sem_t semServAJob;
sem_t semCliFS;

//prototipos
void* servidorAJob();
void* clienteAFS();

int main(int argc, char **argv) {
	int error, errorOtro;

	// Toda esta secuencia es por job, asi que ir pensando en hacer una void* para
	// meterlo adentro de un hilo
	leerArchivoDeConfiguracion();
	testleerArchivoDeConfiguracion();

	error = sem_init(&semServAJob, 0, 0);
	errorOtro = sem_init(&semCliFS, 0, 0);
	if ((error < 0) || (errorOtro < 0)) {
		perror("[ERROR]: inicializando semaforo");
		exit(-1);
	}

	pthread_t tidClienteFS;
	pthread_t tidServidorAJob;
	pthread_attr_t atributos1, atributos2;
	pthread_attr_init(&atributos1);
	pthread_attr_init(&atributos2);
	pthread_create(&tidClienteFS, &atributos1, clienteAFS, NULL);
	pthread_create(&tidServidorAJob, &atributos2, servidorAJob, NULL);

	pthread_join(tidClienteFS, NULL);
	pthread_join(tidServidorAJob, NULL);
//	se deben hacer dos hilos uno servidorAJob y otro clienteAFilesystem ambos manejaran las respectivas interacciones
	return 0;
}

void* clienteAFS() {
	int sockTranferencia;
	int retorno = -1;
//	sem_post(&semServAJob);
	void* buffer[1024];
	void* msg = "hola desde marta";
	sockTranferencia = crearSocket();
	conectarSocketPorPrimeraVez(sockTranferencia, vg_ipFilesystem,
			vg_puertoFilesystem);

//comienza la comunicacion, se usa sockTranferencia para comunicarse. se debe implementar la interaccion

	enviarPorSocket(sockTranferencia, msg, strlen(msg));
//	recibirPorSocket(sockTranferencia, buffer, 1024);
//	printf("desde el servidor  %s\n", buffer);
	cerrarSocket(sockTranferencia);
	return NULL;
}
void* servidorAJob() {
// servidorAJob
//	sem_wait(&semServAJob);
	void* bufferJOb = malloc(sizeof(int));

	vg_fdMarta = crearSocket();
	asociarSocket(vg_fdMarta, vg_martaPuerto);
	escucharSocket(vg_fdMarta, vg_conexionesPermitidas);
	vg_fdJob = aceptarConexionSocket(vg_fdMarta);

	recibirPorSocket(vg_fdJob, bufferJOb, sizeof(int));
	printf("Mensaje recibido de job: %s\n", bufferJOb);

//	// Envia pedido
//	char mensaje[] = "Aplica una rutina en\n"
//					 "Nodo 1, Bloque 2\n"
//					 "Nodo 2, Bloque 1\n"
//					 "Nodo 4, Bloque 3\n";
//
//	enviarPorSocket(vg_fdJob, mensaje, sizeof(mensaje));
	cerrarSocket(vg_fdJob);
	cerrarSocket(vg_fdMarta);
	return NULL;
}
