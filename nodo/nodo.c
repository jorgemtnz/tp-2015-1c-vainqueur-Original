#include "nodo.h"

void levantarArchivoConfiguracion() {
	char * temporal;
	t_config * archivoConfig;
	archivoConfig = config_create(RUTACONFIG);
	puertoFS = config_get_int_value(archivoConfig, "PUERTO_FS");
	puertoNodo = config_get_int_value(archivoConfig, "PUERTO_NODO");
	ipFS = config_get_string_value(archivoConfig, "IP_FS");
	ipNodo = config_get_string_value(archivoConfig, "IP_NODO");
	archivoBin = config_get_string_value(archivoConfig, "ARCHIVO_BIN");
	dirTemp = config_get_string_value(archivoConfig, "DIR_TEMP");
	temporal = config_get_string_value(archivoConfig, "NODO_NUEVO");
	if (strcmp(temporal, "SI") == 0) {
		nodoNuevo = NODO_NUEVO;
	}
	if (strcmp(temporal, "NO") == 0) {
		nodoNuevo = NODO_NUEVO;
	}
	config_destroy(archivoConfig);
}

int informarEjecucionAJob(nodo_t* datosDelNodo, char* ipJob, int puertoJob,
		int comoTerminoLaEjecucion) {
	int fdNodo = crearSocket();
	conectarSocket(fdNodo, ipJob, puertoJob);
	printf("Nodo: %d conectado al Job con ip %s mediante el puerto %d \n",
			datosDelNodo->idNodo, ipJob, puertoJob);
	enviarPorSocket(fdNodo, (void *) comoTerminoLaEjecucion, sizeof(int));
	printf("Nodo: Mensaje Enviado al Job \n");
	cerrarSocket(fdNodo);
	return 0;
}

int ejecutarReduce(int soportaCombiner) {
	if (soportaCombiner) {

	}
}
int ejecutarMap(char * nombreArchivoTemporal, char * ptrDireccionMapeo) {
	char ruta[60] = "/tmp/";
	strcat(ruta, nombreArchivoTemporal);
	if (ejecutarScriptRedireccionandoIO(ruta, ptrDireccionMapeo,
	RUTAMAP, "") < 0) {
		perror("[ERROR] Funcion ejecutarScriptRedireccionandoIO\n");
		exit(EJECUCIONFALLO);
	}
	return EJECUCIONOK;
}

int main() {
	nodo_t datosDelNodo;
	datosDelNodo.idNodo = 1;
	return 0;
}

void conectarNodo(nodo_t* datosDelNodo, char* ipFS, int puertoFS) {
	int fdNodo = crearSocket();
	conectarSocket(fdNodo, ipFS, puerto);
	printf("Nodo: %d conectado al FS con ip %s mediante el puerto %d \n",
			datosDelNodo->idNodo, ipFS, puerto);
}

