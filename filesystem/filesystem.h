// WARNING !!! Falta manejar el archivo de configuracion

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
#include <src/commons/string.h>
#include <src/commons/collections/list.h>
#include <src/commons/txt.h>

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
} fs;


// +++++++++++++++++++++++++++++++++++++++ Prototipos +++++++++++++++++++++++++++++++++++++
// Funciones Constructoras
nod*     crearNodo();
bloq*    crearBloque() ;
element* crearElemento();
void     crearFileSystem() ;

// Funciones Destructoras
void liberaMemoriaBloque(bloq* bloque);
void liberaMemoriaNodo(nod* nodo) ;
void liberaNodoBloque(nodBloq* nodoBloque);
void liberaMemoriaElement(element* elemento);
void liberaMemoriaFS();

// Funciones Auxiliares
void cargarBloques(t_list *listaBloques);
void leerRegistro(int arch);
void guardarRegistro(int arch);

// Funciones de Consola
void agregarN(char* nombre) ;
void eliminarN(char* nombre) ;
void formatear(int fdArchConfig);
void crearDirectorio();
void inicializarFilesystem();


// Prototipos
void levantarConsola();
void aplicarFuncion(int idFuncion);
void man(char* funcion);
void mostrarComandos();
int  idFuncion(char* funcion);
// +++++++++++++++++++++++++++++++++++ Variables Globales +++++++++++++++++++++++++++++++++++
fs* FILESYSTEM;


char* funcionesConsola[] = { "formatearMDFS", "eliminarArchivo", "renombrarArchivo",
		"moverArchivos",				    // Archivos
		"crearDirectorio", "eliminarDirectorio", "renombrarDirectorio",
		"moverDirectorio",      // Directorios
		"copiarArchivoLocalAlMDFS", "copiarArchivoDelMDFSAlFSLocal",
		"solicitarMD5deUnArchivoenMDFS", "verBloque", "borrarBloque",
		"copiarBloque",										          // Bloques
		"agregarNodo", "eliminarNodo",								// Nodos
		"mostrarComandos"};

enum nomFun {
	FORMATEAR_MDFS,
	ELIMINAR_ARCHIVO,
	RENOMBRAR_ARCHIVO,
	MOVER_ARCHIVOS,
	CREAR_DIRECTORIO,
	ELIMINAR_DIRECTORIO,
	RENOMBRAR_DIRECTORIO,
	MOVER_DIRECTORIO,
	COPIAR_ARCHIVO_LOCAL_AL_MDFS,
	COPIAR_ARCHIVO_DEL_MDFS_AL_FS_LOCAL,
	SOLICITAR_MD5_DE_UN_ARCHIVO_EN_MDFS,
	VER_BLOQUE,
	BORRAR_BLOQUE,
	COPIAR_BLOQUE,
	AGREGAR_NODO,
	ELIMINAR_NODO,
	MOSTRAR_COMANDOS
};

//Completar descripciones
char* descripcionesConsola[] = { "Descrpcion de la funcion 1",
		"Descrpcion de la funcion 2", "Descrpcion de la funcion 3",
		"Descrpcion de la funcion 4", "Descrpcion de la funcion 5",
		"Descrpcion de la funcion 6", "Descrpcion de la funcion 7",
		"Descrpcion de la funcion 8", "Descrpcion de la funcion 9",
		"Descrpcion de la funcion 10", "Descrpcion de la funcion 11",
		"Descrpcion de la funcion 12", "Descrpcion de la funcion 13",
		"Descrpcion de la funcion 14", "Descrpcion de la funcion 15",
		"Descrpcion de la funcion 16", "Descrpcion de la funcion 17"};



#endif /* FILESYSTEM_H_ */
