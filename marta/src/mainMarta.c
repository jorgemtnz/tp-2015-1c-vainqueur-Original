#include "marta.h"

int main(int argc, char **argv)
{

	int fdJob, fdMarta;
	char buffer[TAMANIOBUFFER];
	char enviarMsg[TAMANIOBUFFER];
	char enviarOtroMsg[TAMANIOBUFFER];

	fdMarta = crearSocket();
	asociarSocket(fdMarta, PUERTO_MARTA);
	escucharSocket(fdMarta, CONEXIONES_ACEPTA_MARTA);

	fdJob = aceptarConexionSocket(fdMarta);

	while (1)
	{
		// El servidor espera el primer mensaje
		recibirPorSocket(fdJob, buffer, TAMANIOBUFFER);
		printf("\nMensaje recibido: %s\n", buffer);

		printf("Enviar mensaje: ");
		fgets(enviarOtroMsg,TAMANIOBUFFER,stdin);
		enviarPorSocket(fdJob, enviarOtroMsg, 1024);
	}

	cerrarSocket(fdMarta);
	return 0;

}
