#include "job.h"

/*
 **					DOCUMENTACION - mainJob.c
 **
 **		Funcion leerArchivoDeConfiguracion();
 **	[ Test OK ] - leerArchivoDeConfiguracion();
 **	[ Test OK ] - testleerArchivoDeConfiguracion();
 **	NOTA: Cuando se haga el archivo de configuracion, NO poner espacio antes y despues del =
 **
 **		Funcion indicarArchivosAMarta();
 **		incluye
 **			Funcion [void sendTamanioDe(char* cadena);]
 **			Funcion [void conectarConMarta();]
 **	[ Test OK ] - sendTamanioDe(char* cadena);
 **	[ Test OK ] - conectarConMarta();
 **
 */

int main() {

	leerArchivoDeConfiguracion(); // /home/utnso/TPOperativos/job/a.cfg

	indicarArchivosAMarta();

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
