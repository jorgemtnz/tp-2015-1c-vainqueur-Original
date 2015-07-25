#ifndef MARTA_H_
#define MARTA_H_

// +++++++++++++++++++++++++++++++++++++++ Includes +++++++++++++++++++++++++++++++++++++
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>  // read write
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sockets/sockets.h>
#include <src/commons/collections/list.h>
#include <src/commons/config.h>
#include <src/commons/temporal.h>
#include <src/commons/string.h>
#include <src/commons/txt.h>
#include <semaphore.h>
#include <pthread.h>
// +++++++++++++++++++++++++++++++++++++++ Define +++++++++++++++++++++++++++++++++++++
#define SI 1
#define NO 0
#define COMPLETADO 1
#define EN_ESPERA 0
#define MAPEADO 1;
#define NO_MAPEADO 0;
#define TAMANIOBUFFER 1050
#define TAMANIO_SOLICITUD 200
#define ACEPTA_COMBINER 1
#define NO_ACEPTA_COMBINER 0
#define LONGPATH 200

// +++++++++++++++++++++++++++++++++++++++ Estructuras +++++++++++++++++++++++++++++++++++++
typedef struct estructuraMarta {
	t_list* listaSolicitudes;
	t_list* listaInformacionDelArchivo;
	t_list* listaArchivosProcesados;
} t_estructuraMarta;

typedef struct solicitud {
	char *	nombreArchivoATrabajar;
	t_list* listaNombresFunciones;
	int 	soportaCombiner; //1 si soporta 0 si no soporta
	int 	estado; //1 completado 0 en espera
} t_solicitud;

typedef struct informacionDelArchivo {
	char * nombreArchivo;
	t_list* listaUbicacionBloques;
	int enUso; //Si = 1 / No = 0
} t_informacionDelArchivo;

typedef struct ubicacionBloque {
	int numero;
	t_list* listaRelacionesNodoBloque;
} t_ubicacionBloque;

typedef struct relacionNodoBloque {
	int numeroNodo;
	int numeroBloque;
	int estado;
} t_relacionNodoBloque;

typedef struct archivoProcesado {
	char * nombreArchProcesado;
	int numeroNodo;
	char * ubicacion;
	int aplicoMapper; //Si = 1 / No = 0
	int estado; 
	
} t_archivoProcesado;


// +++++++++++++++++++++++++++++++++++++++ Prototipos +++++++++++++++++++++++++++++++++++++
// Funciones Constructoras hace el malloc de la estructura e inicializa los campos
t_archivoProcesado* crearArchivoProcesado() ;
t_relacionNodoBloque* crearRelacionNodoBloque() ;
t_ubicacionBloque* crearUbicacionBloque() ;
t_informacionDelArchivo* crearInformacionArchivo();
t_solicitud* crearSolicitud();
t_estructuraMarta* crearMarta();

// Funciones Destructoras hace el free de la estructura y libera las listas segun sea necesario
void liberaMemoriaArchivoProcesado(t_archivoProcesado* ptrArchivoProcesado);
void liberaMemoriaRelacionNodoBloque(t_relacionNodoBloque* ptrRelacionNodoBloque);
void liberaMemoriaUbicacionBloque(t_ubicacionBloque* ptrUbicacionBloque);
void liberaMemoriaInformacionArchivo(t_informacionDelArchivo* ptrInformacionArchivo);
void liberaMemoriaNombreFuncion(char* ptrNombreFuncion); // Puntero a string
void liberaMemoriaSolicitud(t_solicitud* ptrSolicitud);
void liberaMemoriaMarta(t_estructuraMarta* ptrMarta) ;
void liberaVG();

// Marta
char* recibirSolicitudDeJob();
char * generarNombreAlmacenado(char * nombreArchivo, char * nombreFuncion);
// [generarNombreAlmacenado] genera el nombre del archivo que se almacena en el temporal
void solicitarBloquesAFilesystem(char * archivoAProcesar);
void leerArchivoDeConfiguracion();

// +++++++++++++++++++++++++++++++++++ Variables Globales +++++++++++++++++++++++++++++++++++
t_estructuraMarta marta;
int vg_martaPuerto;
int vg_puertoFilesystem;
int vg_conexionesPermitidas;
int vg_fdMarta;
int vg_fdJob;
char rutaArchConfig[LONGPATH];
char * vg_ipFilesystem;
unsigned char resultado; // Esta variable recibe el valor de respuesta de exito o no del JOB


#endif /* MARTA_H_ */
