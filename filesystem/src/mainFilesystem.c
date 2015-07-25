#include "filesystem.h"

sem_t semServAMartha;
sem_t semSerANodos;
//prototipos
void* servidorAMartha();
void* servidorANodos();

int main(int argc, char **argv) {

int error, errorOtro;
error = sem_init(&semServAMartha,0,0);
errorOtro= sem_init(&semSerANodos,0,0);
if((error<0)||(errorOtro<0)){
	perror("[ERROR]: inicializando semaforo");
	exit(-1);
}

pthread_t tidServidorAMartha;
pthread_t tidServidorANodos;
pthread_attr_t atributos1, atributos2;
pthread_attr_init(&atributos1);
pthread_attr_init(&atributos2);
pthread_create(&tidServidorAMartha, &atributos1, servidorAMartha, NULL);
pthread_create(&tidServidorANodos, &atributos2,servidorANodos, NULL);

pthread_join(tidServidorAMartha, NULL);
pthread_join(tidServidorANodos, NULL);

//	se escribe en pseudocodigo lo que se debe hacer para luego irlo programando
//crearFilesystem
//inicializar filesystem
//leer archivoDeConfiguracion
//crear hilos, uno servidorAMartha y otro servidorANodos y hacer uso del join para que el hilo del main los espere
//
//servidorAMartha
//se encarga de las comunicaciones con Martha. debe ser un servidor que se conecta con un solo cliente
//dentro de un ciclo infinito -donde martha es quien se conecta.
//manejar los mensajes por socket
//1. mensaje de martha que pide ubicacion de archivos
//
//servidorANodos
//se encarga de las comunicaciones con los nodos, debe ser un hilo concurrente con select- donde se recibe
//una cantidad de nodos en el archivo de configuracion
//levantarConsola y en funcion de  lo que se va pidiendo se debe
//dentro de un ciclo infinito manejar mensajes por socket

return 0;
}

void* servidorAMartha(){

	return NULL;
}

void* servidorANodos(){
	return NULL;
}
