#include <stdio.h>
#include <stdlib.h>
#include <sockets/sockets.h>
#include <redireccionIO/redireccionIO.h>
#include <string.h>

#define RUTAMAP "blabl/blabla"
#define EJECUCIONOK 1
#define EJECUCIONFALLO -1

typedef struct nodo {
	int idNodo;
	short estado; //1 disponible, 0 ocupado;
	void * bloques;

} nodo_t;

/*
 getBloque(numero) ​
 :   Devolverá   el   contenido   del   bloque   solicitado   almacenado   en   el
 Espacio de Datos.
 ● setBloque(numero,   [datos]) ​
 :   Grabará   los   datos   enviados   en   el   bloque   solicitado   del
 Espacio de Datos
 ● getFileContent(nombre) ​
 :   Devolverá   el   contenido   del   archivo   de   Espacio   Temporal
 solicitado.
 */

void * getBloque(int numeroBloque) {

}

setBloque() {

}

getFileContent() {

}

int informarEjecucionAJob(nodo_t* datosDelNodo, char* ipJob, int puertoJob,
		int comoTerminoLaEjecucion) {
	int fdNodo = crearSocket();
	conectarSocket(fdNodo, ipJob, puertoJob);
	printf("Nodo: %d conectado al Job con ip %s mediante el puerto %d \n",
			datosDelNodo->idNodo, ipJob, puertoJob);
	enviarPorSocket(fdNodo, (void *) comoTerminoLaEjecucion, sizeof(int));
	printf("Nodo: Mensaje Enviado al Job \n");
	cerrarSocket(fdNodo);
	return 0;
}

int ejecutarReduce(int soportaCombiner) {
	if (soportaCombiner) {

	}
}
int ejecutarMap(char * nombreArchivoTemporal, char * ptrDireccionMapeo) {
	char ruta[60] = "/tmp/";
	strcat(ruta, nombreArchivoTemporal);
	if (ejecutarScriptRedireccionandoIO(ruta, ptrDireccionMapeo,
	RUTAMAP, "") < 0) {
		perror("[ERROR] Funcion ejecutarScriptRedireccionandoIO\n");
		exit(EJECUCIONFALLO);
	}
	return EJECUCIONOK;
}

int main() {
	nodo_t datosDelNodo;
	datosDelNodo.idNodo = 1;
	return 0;
}

void conectarNodo(nodo_t* datosDelNodo, char* ipFS, int puerto) {
	int fdNodo = crearSocket();
	conectarSocket(fdNodo, ipFS, puerto);
	printf("Nodo: %d conectado al FS con ip %s mediante el puerto %d \n",
			datosDelNodo->idNodo, ipFS, puerto);
}

