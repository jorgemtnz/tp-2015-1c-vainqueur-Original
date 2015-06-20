#include "marta.h"

int main(int argc, char **argv)
{
	int fdJob, fdMarta;
	char enviarMsg[TAMANIOBUFFER];
	char enviarOtroMsg[TAMANIOBUFFER];

	fdMarta = crearSocket();
	asociarSocket(fdMarta, PUERTO_MARTA);
	escucharSocket(fdMarta, CONEXIONES_ACEPTA_MARTA);

	fdJob = aceptarConexionSocket(fdMarta);

	// Recibe Pedido
	char buffer[TAMANIOBUFFER];
	int bytes_recibidos = recibirPorSocket(fdJob,buffer,TAMANIOBUFFER);
	comprobarDesconexion(bytes_recibidos);
	printf("Mensaje recibido: %s\n", buffer);

	// Envia pedido
	printf("Enviar mensaje: ");
	fgets(enviarOtroMsg,TAMANIOBUFFER,stdin);
	enviarPorSocket(fdJob, enviarOtroMsg, 1024);


	cerrarSocket(fdMarta);
	return 0;

}
