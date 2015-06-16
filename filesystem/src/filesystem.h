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
#define RUTACONFIGFS "/"
#define LONGITUD_DE_IP 20
#define LONGITUD_STRINGS 150 //UTILIZADO para inicializar strings


// +++++++++++++++++++++++++++++++++++++++ Estructuras +++++++++++++++++++++++++++++++++++++
typedef struct bloq {
	int numero;
	int tamanio;
} bloq;

typedef struct nod {
	int     numero;
	int     estado;
//	long    long tamanio; 2GB  consultar, posiblemente no sea necesario
	t_list* listaBloques;   //del nodo
	char*   dirEspacioNodo;
} nod;

typedef struct nodBloq {
	int numeroCopia; // 0 original, 1 copia 1, n copia n.
	int numeroNodo;
	int numeroBloque;
} nodBloq;

typedef struct element {
	char*   nombre;
	int     estado;
	int     index;
	int     tamanio;
	int     directorioPadre;
	int     tipoElemento;        // USAR DEFINE: ESDIRECTORIO (1) para directorio, ESARCHIVO (0) para archivo o documento.
	t_list* listaNodoBloque;
} element;

typedef struct fs {
	int     estado;
	int     espacioDisponible;
	t_list* listaNodosConectados;
	t_list* listaElementos;
	char** ipNodos;	// Array de strings
} fs;


// +++++++++++++++++++++++++++++++++++++++ Prototipos +++++++++++++++++++++++++++++++++++++
// Funciones Constructoras
nod*     crearNodo();
bloq*    crearBloque() ;
element* crearElemento();
void     crearFileSystem();
void     inicializarFilesystem();

// Funciones Destructoras
void liberaMemoriaLista(t_list* lista, int cantElementos, void (*funcionLiberaElemento)(void*));
void liberaMemoriaBloque(bloq* bloque);
void liberaMemoriaNodo(nod* nodo) ;
void liberaNodoBloque(nodBloq* nodoBloque);
void liberaMemoriaElement(element* elemento);
void liberaMemoriaFS();

// Funciones Auxiliares
void leerArchivoDeConfiguracion();
void cargarBloques(t_list *listaBloques);
void leerRegistro(int arch);
void guardarRegistro(int arch);
element* buscarElementoPor(char* nombre);

// Funciones de Consola
void formatearMDFS();
void eliminarElemento(char* nombreElemento);
void eliminarArchivo();
void renombrarArchivo();
void moverArchivo();
void crearDirectorio();
void eliminarDirectorio();
void copiarArchivoLocalAlMDFS();//Falta implementar
void agregarNodo(char* nombre);
void eliminarNodo(char* nombre);
void mostrarElementos();
void mostrarComandos();

// Consola implementacion
int  idFuncion(char* funcion);
void aplicarFuncion(int idFuncion);
void levantarConsola();

// +++++++++++++++++++++++++++++++++++ Variables Globales +++++++++++++++++++++++++++++++++++
fs* FILESYSTEM;
int vg_puerto_listen;
char** vg_lista_nodos; // array de strings
char* archivo; // puntero a un archivo genérico

#endif /* FILESYSTEM_H_ */
