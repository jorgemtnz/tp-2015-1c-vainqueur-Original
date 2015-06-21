#include "marta.h"

int main(int argc, char **argv)
{
	int fdJob, fdMarta;

	// Conexion con Job
	fdMarta = crearSocket();
	asociarSocket(fdMarta, PUERTO_MARTA);
	escucharSocket(fdMarta, CONEXIONES_ACEPTA_MARTA);

	while(1){
	fdJob = aceptarConexionSocket(fdMarta);

	// Recibe Pedido
	char buffer[TAMANIOBUFFER];
	recibirPorSocket(fdJob,buffer,TAMANIOBUFFER);
	printf("Mensaje recibido: %s\n", buffer);

	// Envia pedido
	char mensaje[] = "Aplica una rutina en\n"
					 "Nodo 1, Bloque 2\n"
					 "Nodo 2, Bloque 1\n"
					 "Nodo 4, Bloque 3\n";

	enviarPorSocket(fdJob, mensaje, sizeof(mensaje));
	}

	cerrarSocket(fdMarta);
	return 0;

}
