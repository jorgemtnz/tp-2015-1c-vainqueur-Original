//#include "protocolo.h"
//
//int obtenerHeader(void* buffer) {
//
//char* primerChar = malloc(sizeof(char));
//
//	int header = 0;
//	(char*) buffer;
//	primerChar = string_substring_until(buffer, UN_BYTE);
//	header = (*(primerChar)) - '0'; //Lo paso a int
//	close(primerChar);
//	return header;
//}
//
//char * obtenerPayload(void* buffer) {
//	char* payload = malloc(sizeof(char*));
//
//	payload = string_substring_from(buffer, UN_BYTE);
//
//	return payload;
//}
//
//void * obtenerEstructura(void * buffer) {
//
//	int header;
//	char* payload;
//	void* bufferConEstructura;
//
//	header = obtenerHeader(buffer);
//
//	payload = obtenerPayload(buffer);
//
//	switch (header) {
//
//	case ARCHIVO_CARGA_INICIAL:
//
//		bufferConEstructura = payload;
//
//		break;
//
//	case ESCRITURA_BLOQUE:
//
//		 t_escrituraBloque escribir_en_bloque;
//
//		 escribir_en_bloque.numeroDeBloque = string_substring_until( payload, UN_BYTE);
//		 escribir_en_bloque.archivo = string_substring_from( payload, UN_BYTE);
//
//		 bufferConEstructura = (void *)escribir_en_bloque;
//
//		break;
//
//	case INFORMAR_UBICACION_ARCHIVOS:
//		break;
//
//	case SOLICITUD_JOB:
//		break;
//
//	case RTA_SOLICITUD_JOB:
//		break;
//
//	case NOTIFICACION_RESUL:
//		break;
//
//	case EJECUTAR_MAP:
//		break;
//
//	case EJECUTAR_RED:
//		break;
//
//	case SOLICITUD_ARCHIVO:
//		break;
//
//	case RTA_SOLICITUD_ARCHIVO:
//		break;
//
//	default:
//		perror("El protocolo no se encuentra definido");
//		exit(-1);
//
//	}
//
//	return bufferConEstructura;
//
//}
//// Serializar
//void * prepararParaEnviar(int protocolo, void * buffer) {
//
//	t_escrituraBloque* contenido;
//
//	char * bufferSerializado;
//
//
//	switch (protocolo) {
//
//	case ARCHIVO_CARGA_INICIAL:
//		//Es un archivo(char*), no tiene estructura.
//
//		bufferSerializado = buffer;
//
//		break;
//
//	case ESCRITURA_BLOQUE:
//
//		contenido = (t_escrituraBloque *)buffer;
//
//		//Preparo el Protocolo
//		int protocoloAux = protocolo + '0';
//		char * protocoloStr = &protocoloAux;
//
//		//Preparo el Bloque
//		char * bloqueListo;
//		bloqueListo = contenido->bloqueListo;
//
//		//Preparo el numero de copia
//		int numeroCopia;
//		numeroCopia = (contenido->unNodoBloque.numeroCopia) + '0';
//		char * numeroCopiaStr = &numeroCopia;
//
//		// Preparo el nro de bloque del nodo
//		int nroBloque = (contenido->unNodoBloque.numeroDeBloqueDelNodo) + '0';
//		char* nroBloqueStr = &nroBloque;
//
//		// Preparo el nro de nodo
//		int nroNodo = (contenido->unNodoBloque.numeroNodo) + '0';
//			char* nroNodoStr = &nroNodo;
///*
//		printf("%s\n", bloqueListo);
//		printf("%s\n",numeroCopiaStr);
//*/
//		size_t tamanioBuffer = 5+sizeof(bloqueListo)+sizeof(numeroCopiaStr) + sizeof(protocoloStr) + sizeof(nroBloqueStr);
//
//		bufferSerializado = (char *) malloc(tamanioBuffer);
//
//		strcpy(bufferSerializado, protocoloStr);
//		strcat(bufferSerializado, SEPARADOR);
//		strcat(bufferSerializado, bloqueListo);
//		strcat(bufferSerializado, SEPARADOR);
//		strcat(bufferSerializado,numeroCopiaStr);
//		strcat(bufferSerializado, SEPARADOR);
//		strcat(bufferSerializado,nroBloqueStr);
//		strcat(bufferSerializado, SEPARADOR);
//		strcat(bufferSerializado,nroNodo);
//
//		(void*)bufferSerializado;
//		break;
//
//	case INFORMAR_UBICACION_ARCHIVOS:
//		break;
//
//	case SOLICITUD_JOB:
//		break;
//
//	case RTA_SOLICITUD_JOB:
//		break;
//
//	case NOTIFICACION_RESUL:
//		break;
//
//	case EJECUTAR_MAP:
//		break;
//
//	case EJECUTAR_RED:
//		break;
//
//	case SOLICITUD_ARCHIVO:
//		break;
//
//	case RTA_SOLICITUD_ARCHIVO:
//		break;
//
//	default:
//		perror("El protocolo no se encuentra definido");
//		exit(-1);
//
//	}
//	return bufferSerializado;
//}
