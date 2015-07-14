/*
 * envioYRecepcionMensaje.c
 *
 *  Created on: 5/7/2015
 *      Author: utnso
 */
#include "filesystem.h"




PaqueteEnvio* enviar(int tipoDeMensaje, void* t_estructura,int fdDestinatario){

	switch(tipoDeMensaje){
		case(0):{//en vez de 1 iria el nombre del protocolo
			PaqueteEnvio* paqueteAEnviar = malloc(PaqueteEnvio);
			t_escritura_bloque* bloqueAEscribir = (t_escritura_bloque*) t_estructura;
			size_t tamanioMensaje = sizeof(int)+VEINTEMEGAS;
			paqueteAEnviar->tamanioMensaje = malloc(tamanioMensaje);
			memcpy(buffer,&(bloqueAEscribir->numeroDeBloque),sizeof(bloqueAEscribir->numeroDeBloque));
			size_t desplazamietno = sizeof(bloqueAEscribir->numeroDeBloque);
			memcpy(buffer+desplazamietno,&(bloqueAEscribir->archivo),VEINTEMEGAS);
				//aca iria la funcion serializar que devuelve un paquete a enviar
			//aca iria el send del tamanio del paquete
			//aca iria el send del mensaje

			break;
		}

		case(2):{

		}
	}
}

/*

 case 2:{
		t_jamon* estructuraTemp2 = (t_jamon*) estructura;
		size_t tamanioMensaje2 = sizeof(t_jamon);//obtengo el tamnio del mensaje
		char* buffer2 = malloc(TAMANIOHEADER + tamanioMensaje2);
		memcpy(buffer2, &tamanioMensaje2, sizeof(int));
		int dezplamiento2 = sizeof(int);
		memcpy(buffer2+dezplamiento2,&(estructuraTemp2->altura),sizeof(int));
		dezplamiento2 += sizeof(estructuraTemp2->altura);//se agrega al desplazamiento el datoagregado anteriomente
		memcpy(buffer2+dezplamiento2,&(estructuraTemp2->edad),sizeof(int));
		return strdup(buffer2);
		break;}


	}
 */
