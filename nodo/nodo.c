#include "nodo.h"

void levantarArchivoConfiguracion() {
	char* temporal;
	t_config* archivoConfig;

	*archivoConfig = config_create(RUTACONFIGNODO);

	*vg_puerto_FS 	= config_get_int_value(archivoConfig, "PUERTO_FS");
	*vg_ip_FS 		= config_get_string_value(archivoConfig, "IP_FS");
	*vg_archivo_Bin = config_get_string_value(archivoConfig, "ARCHIVO_BIN");
	*vg_ip_Nodo		= config_get_string_value(archivoConfig, "IP_NODO");
	*vg_dirTemp 	= config_get_string_value(archivoConfig, "DIR_TEMP");
	temporal 		= config_get_string_value(archivoConfig, "NODO_NUEVO");
	*vg_puerto_Nodo = config_get_int_value(archivoConfig, "PUERTO_NODO");

	if (strcmp(temporal, "SI") == 0) {
		*vg_nodo_Nuevo = NODO_NUEVO;
	}
	if (strcmp(temporal, "NO") == 0) {
		*vg_nodo_Nuevo = NODO_NO_NUEVO;
	}

	free(temporal);
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
	return 0;
}

int ejecutarMap(char * nombreArchivoTemporal, char * ptrDireccionMapeo) {
	char *ruta;
	strcpy(ruta,*vg_dirTemp);
	ruta = strcat(ruta, nombreArchivoTemporal);
	if (ejecutarScriptRedireccionandoIO(ruta, ptrDireccionMapeo,
	RUTAMAP, "") < 0) {
		perror("[ERROR] Funcion ejecutarScriptRedireccionandoIO\n");
		exit(EJECUCIONFALLO);
	}
	return EJECUCIONOK;
}


void conectarNodo(nodo_t* datosDelNodo) {
	int fdNodo = crearSocket();
	int numNodo = datosDelNodo->idNodo;
	conectarSocket(fdNodo,*vg_ip_FS,*vg_puerto_FS);
	printf("Nodo: %d conectado al FS con ip %s mediante el puerto %d \n",
			numNodo, *vg_ip_FS, *vg_puerto_FS);
}


int main() {
	nodo_t datosDelNodo;
	datosDelNodo.idNodo = 1;
	return 0;
}
