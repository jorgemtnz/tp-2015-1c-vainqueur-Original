#include "filesystem.h"

void enviar(int tipoDeMensaje, void* t_estructura,int fdDestinatario) {
	switch (tipoDeMensaje) {
	case (ESCRITURA): {
		t_escritura_bloque* bloqueAEscribir = (t_escritura_bloque*) t_estructura;
		size_t tamanioPayload = VEINTEMEGAS;

		void * payload = malloc(tamanioPayload);
		memcpy(payload, &(bloqueAEscribir->numeroDeBloque),
				sizeof(bloqueAEscribir->numeroDeBloque));
		size_t desplazamietno = sizeof(bloqueAEscribir->numeroDeBloque);
		memcpy(payload + desplazamietno, &(bloqueAEscribir->archivo),
		VEINTEMEGAS);

		PaqueteEnvio * unPaquete = serializar(ESCRITURA, payload,
				tamanioPayload);
		enviarPorSocket(fdDestinatario,&(unPaquete->tamanioMensaje),sizeof(unPaquete->tamanioMensaje));
		enviarPorSocket(fdDestinatario,unPaquete->mensaje,unPaquete->tamanioMensaje);
		break;
	}
	case (LECTURA): {
		int numeroDeBloque = (int*) t_estructura;
		size_t tamanioPayload = sizeof(int);
		void* payload = malloc(tamanioPayload);
		memcpy(payload, &numeroDeBloque, sizeof(int));
		PaqueteEnvio* unPaquete = serializar(LECTURA, payload, tamanioPayload);
		enviarPorSocket(fdDestinatario,&(unPaquete->tamanioMensaje),sizeof(unPaquete->tamanioMensaje));
		enviarPorSocket(fdDestinatario,unPaquete->mensaje,unPaquete->tamanioMensaje);
		break;
	}
	}
}

void recibir(int fdReceptor){
	size_t tamanioMensaje;
	recibirPorSocket(fdReceptor,&tamanioMensaje,sizeof(int));
	void* buffer = malloc(tamanioMensaje);
	recibirPorSocket(fdReceptor,buffer,tamanioMensaje);
	Paquete* unPaquete = deserializar(buffer,tamanioMensaje);//primer deserializado


	 interpretarPaquete ( unPaquete, fdReceptor);



}

void interpretarPaquete(Paquete* unPaquete, int fdReceptor){

	switch(unPaquete->tipoDeMensaje){
		case(CONEXION_NODO):{//recibe el mensaje de coneccion de un nodo
				//aceptar el nodo
				//validar de que no sea un nodo viejo
				//agregarlo
				//agregar su espacio y en base a eso la cantidad de bloques de las listaBloques de un nodo
			break;
		}
		case(SOLICITUD_ARCHIVO):{//MaRTA pide un archivo
			//buscar archivo y sus ubicaciones nodoBloque
			//usar la funcion enviar de arriba para serializar esa lista y mandarsela a MaRTA

			break;
		}
	}

}














//ver lo del OK para liberar el buffer

//	Guia
//
// case 2:{
//		t_jamon* estructuraTemp2 = (t_jamon*) estructura;
//		size_t tamanioMensaje2 = sizeof(t_jamon);//obtengo el tamnio del mensaje
//		char* buffer2 = malloc(TAMANIOHEADER + tamanioMensaje2);
//		memcpy(buffer2, &tamanioMensaje2, sizeof(int));
//		int dezplamiento2 = sizeof(int);
//		memcpy(buffer2+dezplamiento2,&(estructuraTemp2->altura),sizeof(int));
//		dezplamiento2 += sizeof(estructuraTemp2->altura);//se agrega al desplazamiento el datoagregado anteriomente
//		memcpy(buffer2+dezplamiento2,&(estructuraTemp2->edad),sizeof(int));
//		return strdup(buffer2);
//		break;}
//
//
//	}
//
