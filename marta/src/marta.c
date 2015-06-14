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
/*  aun no terminada
void evaluarSolicitudMapper(char * nombreArchivo) {
	t_informacionDelArchivo* ptrInformacionDelArchivo;

	list_find(marta->listaInformacionDelArchivo,(nombreArchivo==));

}*/


