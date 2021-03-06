#include "demo.h"
void imprimirAlumno(unaStr* alumno);

int main()
{
	// Seteamos struc
	unaStr *  lucas = malloc(sizeof(unaStr));
	lucas->edad = 20;
	lucas->promedio = 7,6;
	lucas->nombre = strdup("Lucas");

	imprimirAlumno(lucas);

	// Creamos buffer para serealizar
	// Magia negra
	size_t tamanioMensaje = sizeof(unaStr) + strlen(lucas->nombre) - sizeof(char*);

	void* payload = malloc(tamanioMensaje);
	memcpy(payload, &(lucas->edad) , sizeof(lucas->edad));
	size_t desplazamiento = sizeof(lucas->edad);
	memcpy(payload + desplazamiento, &(lucas->promedio) , sizeof(lucas->promedio));
	desplazamiento += sizeof(float);
	memcpy(payload + desplazamiento, &(lucas->nombre) , strlen(lucas->nombre));

	// Serealizamos
	PaqueteEnvio * unPaq = serializar(NO_IMPORTA_NUMERO, payload, tamanioMensaje);

	int fdServidor = crearSocket();
	asociarSocket(fdServidor, PUERTO);
	escucharSocket(fdServidor,3);

	int fdCliente = aceptarConexionSocket(fdServidor);

	printf("El tamanio que esto mandando, tamanioMensaje = %d\n",unPaq->tamanioMensaje);
	int len = sizeof(int);
	enviarPorSocket(fdCliente,&(unPaq->tamanioMensaje),&len);
	// Manda cuanto pesa el mensaje

	enviarPorSocket(fdCliente, unPaq->mensaje, &tamanioMensaje);
	// Manda el mensaje en si


	free(lucas);
	free(payload);

	cerrarSocket(fdServidor);
	return 0;
}
void imprimirAlumno(unaStr* alumno){
	printf("Nombre del alumno:\t[%s]\n",alumno->nombre);
	printf("Edad del alumno:\t[%d]\n",alumno->edad);
	printf("Promedio del alumno:\t[%.2f]\n",alumno->promedio);
	printf("\n");
}
