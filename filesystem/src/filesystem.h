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
#include <protocolo/protocolo.h>
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
#define TAMANIO_DIRECTORIO 0
// #define RUTACONFIGFS "/" Mejor si lo ingresamos por consola
#define LONGITUD_DE_IP 20
#define LONGITUD_STRINGS 150 //UTILIZADO para inicializar strings
#define EXISTE 1
#define NO_EXISTE 0
#define COPIAS_BLOQUE 3  // cantidad de copias
#define CANT_FILAS 308 // MaximoArchivo = 6144 miB (6 GB) Bloque = 20 miB  => 2144/20 = 307,2 ~= 308
#define ESTA_OCUPADO 1
#define ESTA_DISPONIBLE 0
#define CONECTADO 1
#define DESCONECTADO 0

// +++++++++++++++++++++++++++++++++++++++ Estructuras +++++++++++++++++++++++++++++++++++++
typedef struct bloq {
	int numero;
	int tamanio;
	int estaOcupado;
} bloq;

typedef struct nod {
	int numero;
	int estado; //conectado 1  o desconectado 0
//	long    long tamanio; 2GB  consultar, posiblemente no sea necesario
	t_list* listaBloques;   //del nodo
} nod;

typedef struct ubicacionDelBloqueEnNodo {
	int numeroCopia; // 0 original, 1 copia 1, n copia n.
	int bloqueArchivo; // este es el numero que representa que bloque del archivo es
	int numeroNodo;     //identifica al nodo
	int numeroDeBloqueDelNodo;
} ubicacionDelBloqueEnNodo;

typedef struct element {
	char* nombre;
	int estado;
	int index;
	int tamanio;
	int directorioPadre;
	int idUbicacionDelBloqueEnNodo;
	int tipoElemento; // USAR DEFINE: ESDIRECTORIO (1) para directorio, ESARCHIVO (0) para archivo o documento.
	t_list* dobleListaUbicacionDelBloqueEnNodo;
// Agregar ubicacionDelBloqueEnNodo en constructora y destructora
} element;

typedef struct fs {
	int estado;
	int espacioDisponible;
	int idElemento; //valor incremental que no se repite
	int idNodo;  //valor incremental que no se repite
	t_list* listaNodos;
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
// Funciones Constructoras crea los malloc de las estructuras e inicializa
bloq* crearBloque();
nod* crearNodo();
ubicacionDelBloqueEnNodo* crearUbicacionDelBloqueEnNodo();
element* crearElemento();
void crearFileSystem();
void inicializarFilesystem();


// Funciones Destructoras hace el free de las estructuras para las que se hizo un malloc
void liberaMemoriaBloque(bloq* bloque);
void liberaMemoriaNodo(nod* nodo);
void liberaNodoBloque(ubicacionDelBloqueEnNodo* nodoBloque);// se debe dejar porque se hace un malloc cuando se construye
void liberaMemoriaElement(element* elemento);
void liberaMemoriaFS();

// Funciones Auxiliares
void leerArchivoDeConfiguracion();	//lee el archivo configuracion
element* buscarElementoPorNombre(char* nombre);	//recibe un nombre y devuelve un tipo element*
void crearYAgregarBloquesALista(t_list *listaBloques, int cantidadBloquesACrear);//recibe una lista de blqoues y un cantidad de bloques a cargar en esa lista
void leerRegistro(int arch);	//lee un registro guardado en un txt
void guardarRegistro(int arch);	//guarda un registro en un txt
void empaquetarYMandarPorSocket(char* bloqueListo,
		ubicacionDelBloqueEnNodo* unNodoBloque); 	// Falta implementar
int devuelveCantBloquesLista(void*lista, int elementosEnLista);	// Falta implementar
int devuelveMenorNodoConBloques();//devuelve el nodoID con menor cantidad de bloques
bool puedoHacerCopias(int cantBloquesOriginales);//algoritmo que calcula si se puede realizar el copiado
bloq* buscaBloqueDisponible(nod* unNodo);//devuelve el primer blqoue disponible para almacenar informacion
void distribucionInicial(char* bloqueListo, element* unElemento);//recibe un blqoue listo y un elemento (Archivo) para distribuirlo en los nodos equitativamente
void copiaDistribuyeYEmpaqueta(char* bloqueListo, int cantBloques,
		element* elemento);	//recibe un bloque listo y inicia la copia del bloque a los nodos
int devuelveCantidadElementosArreglo(char** arregloPtrContenidoBloque);	//devuelve la cantidad de venctores en un arreglo (se usa par ala canto de blques originales ya que es un vector muy grande y no todos estas llenos)
void divideBloques(char** ptrArregloConOracionesParaBloque, element* unElemento);//guarda en un vector donde se almacenan las ultimas posiciones de las oraciones al poner en un bloque listo
ubicacionDelBloqueEnNodo* devuelveBloque(char* nombreArchivo, int numeroBloque);//recibe un nombre de archivo y un numero de blqoue y devuelve un tipo de datoubicaionNodoBlqoue
ubicacionDelBloqueEnNodo* verUbicacionBloque(); //se debe modificar , porque solapo la de mostrar bloque
void solicitudCopiaDeBloque(); // se esta implementando
char* sacarUltimaParte(char* dirArchivoLocal);
void marcaNodoDesconectado(int numeroNodo);
bool verificaNodoConectado(t_list*listaBloquesArchivo);

t_list* buscaListaArchivo(element* ptrArchivo);

// Funciones de Consola
void renombrarElemento(element* ptrElemento, char* nuevoNombreElemento);
void moverElemento(element* elementoOrigen, element* directorioDestino);
void eliminarElemento(char* nombreElemento);
void mostrarElementos();
void formatearMDFS();
void eliminarArchivo();
void renombrarArchivo();
void moverArchivo();
void crearDirectorio();
void eliminarDirectorio();
void renombrarDirectorio();
void moverDirectorio();
void copiarArchivoLocalAlMDFS();      // RECORDAR: CAMBIARLE LOS NULL ?? por que?
void copiarArchivoDelMDFSAlFSLocal(); // Falta implementar
void solicitarMD5deUnArchivoenMDFS(); // Falta implementar
void copiarBloque();				// Falta implementar
void actualizarListaDeArchivos(ubicacionDelBloqueEnNodo* unaUbicacion,
		element* unArchivo); // Usada para borrarBloque // Usa doble lista VER
void borrarBloque();
void agregarNodo();		// Necesita Sockets?
void eliminarNodo();	// Falta implementar
void mostrarComandos();

// Consola implementacion
int idFuncion(char* funcion);
void aplicarFuncion(int idFuncion);
void levantarConsola();
//++++++++++++++++++++++++++++++++++++funciones envio +++++++++++++++++++++++++++++++++++++++

// +++++++++++++++++++++++++++++++++++ Variables Globales +++++++++++++++++++++++++++++++++++
fs* FILESYSTEM;
int vg_puerto_listen;
char** vg_lista_nodos; // array de strings para guardar las IP de los nodos.


#endif /* FILESYSTEM_H_ */
