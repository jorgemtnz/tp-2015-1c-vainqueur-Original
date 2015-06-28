#include "nodo.h"

void levantarArchivoConfiguracion() {
	char* temporal;
	t_config* archivoConfig;
	archivoConfig = config_create(RUTACONFIGNODO);
	vg_puerto_FS = config_get_int_value(archivoConfig, "PUERTO_FS");
	vg_ip_FS = config_get_string_value(archivoConfig, "IP_FS");
	vg_archivo_Bin = config_get_string_value(archivoConfig, "ARCHIVO_BIN");
	vg_ip_Nodo = config_get_string_value(archivoConfig, "IP_NODO");
	vg_dirTemp = config_get_string_value(archivoConfig, "DIR_TEMP");
	temporal = config_get_string_value(archivoConfig, "NODO_NUEVO");
	vg_puerto_Nodo = config_get_int_value(archivoConfig, "PUERTO_NODO");

	if (strcmp(temporal, "SI") == 0) {
		vg_nodo_Nuevo = NODO_NUEVO;
	}
	if (strcmp(temporal, "NO") == 0) {
		vg_nodo_Nuevo = NODO_NO_NUEVO;
	}

	free(temporal);
	config_destroy(archivoConfig);
}

int informarEjecucionAJob(t_nodo* datosDelNodo, char* ipJob, int puertoJob,
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
//revisar el funcionamiento de esta funcion porque el map solo se hace sobre un bloque
int ejecutarMap(char * nombreArchivoTemporal, char * ptrDireccionMapeo) {
	char *ruta;
	ruta = RUTAMAP;
	strcpy(ruta, vg_dirTemp);
	ruta = strcat(ruta, nombreArchivoTemporal);
	if (ejecutarScriptRedireccionandoIO(ruta, ptrDireccionMapeo,
	RUTAMAP, "") < 0) {
		perror("[ERROR] Funcion ejecutarScriptRedireccionandoIO\n");
		exit(EJECUCIONFALLO);
	}
	return EJECUCIONOK;
}

void conectarNodo(t_nodo* datosDelNodo) {
	int fdNodo = crearSocket();
	int numNodo = datosDelNodo->idNodo;
	conectarSocket(fdNodo, vg_ip_FS, vg_puerto_FS);
	printf("Nodo: %d conectado al FS con ip %s mediante el puerto %d \n",
			numNodo, vg_ip_FS, vg_puerto_FS);
}
//no se puede devolver un array, da error, por eso mejor seria que devuelva un ptr al array
bufferVeinteMegas* getBloque(int numeroDeBloque) {
	int fdDatosBin = open(vg_archivo_Bin, O_RDONLY, 0);
	bufferVeinteMegas* buffer = malloc(sizeof(bufferVeinteMegas));
	long pos = (numeroDeBloque - 1) * VEINTEMEGAS;
	if (lseek(fdDatosBin, pos, SEEK_SET) == 0) {
		read(fdDatosBin, &buffer, sizeof(VEINTEMEGAS));

	} else {
		perror("[ERROR] error al leer un bloque\n");
		exit(-1);
	}
	close(fdDatosBin);
	return buffer;
}
int setBloque(int numeroDeBloque, bufferVeinteMegas buffer) {
	int fdDatosBin = open(vg_archivo_Bin, O_RDWR, 0);
	long pos = (numeroDeBloque - 1) * VEINTEMEGAS;
	if (lseek(fdDatosBin, pos, SEEK_SET) == 0) {
		write(fdDatosBin, &buffer, sizeof(VEINTEMEGAS));

	} else {
		perror("[ERROR] error al escribir un bloque\n");
		exit(-1);
	}
	close(fdDatosBin);
	return EJECUCIONOK;
}

char* getFileContent(char* nombreDelArchivo) { //devuelve archivo del tmp
	char* dirArchiv = string_new();
	string_append(&dirArchiv, vg_dirTemp);
	string_append(&dirArchiv, nombreDelArchivo);
	int fdArchvTmp = open(dirArchiv, O_RDONLY, 0);
	int tamanioArch = lseek(fdArchvTmp, 0, SEEK_END); //cuenta tamanio del archivo
//	bufferTemp buffer[tamanioArch];
	char* buffer = malloc(sizeof(tamanioArch));
	if (lseek(fdArchvTmp, 0, SEEK_SET) == 0) { //se posiciona devuelta en el inicio del archivo
		read(fdArchvTmp, buffer, sizeof(tamanioArch));
	} else {
		perror("[ERROR] no se pudo abrir el archivo temporal del nodo\n");
		exit(-1);
	}
	close(fdArchvTmp);
	return buffer; // esto que se regresa es un ptr a la primera posición del arreglo
}
