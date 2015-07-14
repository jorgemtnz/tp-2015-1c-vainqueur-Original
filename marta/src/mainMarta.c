#include "marta.h"

int main(int argc, char **argv)
{
	// Toda esta secuencia es por job, asi que ir pensando en hacer una void* para
	// meterlo adentro de un hilo
	leerArchivoDeConfiguracion();

	void* buffer = malloc(sizeof(int));

	vg_fdMarta = crearSocket();
	asociarSocket(vg_fdMarta,vg_martaPuerto);
	escucharSocket(vg_fdMarta,vg_conexionesPermitidas);
	vg_fdJob = aceptarConexionSocket(vg_fdMarta);

	recibirPorSocket(vg_fdJob,buffer,sizeof(int));
	printf("Mensaje recibido: %s\n", buffer);

//	// Envia pedido
//	char mensaje[] = "Aplica una rutina en\n"
//					 "Nodo 1, Bloque 2\n"
//					 "Nodo 2, Bloque 1\n"
//					 "Nodo 4, Bloque 3\n";
//
//	enviarPorSocket(vg_fdJob, mensaje, sizeof(mensaje));

	cerrarSocket(vg_fdMarta);
	return 0;

}
