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

//	se deben crear dos hilos una clienteAMartha y el otro clienteANodo ambos manejan sus interacciones medinate socket
//todas la variables globales que sean compartidas entre los hilos deben ser sincronizadas.

	//    clienteAMarta

	indicarArchivosAMarta();


//	clienteANodo

	/*int incrementador; estos hilos son como conexion para el nodo, dependen de lo recibido por marta.

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
