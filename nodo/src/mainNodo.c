#include "nodo.h"

sem_t semCliAFS;
sem_t semServAJob;
sem_t semCliANodo;
sem_t semServANodo;

//prototipos
void* clienteAFS(); //-> le pasa la ip y el puerto del nodo ++ solo para conectarFS
void* servidorAJob(); //->usa el puerto a Job del config ++ solo para atender a un job
void* clienteANodo(); //->necesita ip y puerto de otro nodo-servidorNodo ++solo para conectarse a otro Nodo
void* servidorANodo(); //-> usa el puerto del config  ++ solo para atender a otro Nodo

//se deben crear 4 hilos uno clienteAFilesystem y otro servidorAJob, y uno ServidorANodo y otro clienteANodo
//cada uno debe manejar sus respectivas interacciones
//clienteAFIlesystem
//servidorAJob - recibe el pedido e inicia los dos hilos mapper y reducer
//servidorANodo -
//clienteANodo -
int main(int argc, char **argv) {
	int i, error[4];

	vg_nodo =  crearNodo();

	levantarArchivoConfiguracion();
	testleerArchivoDeConfiguracion();

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
	int sockTranferencia = 0;


	sockTranferencia = crearSocket();
	conectarSocketPorPrimeraVez(sockTranferencia, vg_ip_FS, vg_puerto_FS);//lo hardcodeo por ahora
	//comienza la comunicacion se usa sockTranferencia para comunicarse. se debe implementar
	//enviar el el idNodo, luego el puerto y el ip del nodo
	enviar(CONECXION_NODO,vg_nodo,sockTranferencia);
//	enviarPorSocket(sockTranferencia, buffer, strlen(buffer));
// voy a recibir del FS el pedido del bloque
	while (vg_desconectar == 1) {
		recibir(sockTranferencia);
	}

	return NULL;
}
void* servidorAJob() {
	int sockEscucha;
	int sockTranferencia;
	void* bufferJob[1024];

	sockEscucha = crearSocket();
	asociarSocket(sockEscucha, vg_puerto_job);
	escucharSocket(sockEscucha, 1);
	sockTranferencia = aceptarConexionSocket(sockEscucha);
//sockTranferencia se puede usar para send y recv
//aca se debe implementar
	recibirPorSocket(sockTranferencia, bufferJob, 1024);
//	printf("desde el job  %s\n", bufferJob);
	cerrarSocket(sockEscucha);
	cerrarSocket(sockTranferencia);

	return NULL;
}

void* clienteANodo() {
//	int sockTranferencia;
//	int retorno = -1;
//	sockTranferencia = crearSocket();
//	conectarSocketPorPrimeraVez(sockTranferencia, vg_ip_Nodo, vg_puerto_Nodo);
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
