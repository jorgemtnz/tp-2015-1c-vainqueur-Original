#include "marta.h"

// Terminadas
char* recibirSolicitudDeJob() {
	t_solicitud* solicitudTrabajo = malloc(sizeof(t_solicitud));
	char buffer[TAMANIO_SOLICITUD];
	vg_fdMarta = crearSocket();
	asociarSocket(vg_fdMarta, vg_martaPuerto);
	escucharSocket(vg_fdMarta, vg_conexionesPermitidas);
	vg_fdJob = aceptarConexionSocket(vg_fdMarta);

	recibirPorSocket(vg_fdJob, buffer, TAMANIO_SOLICITUD);
	// Deserealizar buffer recibido que representa solicitudTrabajo

	return buffer;
}

char * generarNombreAlmacenado(char * nombreArchivo, char * nombreFuncion) {
	char * tiempoActual;
	tiempoActual = temporal_get_string_time();
	char * nombreArchivoAux = strdup(nombreArchivo);
	strcat(nombreArchivoAux, ".");
	strcat(nombreArchivoAux, nombreFuncion);
	strcat(nombreArchivoAux, ".");
	strcat(nombreArchivoAux, tiempoActual);
	return nombreArchivoAux;
}

void solicitarBloquesAFilesystem(char * archivoAProcesar) {
	int fdMarta = crearSocket();
	conectarSocket(fdMarta, vg_ipFilesystem, vg_puertoFilesystem);
	char mensaje[100] = "Solicito el archivo: ";
	strcat(mensaje, archivoAProcesar);
	int length =  sizeof(mensaje);
	enviarPorSocket(fdMarta, mensaje, &length);
}

void leerArchivoDeConfiguracion() {
//	printf("Ingrese la ruta del archivo de configuracion: ");
//	fflush(stdin);
//	scanf("%s", rutaArchConfig);
	// /home/utnso/TPOperativos/marta/configMarta.cfg
	char* rutaArchConfig;
	t_config* archivoConfig = NULL;
	rutaArchConfig = "/home/utnso/TPOperativos/marta/config_Marta.cfg";
	if (checkearRutaArchivoConfig(rutaArchConfig) == -1) {
		perror("[ERROR]: Archivo de configuracion no encontrado");
		log_error(logger, "[ERROR]: Archivo de configuracion no encontrado");
		exit(-1);
	}

	else {
		archivoConfig = config_create(rutaArchConfig);
		vg_puertoFilesystem = config_get_int_value(archivoConfig,
				"PUERTO_FILESYSTEM");
		vg_martaPuerto = config_get_int_value(archivoConfig, "PUERTO_MARTA");
		vg_conexionesPermitidas = config_get_int_value(archivoConfig,
				"CONEXIONES_PERMITIDAS");
		vg_ipFilesystem = strdup(
				config_get_string_value(archivoConfig, "IP_FILESYSTEM"));

	}

	config_destroy(archivoConfig);
}

// Sin terminar

//void planificarTrabajos();							// Falta implementar
//void almacenarResultado(char * nombreDelArchivo);	// Falta implementar
//void solicitarMapper();								// Falta implementar
//void solicitarReducer(int soportaCombiner);			// Falta implementar
//int  mandarNodoBloque(int numeroBloque);			// Falta implementar
//void noRepiteNodo();								// Falta implementar
//void evaluarSolicitudMapper(char * nombreArchivo);  // Falta implementar

// void evaluarSolicitudMapper(char * nombreArchivo) {
// t_informacionDelArchivo* ptrInformacionDelArchivo;
//
// list_find(marta->listaInformacionDelArchivo,(nombreArchivo==));
//
// }
//
//
//
//
//void crearTrabajo(char* solicitud){
//
//}
//
//void recibirUnaPeticionDeJob(){
//	// Funcion pendiente a que se termine el protocolo
//
//	int fdMarta = crearSocket();
//	asociarSocket(fdMarta,vg_martaPuerto);
//	escucharSocket(fdMarta,);
//
//	desEncriptarMensaje();
//
//}
//
//
//void buscarUbicacionDelArchivo(t_solicitud solTarea){
//
//}
//
//void crearTarea(t_solicitud solTarea){
//
//	buscarUbicacionDelArchivo(solTarea);{
//		comprobarCargaDeHilosEnNodos();
//		verificarTablaDeBLoquesDelArchivo();
//	}
//
//	demandarHilosPorBloques();	// Un bloque = un hilo
//
//	armarTareaParaJob();
//
//
//}
