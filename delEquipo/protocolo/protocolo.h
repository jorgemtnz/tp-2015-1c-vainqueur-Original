/*
 * protocolol.h
 *
 *  Created on: 13/7/2015
 *      Author: utnso
 */

#ifndef PROTOCOLO_PROTOCOLO_H_
#define PROTOCOLO_PROTOCOLO_H_
#define	ESCRITURA 0
//#define	ESCRITURA_BLOQUE 1
//#define	INFORMAR_UBICACION_ARCHIVOS	2
//#define	SOLICITUD_JOB 3
//#define	RTA_SOLICITUD_JOB 4
//#define	NOTIFICACION_RESUL 5
//#define	EJECUTAR_MAP 6
//#define	EJECUTAR_RED 7
//#define	SOLICITUD_ARCHIVO 8
//#define	RTA_SOLICITUD_ARCHIVO 9

//#define UN_BYTE 1
typedef struct PaqueteEnvio{
	int tamanioMensaje;
	void* mensaje;
}PaqueteEnvio;

typedef struct Paquete{
	int tipoDeMensaje;
	void* payLoad;
}Paquete;

PaqueteEnvio* serializar(int tipoDeMensaje, void* payLoad, int tamanioPayLoad);
Paquete* deserializar(void* buffer,int tamanioMensaje);


#endif /* PROTOCOLO_PROTOCOLO_H_ */
