#ifndef MARTA_H_
#define MARTA_H_
#define SI 1
#define NO 0
#define COMPLETADO 1
#define EN_ESPERA 0
#define NO_MAPEADO 0;
#define MAPEADO 1;

//------comienzan los include

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>  // read write
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <src/commons/collections/list.h>
#include <src/commons/temporal.h>
#include <src/commons/string.h>
#include <src/commons/txt.h>


//-------comienza estructura-----

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

typedef char * t_nombreFuncion;

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

//-----termina estructura-------

//---------Variables globales-----------------

t_estructuraMarta marta;


//------terminan variables globales-----


//--------funciones de creacion----

t_archivoProcesado* crearArchivoProcesado() ;
t_relacionNodoBloque* crearRelacionNodoBloque() ;
t_ubicacionBloque* crearUbicacionBloque() ;
t_informacionDelArchivo* crearInformacionArchivo();
t_nombreFuncion* crearNombreFuncion();

//------terminan funciones de creacion


//-----funciones de destruccion----

void liberaMemoriaArchivoProcesado(t_archivoProcesado* ptrArchivoProcesado);

void liberaMemoriaRelacionNodoBloque(
		t_relacionNodoBloque* ptrRelacionNodoBloque);
void liberaMemoriaUbicacionBloque(t_ubicacionBloque* ptrUbicacionBloque);

void liberaMemoriaInformacionArchivo(
		t_informacionDelArchivo* ptrInformacionArchivo);

void liberaMemoriaNombreFuncion(t_nombreFuncion* ptrInformacionArchivo);

void liberaMemoriaSolicitud(t_solicitud* ptrSolicitud);

void liberaMemoriaMarta(t_estructuraMarta* ptrMarta) ;

//---- terminan funciones de destruccion---


//---------funcionesAuxiliares----

void liberaMemoriaLista(t_list* lista, int* cantElementos,
		void (*funcionLiberaElemento)(void*));//cuando se llama se escribe-> liberaMemoriaLista(lista,cantElementos,
void (*funcionLiberaElemento)(void*);   // (void*)funcionLiberaElemento)

// -----terminan funcionesAuxiliares------

// --------Funciones----

void planificarTrabajos();
void almacenarResultado(char * nombreDelArchivo);
void solicitarMapper();
void solicitarReducer(int soportaCombiner);

// Genera el nombre del archivo temporal de la siguiente forma: "nombreAntiguo.nomreFuncion.fechaActual"
char * generarNombreAlmacenado(char * nombreArchivo, char * nombreFuncion);

int mandarNodoBloque(int numeroBloque);
void noRepiteNodo();

//(char * nombreArchivoBuscado);

#endif /* MARTA_H_ */
