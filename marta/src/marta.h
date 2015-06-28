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

// +++++++++++++++++++++++++++++++++++++++ Define +++++++++++++++++++++++++++++++++++++
#define SI 1
#define NO 0
#define COMPLETADO 1
#define EN_ESPERA 0
#define NO_MAPEADO 0;
#define MAPEADO 1;
#define PUERTO_MARTA 6546
#define CONEXIONES_ACEPTA_MARTA 1
#define TAMANIOBUFFER 1050

// +++++++++++++++++++++++++++++++++++++++ Estructuras +++++++++++++++++++++++++++++++++++++
typedef struct estructuraMarta {
	t_list* listaSolicitudes;
	t_list* listaInformacionDelArchivo;
	t_list* listaArchivosProcesados;
} t_estructuraMarta;

typedef struct solicitud {
	t_list* listaNombresFunciones;
	int soportaCombiner; //1 si soporta 0 si no soporta
	char * nombreArchivoATrabajar;
	int estado; //1 completado 0 en espera
} t_solicitud;

typedef char* t_nombreFuncion; // Es un sinonimo de tipo, no una estructura vacia

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

//Variables Globales
int vg_puertoFilesystem;
char * vg_ipFilesystem;

// +++++++++++++++++++++++++++++++++++++++ Prototipos +++++++++++++++++++++++++++++++++++++
// Funciones Constructoras hace el malloc de la estructura e inicializa los campos
t_archivoProcesado* crearArchivoProcesado() ;
t_relacionNodoBloque* crearRelacionNodoBloque() ;
t_ubicacionBloque* crearUbicacionBloque() ;
t_informacionDelArchivo* crearInformacionArchivo();
t_nombreFuncion* crearNombreFuncion();
t_solicitud* crearSolicitud();
t_estructuraMarta* crearMarta();

// Funciones Destructoras hace el free de la estructura y libera las listas segun sea necesario
void liberaMemoriaArchivoProcesado(t_archivoProcesado* ptrArchivoProcesado);
void liberaMemoriaRelacionNodoBloque(t_relacionNodoBloque* ptrRelacionNodoBloque);
void liberaMemoriaUbicacionBloque(t_ubicacionBloque* ptrUbicacionBloque);
void liberaMemoriaInformacionArchivo(t_informacionDelArchivo* ptrInformacionArchivo);
void liberaMemoriaNombreFuncion(t_nombreFuncion ptrNombreFuncion); // Puntero a string
void liberaMemoriaSolicitud(t_solicitud* ptrSolicitud);
void liberaMemoriaMarta(t_estructuraMarta* ptrMarta) ;
void liberaVG();

// Funciones Auxiliares
/* Lucas lo eliminaria
 ** void liberaMemoriaLista(t_list* lista, int* cantElementos, void (*funcionLiberaElemento)(void*));
 ** cuando se llama se escribe-> liberaMemoriaLista(lista,cantElementos,void (*funcionLiberaElemento)(void*);
 ** (void*)funcionLiberaElemento)
 ** Todo lo que comento aca lucas lo borraria
 */

// Marta
char * generarNombreAlmacenado(char * nombreArchivo, char * nombreFuncion); //genera el nombre del archivo que se almacena en el temporal


//!!!! Revisar bien los argumentos que reciben al codificarlas ya que estos fueron pensados medios rapido
//y seguro hacen falta mas y puede que nisiquiera sean estos los que necesita!!!!
void leerArchivoDeConfiguracion();
void planificarTrabajos();							// Falta implementar
void almacenarResultado(char * nombreDelArchivo);	// Falta implementar
void solicitarMapper();								// Falta implementar
void solicitarReducer(int soportaCombiner);			// Falta implementar
int  mandarNodoBloque(int numeroBloque);			// Falta implementar
void noRepiteNodo();								// Falta implementar
void evaluarSolicitudMapper(char * nombreArchivo);  // Falta implementar

// +++++++++++++++++++++++++++++++++++ Variables Globales +++++++++++++++++++++++++++++++++++
t_estructuraMarta marta;
unsigned char resultado; // Esta variable recibe el valor de respuesta de exito o no del JOB
char rutaArchConfig[300];
#endif /* MARTA_H_ */
