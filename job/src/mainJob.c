#include "job.h"

int main(int argc, char **argv) {

	leerArchivoDeConfiguracion();
	/*int incrementador;

	for(incrementador = 0; incrementador < HILOS_A_LANZAR; incrementador ++){
		pthread_t tidHiloJob;
		pthread_attr_t atributosDeHilo;

		pthread_attr_init(&atributosDeHilo);

		pthread_create(&tidHiloJob,&atributosDeHilo,conectarConMarta,NULL);
		pthread_join(tidHiloJob,NULL);
	}*/
	liberarMemoriaVG();
	return 0;
}
