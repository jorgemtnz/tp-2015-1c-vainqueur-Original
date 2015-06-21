#include "job.h"

void* lanzarUnJob(){

	leerArchivoDeConfiguracion(); // Falta el arrays de archivos

	int fdJob = crearSocket();
	conectarSocket(fdJob,vg_ipMarta,vg_puertoMarta);

	char msg[]="3 Marta, indicame a que archivos les habo un job";
	int msgSize = strlen(msg);
	enviarPorSocket(fdJob,msg,msgSize);

	char bufer[200];
	recibirPorSocket(fdJob,bufer,sizeof(bufer)); // Recibe los bloques a operar sus rutinas
	printf("%s",bufer);

	cerrarSocket(fdJob);
	return NULL;
}

int main(int argc, char **argv) {
	int incrementador;

	for(incrementador = 0; incrementador < HILOS_A_LANZAR; incrementador ++){
		pthread_t tidHiloJob;
		pthread_attr_t atributosDeHilo;

		pthread_attr_init(&atributosDeHilo);

		pthread_create(&tidHiloJob,&atributosDeHilo,lanzarUnJob,NULL);
		pthread_join(tidHiloJob,NULL);
	}
	liberarMemoriaVG();
	return 0;
}
