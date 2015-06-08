#include <stdio.h>
#include <sockets/sockets.h>
#include <redireccionIO/redireccionIO.h>

#define RUTAMAP "blabl/blabla"

typedef struct nodo {
	int idNodo;
	short estado; //1 disponible, 0 ocupado;
	void * bloques;

} nodo_t;

int informarFinEjecucion() {

}

int ejecutarReduce(int soportaCombiner) {
	if (soportaCombiner) {

	}
}
int ejecutarMap(char * nombreArchivoTemporal, char * ptrDireccionMapeo) {
	ejecutarScriptRedireccionandoIO(dirArchivoSalida, ptrDireccionMapeo,
			RUTAMAP, "");
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
