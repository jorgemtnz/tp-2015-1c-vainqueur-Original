#include <stdio.h>
#include <string.h>
#include <src/commons/string.h>
#include "protocolo.h"
#include <stdlib.h>
// En desarrollo

int obtenerHeader(void* buffer){
	char* primerChar = malloc(sizeof(char));
	int header = 0;
	(char*)buffer;
	primerChar = string_substring_until( buffer, UN_BYTE);
	header = (*(primerChar))-'0';//Lo paso a int
	close(primerChar);
	return header;
}

char * obtenerPayload(void* buffer){
	char* payload = malloc(sizeof(char*));
	payload = string_substring_from(buffer, UN_BYTE);

	return payload;
}


void * obtenerEstructura(void * buffer) {
	
int header;
char* payload;
void* bufferSerializado;

header = obtenerHeader(buffer);

payload = obtenerPayload(buffer);


	

	switch (header)
	{

		case ARCHIVO_CARGA_INICIAL:

			bufferSerializado = payload;

		break;

		case ESCRITURA_BLOQUE:
		break;


		case INFORMAR_UBICACION_ARCHIVOS:
		break;

		case SOLICITUD_JOB:
		break;

		case RTA_SOLICITUD_JOB:
		break;

		case NOTIFICACION_RESUL:
		break;

		case EJECUTAR_MAP:
		break;

		case EJECUTAR_RED:
		break;

		case SOLICITUD_ARCHIVO:
		break;

		case RTA_SOLICITUD_ARCHIVO:
		break;

		default:
			perror("El protocolo no se encuentra definido");
			exit(-1);

}

	return bufferSerializado;

}

