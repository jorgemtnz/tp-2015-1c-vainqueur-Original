
#ifndef PROTOCOLO_H_
#define PROTOCOLO_H_

#include <stdio.h>
#include <string.h>
#include <src/commons/string.h>
#include <src/filesystem.h>

#define	ARCHIVO_CARGA_INICIAL 0
#define	ESCRITURA_BLOQUE 1
#define	INFORMAR_UBICACION_ARCHIVOS	2
#define	SOLICITUD_JOB 3
#define	RTA_SOLICITUD_JOB 4
#define	NOTIFICACION_RESUL 5
#define	EJECUTAR_MAP 6
#define	EJECUTAR_RED 7
#define	SOLICITUD_ARCHIVO 8
#define	RTA_SOLICITUD_ARCHIVO 9

#define UN_BYTE 1


// El separador del protocolo
const char * SEPARADOR = "$";

// Función polimórfica que retorna el buffer contenido en la estructura del protocolo dado
void * obtenerEstructura(char *);

#endif /* PROTOCOLO_H_ */
