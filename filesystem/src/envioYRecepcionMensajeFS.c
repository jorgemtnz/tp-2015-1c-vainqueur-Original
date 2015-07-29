#include "filesystem.h"

void enviar(int tipoDeMensaje, void* t_estructura,int fdDestinatario) {
	switch (tipoDeMensaje) {
	case (ESCRITURA): { // cuando se manda un bloque
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

void* recibir(int fdReceptor){
	size_t tamanioMensaje;

	recibirPorSocket(fdReceptor,&tamanioMensaje,sizeof(int));

	void* buffer = malloc(tamanioMensaje);

	recibirPorSocket(fdReceptor,buffer,tamanioMensaje);
	Paquete* unPaquete = deserializar(buffer,tamanioMensaje);//primer deserializado
//da un tratamiento al mensaje en especifico
	 interpretarPaquete ( unPaquete, fdReceptor);
}

void* interpretarPaquete(Paquete* unPaquete, int fdReceptor){

	switch(unPaquete->tipoDeMensaje){
		case(CONEXION_NODO):{//recibe el mensaje de coneccion de un nodo
			nod* nodo;
			 int tamanioStringIp;
			nodo = crearNodo();  // se crea el nodo como desconectado porque  aun no se
			                     //ha agregado a la lista de nodos activos(CONECTADOS)

		//primero se le el identificador del nodo que es su numero
			 memcpy(&(nodo->numero),unPaquete->payLoad, sizeof(int));
			 size_t desplazamiento = sizeof(nodo->numero);
			 memcpy(&(nodo->puerto), unPaquete->payLoad+ desplazamiento, sizeof(int));
			 desplazamiento += sizeof(nodo->puerto);
			 memcpy(&(tamanioStringIp) , unPaquete->payLoad + desplazamiento,sizeof(int) );
			 nodo->ipNodo[tamanioStringIp];

			 memcpy(&(nodo->ipNodo), unPaquete->payLoad + desplazamiento, tamanioStringIp);
			 desplazamiento +=tamanioStringIp;
			 memcpy(&(nodo->esNuevo), unPaquete->payLoad + desplazamiento, sizeof(int));

						 				//validar de que no sea un nodo viejo
			 if ( nodo->esNuevo == SI)
			 {
				//agregarlo
				//agregar su espacio y en base a eso la cantidad de bloques de las listaBloques de un nodo
			 list_add(FILESYSTEM->listaNodosActivos, nodo);
			 } else{
				 nodo->estado = CONECTADO;
			 }

             if( FILESYSTEM->listaNodosActivos->elements_count > vg_cant_MinNodosOperar)
            	 FILESYSTEM->estado = OPERATIVO;
			break;
		}
		case(SOLICITUD_ARCHIVO):{//MaRTA pide un archivo
			//buscar archivo y sus ubicaciones nodoBloque
			//usar la funcion enviar de arriba para serializar esa lista y mandarsela a MaRTA

			break;
		}
		case(BLOQUE):{//problema porque hay dos funciones de consola que solicitan un bloque copiar bloque y la funcion de md5
			char* bloque;
			memcpy(bloque,unPaquete->payLoad,VEINTEMEGAS);
			return bloque;

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
