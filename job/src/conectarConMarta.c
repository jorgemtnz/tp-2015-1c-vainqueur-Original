#include "funcionesJob.h"

void conectarConMarta(char* ipMarta, int puertoMarta){
	int fdJob = crearSocket();
	conectarSocket(fdJob,ipMarta,puertoMarta);
}
// TERMINADO!
