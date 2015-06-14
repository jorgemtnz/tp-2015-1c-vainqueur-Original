#include "marta.h"

char * generarNombreAlmacenado(char * nombreArchivo, char * nombreFuncion) {
	char * tiempoActual;
	tiempoActual = temporal_get_string_time();
	strcat(nombreArchivo, ".");
	strcat(nombreArchivo, nombreFuncion);
	strcat(nombreArchivo, ".");
	strcat(nombreArchivo, tiempoActual);
	return nombreArchivo;
}

void evaluarSolicitudMapper(char * nombreArchivo) {
	list_find(marta->listaInformacionDelArchivo,(nombreArchivo==));

}


