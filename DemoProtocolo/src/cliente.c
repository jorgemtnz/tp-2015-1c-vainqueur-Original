#include "demo.h"

int main() {
	int tamanioPaqueteRecibido;

	int fdCliente  = crearSocket();
	conectarSocket(fdCliente,"127.0.0.1",PUERTO);

	recibirPorSocket(fdCliente, &tamanioPaqueteRecibido , sizeof(int));
	printf("Tamanio del paquete recibido: %d\n",tamanioPaqueteRecibido);

	void * buffer = malloc (tamanioPaqueteRecibido);
	recibirPorSocket(fdCliente,buffer,tamanioPaqueteRecibido);

	Paquete * paqueteRecibido = deserializar(buffer,tamanioPaqueteRecibido);

	unaStr * alumno = malloc(sizeof(unaStr));
	memcpy(& (alumno->edad) , paqueteRecibido->payLoad,sizeof(alumno->edad));
	size_t desplazamiento = 4;

	memcpy(& (alumno->promedio) , paqueteRecibido->payLoad + desplazamiento , sizeof(alumno->promedio));
	desplazamiento += 4;

	// Hasta aca, una puinturita.
	alumno->nombre = malloc(6);
	strcpy(alumno->nombre,paqueteRecibido->payLoad + desplazamiento);
//	memcpy(alumno->nombre, paqueteRecibido->payLoad + desplazamiento , 6 );

	imprimirAlumno(alumno);

	free(buffer);
	cerrarSocket(fdCliente);

	return 0;
}
