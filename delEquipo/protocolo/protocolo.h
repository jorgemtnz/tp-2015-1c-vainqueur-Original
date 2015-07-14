// Comentado porque falta terminar y no compila

//#ifndef PROTOCOLO_H_
//#define PROTOCOLO_H_
//
//#include <stdio.h>
//#include <src/commons/string.h>
//#include <stdlib.h>
//#include <memory.h>
////++++++++++++++++++++++++++++ Constantes ++++++++++++++++++++++++++++++++++
//#define	ARCHIVO_CARGA_INICIAL 0
//#define	ESCRITURA_BLOQUE 1
//#define	INFORMAR_UBICACION_ARCHIVOS	2
//#define	SOLICITUD_JOB 3
//#define	RTA_SOLICITUD_JOB 4
//#define	NOTIFICACION_RESUL 5
//#define	EJECUTAR_MAP 6
//#define	EJECUTAR_RED 7
//#define	SOLICITUD_ARCHIVO 8
//#define	RTA_SOLICITUD_ARCHIVO 9
//
//#define UN_BYTE 1
//
////++++++++++++++++++++++++++++Variables Globales++++++++++++++++++++++++++++++++
//// El separador del protocolo
//const char * SEPARADOR = "$";
//
////++++++++++++++++++++++++++++Estructuras ++++++++++++++++++++++++++++++++++++++
//
//typedef struct unNodoBloqueParaEnviar{
//	int numeroCopia; // 0 original, 1 copia 1, n copia n.
//	int numeroNodo;
//	int numeroDeBloqueDelNodo;
//}unNodoBloqueParaEnviar;
//
//typedef struct t_escrituraBloque{
//	char* bloqueListo;
//	unNodoBloqueParaEnviar unNodoBloque;
//}t_escrituraBloque;
//
//
////+++++++++++++++++++++++++++Funciones Principales+++++++++++++++++++++++++++++++
//// Función polimórfica que retorna el buffer contenido en la estructura del protocolo dado.
//void * obtenerEstructura(void *);
//
//// Función polimórfica que recibe como primer parametro los datos que se van a enviar por socket
////con una estructura específica.
//// El segundo parametro que recibe es el protocolo que se ubicará delante del string devuelto.
//// devuelve un string con cada valor de esa estructura separado por un separador. El primer byte del
//// string devuelto es el protocolo
//void * prepararParaEnviar(int, void *);
//
////+++++++++++++++++++++++++ Funciones Auxiliares+++++++++++++++++++++++++++++++++++
//int obtenerHeader(void *);
//
//char * obtenerPayload(void *);
//
//
//#endif
