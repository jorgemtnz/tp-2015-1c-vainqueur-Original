#include "job.h"

int main(int argc, char **argv)
{
	int fdJob;
	char buffer[TAMANIOBUFFER];
	char enviarMsg[TAMANIOBUFFER];

	vg_puertoMarta = 6546;
	vg_ipMarta = "127.0.0.1";

	fdJob = crearSocket();

	conectarSocket(fdJob, vg_ipMarta, vg_puertoMarta);

	recibirPorSocket(fdJob, buffer, TAMANIOBUFFER);
	printf("%s\n", buffer);

	while (1)
	{
		printf("\nEnviar mensaje: ");
		scanf("%*c%[^\n]", enviarMsg);

		enviarPorSocket(fdJob, enviarMsg, TAMANIOBUFFER);

		recibirPorSocket(fdJob, buffer, TAMANIOBUFFER);


		printf("Mensaje recibido: %s\n", buffer);
	}
	cerrarSocket(fdJob);
	return 0;

}
