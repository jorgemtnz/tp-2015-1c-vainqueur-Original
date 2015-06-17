/*
 * protocolo.c
 *
 *  Created on: 17/6/2015
 *      Author: utnso
 */

#include <stdio.h>
#include <string.h>
#include <protocolo.h>


void * retornarEstructura(char * buffer) {

	char* protocolo = NULL;
	size_t tamano_buffer;

	tamano_buffer = strlen(buffer);

//Tamaño máximo del array que se puede obtener.
	char* bufferSerializado[tamano_buffer];

	bufferSerializado = string_split(buffer, SEPARADOR);

	// Obtengo el Header
	protocolo = string_substring_from( buffer, UN_BYTE);

	// convierto el protocolo a int
	(int) (*(protocolo));

	switch (protocolo)
	{

		case ARCHIVO_CARGA_INICIAL:


		// Es un archivo, por lo tanto la estructura que contiene el payload es t_archivo

		bufferSerializado[1] = string_substring_from( buffer, 2);

	    //Cargo la estructura serializada

		(void*)bufferSerializado;

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
