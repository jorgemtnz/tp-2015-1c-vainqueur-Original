#include "protocolo.h"

PaqueteEnvio* serializar(int tipoDeMensaje, void* payLoad, int tamanioPayLoad){
	PaqueteEnvio* paqueteAEnviar = malloc(sizeof(PaqueteEnvio));
	size_t tamanioDelMensaje = tamanioPayLoad + sizeof(int); //+4 por el total del mesnaje, le sumo un sizeof(int) por el header

	paqueteAEnviar->mensaje = malloc(tamanioDelMensaje);
	memcpy(paqueteAEnviar->mensaje,&tipoDeMensaje,sizeof(int));
	size_t desplazameinto = sizeof(int);
	memcpy(paqueteAEnviar->mensaje + desplazameinto,payLoad,tamanioPayLoad);

	paqueteAEnviar->tamanioMensaje = tamanioDelMensaje;
	return paqueteAEnviar;
}

Paquete* deserializar(void* buffer, int tamnioMensaje) {
	Paquete* paqueteDeserial = malloc(sizeof(Paquete));
	memcpy(&(paqueteDeserial->tipoDeMensaje),buffer,sizeof(int));
	int dezplazamiento = sizeof(int);
	size_t tamanioALeerDelBuffer = tamnioMensaje - dezplazamiento;
	paqueteDeserial->payLoad = malloc(tamanioALeerDelBuffer);
	memcpy(paqueteDeserial->payLoad, buffer + dezplazamiento,tamanioALeerDelBuffer);
	return paqueteDeserial;
}
