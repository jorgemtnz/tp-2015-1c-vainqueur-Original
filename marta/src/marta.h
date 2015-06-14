#ifndef MARTA_H_
#define MARTA_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>  // read write
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <commons/collections/list.h>
#include <commons/temporal.h>
#include <src/commons/string.h>
#include <src/commons/txt.h>


#define SI 1
#define NO 0
#define COMPLETADO 1
#define EN_ESPERA 0
#define NO_MAPEADO 0;
#define MAPEADO 1;

typedef struct estructuraMarta {
	t_list listaSolicitudes;
	t_list listaInformacionDelArchivo;
	t_list listaArchivosProcesados;
} t_estructuraMarta;

typedef struct solicitud {
	t_list listaNombresFunciones;
	int soportaCombiner; //1 si soporta 0 si no soporta
	char * nombreArchivoATrabajar;
	int estado; //1 completado 0 en espera
} t_solicitud;

typedef char * t_nombreFuncion;

typedef struct informacionDelArchivo {
	char * nombreArchivo;
	t_list listaUbicacionBloques;
	int enUso; //Si = 1 / No = 0
} t_informacionDelArchivo;

typedef struct ubicacionBloque {
	int numero;
	t_list listaRelacionesNodoBloque;
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

//---------Variables globales-----------------
t_estructuraMarta marta;

//---------funcionesAuxiliares----
void liberaMemoriaLista(t_list* lista, int* cantElementos,
		void (*funcionLiberaElemento)(void*));//cuando se llama se escribe-> liberaMemoriaLista(lista,cantElementos,
void (*funcionLiberaElemento)(void*);   // (void*)funcionLiberaElemento)

// --------Funciones
void planificarTrabajos();
void almacenarResultado(char * nombreDelArchivo);
void solicitarMapper();
void solicitarReducer(int soportaCombiner);

// Genera el nombre del archivo temporal de la siguiente forma: "nombreAntiguo.nomreFuncion.fechaActual"
char * generarNombreAlmacenado(char * nombreArchivo, char * nombreFuncion);

mandarNodoBloque(int numeroBloque);
void noRepiteNodo();

(char * nombreArchivoBuscado);

#endif /* MARTA_H_ */
