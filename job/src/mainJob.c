#include "job.h"

int main(int argc, char **argv)
{
	/*
	 * Enuncuado pagina 5
	 * Al iniciar, leerá su correspondiente archivo de configuración, se conectará al Proceso
	 * MaRTA, le indicará los archivos sobre los que desea ejecutar su Job y quedará a la espera
	 * de indicaciones de MaRTA, al que notificará los resultados de sus operaciones.
	 */
	int fdJob;
	char buffer[TAMANIOBUFFER];
	char enviarMsg[TAMANIOBUFFER];
	char nomArchivo[200];

	printf("Ingrese el nombre del archivo de configuracion del job: ");
	fgets(nomArchivo,200,stdin);

	leerArchivoDeConfiguracion(nomArchivo);

	vg_puertoMarta = 6546;
	vg_ipMarta = "127.0.0.1";

	// Job como cliente
	fdJob = crearSocket();
	conectarSocket(fdJob, vg_ipMarta, vg_puertoMarta);
	while (1)
	{
		printf("\nEnviar mensaje: ");
		fgets(enviarMsg,TAMANIOBUFFER,stdin);
		enviarPorSocket(fdJob, enviarMsg, TAMANIOBUFFER);

		recibirPorSocket(fdJob, buffer, TAMANIOBUFFER);
		printf("Mensaje recibido: %s\n", buffer);
	}

	cerrarSocket(fdJob);
	return 0;

}
