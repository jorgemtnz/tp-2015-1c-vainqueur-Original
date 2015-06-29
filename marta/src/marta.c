#include "marta.h"

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

void solicitarBloquesAFilesystem(char * archivoAProcesar)
{
	int fdMarta = crearSocket();
	conectarSocket(fdMarta, vg_ipFilesystem,vg_puertoFilesystem);
	char mensaje[100] = "Solicito el archivo: ";
	strcat(mensaje, archivoAProcesar);
	enviarPorSocket(fdMarta,mensaje,sizeof(mensaje));
}
void leerArchivoDeConfiguracion() {
	printf("Ingrese la ruta del archivo de configuracion");
	scanf("%s", rutaArchConfig);
	t_config* archivoConfig;
	archivoConfig = config_create(rutaArchConfig);
	vg_puertoFilesystem = config_get_int_value(archivoConfig, "PUERTO_FILESYSTEM");
	vg_martaPuerto = config_get_int_value(archivoConfig, "PUERTO_MARTA");
	vg_ipFilesystem = strdup(config_get_string_value(archivoConfig, "IP_FILESYSTEM"));

	config_destroy(archivoConfig);
}

/*  aun no terminada
 void evaluarSolicitudMapper(char * nombreArchivo) {
 t_informacionDelArchivo* ptrInformacionDelArchivo;

 list_find(marta->listaInformacionDelArchivo,(nombreArchivo==));

 }*/


#define ACEPTA_COMBINER 1
#define NO_ACEPTA_COMBINER 0


void crearTrabajo(char* solicitud){

}

void recibirUnaPeticionDeJob(){
	// Funcion pendiente a que se termine el protocolo
	/*
	int fdMarta = crearSocket();
	asociarSocket(fdMarta,vg_martaPuerto);
	escucharSocket(fdMarta,);

	desEncriptarMensaje();
	*/
}

typedef struct solicitud {
	t_list* listaNombresFunciones;
	int 	soportaCombiner; 			//1 si soporta 0 si no soporta
	char * 	nombreArchivoATrabajar;
	int 	estado; 					//1 completado 0 en espera
} t_solicitud;

void buscarUbicacionDelArchivo(t_solicitud solTarea){

}

void crearTarea(t_solicitud solTarea){

	buscarUbicacionDelArchivo(solTarea);{
		comprobarCargaDeHilosEnNodos();
		verificarTablaDeBLoquesDelArchivo();
	}

	demandarHilosPorBloques();	// Un bloque = un hilo

	armarTareaParaJob();


}



















