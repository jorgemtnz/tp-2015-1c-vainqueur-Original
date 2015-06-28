#ifndef FILESYSTEM_H_
#define FILESYSTEM_H_

// +++++++++++++++++++++++++++++++++++++++ Includes +++++++++++++++++++++++++++++++++++++
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>  // read write
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <mapeoAMemoria/mapeoAMemoria.h>
#include <src/commons/string.h>
#include <src/commons/collections/list.h>
#include <src/commons/txt.h>
#include <src/commons/config.h>
#include <pthread.h>
#include <sockets/sockets.h>
#include <string.h>
#include <semaphore.h>
#include <stdbool.h>

// +++++++++++++++++++++++++++++++++++++++ Define +++++++++++++++++++++++++++++++++++++
#define ESDIRECTORIO 1
#define ESARCHIVO 0
#define VEINTEMEGAS 20971520
#define OPERATIVO 1		// Nodo y FS
#define NOOPERATIVO 0
#define DISPONIBLE 1	// Archivos
#define NODISPONIBLE 0
#define NUMEROBLOQUES 102
#define UBICACIONNODO "/tmp/nodo.txt"
#define NUMEROFUNCIONESCONSOLA 18
// #define RUTACONFIGFS "/" Mejor si lo ingresamos por consola
#define LONGITUD_DE_IP 20
#define LONGITUD_STRINGS 150 //UTILIZADO para inicializar strings
#define EXISTE 1
#define NO_EXISTE 0
#define CANT_COLUMNAS 3  // cantidad de copias
#define CANT_FILAS 308 // MaximoArchivo = 6144 miB (6 GB) Bloque = 20 miB  => 2144/20 = 307,2 ~= 308

// +++++++++++++++++++++++++++++++++++++++ Estructuras +++++++++++++++++++++++++++++++++++++
typedef struct bloq {
	int numero;
	int tamanio;
} bloq;

typedef struct nod {
	int numero;
	int estado;
//	long    long tamanio; 2GB  consultar, posiblemente no sea necesario
	t_list* listaBloques;   //del nodo
	char* dirEspacioNodo;
} nod;

typedef struct ubicacionDelBloqueEnNodo {
	//int numeroCopia; // 0 original, 1 copia 1, n copia n.
	int numeroNodo;
	int numeroDeBloqueDelNodo;
} ubicacionDelBloqueEnNodo;

typedef struct element {
	char* nombre;
	int estado;
	int index;
	int tamanio;
	int directorioPadre;
	int tipoElemento; // USAR DEFINE: ESDIRECTORIO (1) para directorio, ESARCHIVO (0) para archivo o documento.
	ubicacionDelBloqueEnNodo ** matrizUbicacionDelBloqueEnNodo;
} element;

typedef struct fs {
	int estado;
	int espacioDisponible;
	t_list* listaNodosConectados;
	t_list* listaElementos;
	char** ipNodos;	// Array de strings
} fs;

// Estructura para el envío de archivos por socket
typedef struct t_archivo {
	char* contenido;
} t_archivo;

// Estructura para que el FS le mande un bloque al nodo por socket
typedef struct t_escritura_bloque {
	int numeroDeBloque;
	char* archivo;
} t_escritura_bloque;

// +++++++++++++++++++++++++++++++++++++++ Prototipos +++++++++++++++++++++++++++++++++++++
// Funciones Constructoras
nod* crearNodo();
bloq* crearBloque();
element* crearElemento();
void crearFileSystem();
void inicializarFilesystem();

// Funciones Destructoras
void liberaMemoriaBloque(bloq* bloque);
void liberaMemoriaNodo(nod* nodo);
// void liberaNodoBloque(nodBloq* nodoBloque);
void liberaMemoriaElement(element* elemento);
void liberaMemoriaFS();

// Funciones Auxiliares
void leerArchivoDeConfiguracion();
//void inicializarMatriz();
element* buscarElementoPorNombre(char* nombre);
// Lucas - Creo que las primeras tres ya andan bien
int devuelveMenorNodoConBloques();
void crearYAgregarBloquesALista(t_list *listaBloques, int cantidadBloquesACrear);
void leerRegistro(int arch);
void guardarRegistro(int arch);

void distribuyeBloque(t_list* listaNodosConectados, char* bloqueListo) ; //sin implementar
void empaquetarYMandarPorSocket(char* bloqueListo) ; //sin implementar
int devuelveCantBloquesLista(void*lista, int elementosEnLista);  //sin implementar
bool puedoHacerCopias();
void actualizaEstructura();
void copiaDistribuyeYEmpaqueta(char* bloqueListo, int cantBloques) ;
int devuelveCantidadElementosArreglo(char** arregloPtrContenidoBloque);
void divideBloques(char** ptrArregloConOracionesParaBloque);
void mostrarElementos();
ubicacionDelBloqueEnNodo* devuelveBloque(char* nombreArchivo, int* numeroBloque);


// Funciones de Consola
void renombrarElemento(element* ptrElemento, char* nuevoNombreElemento);
void moverElemento(element* elementoOrigen, element* directorioDestino);
void eliminarElemento(char* nombreElemento);	//Corregir

void formatearMDFS();
void eliminarArchivo();
void renombrarArchivo();
void moverArchivo();
void crearDirectorio();             // Corregir
void eliminarDirectorio();
void renombrarDirectorio();
void moverDirectorio();
void copiarArchivoLocalAlMDFS();	// Lucas no entiende que hace
void copiarArchivoDelMDFSAlFSLocal(); // Falta implementar
void solicitarMD5deUnArchivoenMDFS(); // Falta implementar
void verUbicacionBloque();
void copiarBloque() ;				// Lucas - Ya esta terminada?
void borrarBloque() ;				// Falta implementar
void agregarNodo(char* nombre);		// Necesita Sockets?
void eliminarNodo(char* nombre);	// Falta implementar
void mostrarComandos();

// Consola implementacion
int idFuncion(char* funcion);
void aplicarFuncion(int idFuncion);
void levantarConsola();

// +++++++++++++++++++++++++++++++++++ Variables Globales +++++++++++++++++++++++++++++++++++
fs* FILESYSTEM;
int vg_puerto_listen;
char** vg_lista_nodos; // array de strings
ubicacionDelBloqueEnNodo vg_matrizUbicacion[CANT_FILAS][CANT_COLUMNAS]; // Ver funcion auxiliar void inicializarMatriz()

#endif /* FILESYSTEM_H_ */
