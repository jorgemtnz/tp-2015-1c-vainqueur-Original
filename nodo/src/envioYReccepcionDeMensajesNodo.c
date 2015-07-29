/*
 * envioYReccepcionDeMensajesNodo.c
 *
 *  Created on: 28/7/2015
 *      Author: utnso
 */
#include "nodo.h"

void enviar(int tipoDeMensaje, void* t_estructura, int fdDestinatario)
{
	switch (tipoDeMensaje)
	{
	case (CONECXION_NODO):
	{ // cuando se manda una conecxion de nodo

		t_nodo* unNodo = (t_nodo*) t_estructura;
		int tamanioStringIp = sizeof(char) * (strlen(vg_ip_Nodo) + 1);

		int tamanioPayload = sizeof(vg_nodo->idNodo) + sizeof(vg_puerto_Nodo)
				+ tamanioStringIp + sizeof(int) + sizeof(vg_nodo_Nuevo) + sizeof(vg_tamanioArchivo); //el ultimo sizeof(int) es para agregarle el tamanio del string al payload

		void* payload = malloc(tamanioPayload);

		memcpy(payload, &(vg_nodo->idNodo), sizeof(vg_nodo->idNodo));
		int desplazamiento = sizeof(vg_nodo->idNodo);

		memcpy(payload + desplazamiento, &(vg_puerto_Nodo),
				sizeof(vg_puerto_Nodo));
		desplazamiento += sizeof(vg_puerto_Nodo);

		memcpy(payload + desplazamiento, &(tamanioStringIp), sizeof(int));
		desplazamiento += sizeof(int);

		memcpy(payload + desplazamiento, vg_ip_Nodo, tamanioStringIp);
		desplazamiento += tamanioStringIp;

		memcpy(payload + desplazamiento, &(vg_nodo_Nuevo), sizeof(vg_nodo_Nuevo));
		desplazamiento += sizeof(vg_nodo_Nuevo);

		memcpy(payload + desplazamiento, &(vg_tamanioArchivo), sizeof(vg_tamanioArchivo));


		PaqueteEnvio* unPaquete = serializar(tipoDeMensaje, payload,
				tamanioPayload);

		enviarPorSocket(fdDestinatario, &(unPaquete->tamanioMensaje),
				sizeof(int));
		enviarPorSocket(fdDestinatario, unPaquete->mensaje,
				unPaquete->tamanioMensaje);
// solo si el ayudante dice que se debe hacer
		//ftell() para decir donde esta el ptro del archivo de lect/ escritura
//		int fdArchivo =abreArchivo(RUTACONFIGNODO);
//        // debo cambiar el SI del archivo config
//
//		cierraArchivo(fdArchivo);

		printf("mensaje enviado al servidor");
		break;

	}
	case (BLOQUE):
	{
		char* bloque = (char*) t_estructura;
		size_t tamanioPayload = VEINTEMEGAS;
		void* payload = malloc(tamanioPayload);
		memcpy(payload, bloque, VEINTEMEGAS);

		PaqueteEnvio* unPaquete = serializar(BLOQUE, payload, tamanioPayload);

		enviarPorSocket(fdDestinatario, &(unPaquete->tamanioMensaje),
				sizeof(int));
		enviarPorSocket(fdDestinatario, unPaquete->mensaje,
				unPaquete->tamanioMensaje);

		printf("mensaje enviado al servidor");
		break;
	}

	}
}
void* recibir(int fdReceptor)
{
	size_t tamanioMensaje;
	recibirPorSocket(fdReceptor, &tamanioMensaje, sizeof(int));
	void* buffer = malloc(tamanioMensaje);
	recibirPorSocket(fdReceptor, buffer, tamanioMensaje);
	Paquete* unPaquete = deserializar(buffer, tamanioMensaje); //primer deserializado

	interpretarPaquete(unPaquete, fdReceptor);
	return NULL;
}

void* interpretarPaquete(Paquete* unPaquete, int fdReceptor)
{

	switch (unPaquete->tipoDeMensaje)
	{
	case (LECTURA):
	{ //se debe previamente haber abierto el archivo bin del nodo
		int numeroDeBlouqe;
		memcpy(&numeroDeBlouqe, unPaquete->payLoad, sizeof(int)); //saco el numero de bloque que debo leer de mi datos.bin
		char* bloque = getBloque(numeroDeBlouqe);
		enviar(BLOQUE, bloque, fdReceptor);

		// acceder al bloque del nodo y ese string es el que se manda de vuelta.
		//enviar();     // envia por socket el bloque al servidor
		break;
	}
	case (DESCONECTAR_NODO):
	{		// quizas se deba poner en el nodo.h, --- verificar al hacer pull

		cerrarSocket(fdReceptor);
		vg_desconectar = 1;	// para salir del while en el hilo para el clienteFS
		break;
	}
	case (ESCRITURA):{
		int numeroDeBloque;
		char* bloque;
		memcpy(&numeroDeBloque,	unPaquete->payLoad, sizeof(int));
		size_t desplazamiento = sizeof(int);
		memcpy(bloque,unPaquete->payLoad + desplazamiento, VEINTEMEGAS);
		setBloque(numeroDeBloque, bloque);
    break;
	}


	default:
		return NULL;
	}	// del switch
}
