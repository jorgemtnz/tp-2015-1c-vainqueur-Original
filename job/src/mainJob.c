#include "job.h"

/*
 **					DOCUMENTACION - mainJob.c
 **
 **		Funcion leerArchivoDeConfiguracion();
 **	[ Test OK ] - leerArchivoDeConfiguracion();
 **	[ Test OK ] - testleerArchivoDeConfiguracion();
 **	NOTA: Cuando se haga el archivo de configuracion, NO poner espacio antes y despues del =
 **
 **		Funcion indicarArchivosAMarta();
 **		incluye
 **			Funcion [void sendTamanioDe(char* cadena);]
 **			Funcion [void conectarConMarta();]
 **	[ Test OK ] - sendTamanioDe(char* cadena);
 **	[ Test OK ] - conectarConMarta();
 **
 */
sem_t semCliAMartha;
sem_t semCliANodo;

//prototipos
void* clienteAMartha();
void* clienteANodos();

int main() {

	int error, errorOtro;
	error = sem_init(&semCliAMartha, 0, 0);
	errorOtro = sem_init(&semCliANodo, 0, 0);
	if ((error < 0) || (errorOtro < 0)) {
		perror("[ERROR]: inicializando semaforo");
		exit(-1);
	}

	leerArchivoDeConfiguracion(); // /home/utnso/TPOperativos/job/a.cfg
//crearJob() crear las estructuras
	pthread_t tidClienteAMartha;
	pthread_t tidClienteANodos;
	pthread_attr_t atributos1, atributos2;
	pthread_attr_init(&atributos1);
	pthread_attr_init(&atributos2);
	pthread_create(&tidClienteAMartha, &atributos1, clienteAMartha, NULL);
	pthread_create(&tidClienteANodos, &atributos2,clienteANodos, NULL);

	pthread_join(tidClienteAMartha, NULL);
	pthread_join(tidClienteANodos, NULL);
//	se deben crear dos hilos una clienteAMartha y el otro clienteANodo ambos manejan sus interacciones medinate socket
//todas la variables globales que sean compartidas entre los hilos deben ser sincronizadas.


	liberarMemoriaVG();
	return 0;
}
	//    clienteAMarta
void* clienteAMartha(){
	int sockTranferencia;

	sockTranferencia = crearSocket();
	conectarSocket(sockTranferencia, vg_ipMarta,vg_puertoMarta);
	//empieza la comunicacion - marta le manda info de los nodos, IP en una variable que sera compartida
	//y region critica se debe usar mutex
	//indicarArchivosAMarta();
	cerrarSocket(sockTranferencia);
	return NULL;
}
//	clienteANodo se ejecuta solo despues que marta mande la info de los nodos
void* clienteANodos(){
	int sockTranferencia;
//se van a lanzar 2 hilos que van a un nodo,


	/*int incrementador; estos hilos son como conexion para el nodo, dependen de lo recibido por marta.

	 for(incrementador = 0; incrementador < HILOS_A_LANZAR; incrementador ++){
	 pthread_t tidHiloJob;
	 pthread_attr_t atributosDeHilo;

	 pthread_attr_init(&atributosDeHilo);

	 pthread_create(&tidHiloJob,&atributosDeHilo,manejaHilo,NULL);
	 pthread_join(tidHiloJob,NULL);

	 //sockTranferencia = crearSocket();
		//conectarSocket(sockTranferencia,variable compartida con direccion IP que manda marta)
	 }*/
	//cerrarSocket(sockTranferencia);
return NULL;
}
