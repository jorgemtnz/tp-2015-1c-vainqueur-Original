#ifndef NODO2_SRC_NODO_H_
#define NODO2_SRC_NODO_H_

// +++++++++++++++++++++++++++++++++++++++ Includes +++++++++++++++++++++++++++++++++++++
#include <stdio.h>
#include <stdlib.h>
#include <redireccionIO/redireccionIO.h>
#include <string.h>
#include <unistd.h>  // read write
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sockets/sockets.h>
#include <src/commons/temporal.h>
#include <src/commons/string.h>
#include <src/commons/txt.h>
#include <src/commons/config.h>
#include <src/commons/collections/list.h>
#include <src/commons/log.h>
#include <pthread.h>
#include <semaphore.h>
#include <protocolo/protocolo.h>
#include <src/commons/log.h>
#include <mapeoAMemoria/mapeoAMemoria.h>
// +++++++++++++++++++++++++++++++++++++++ Define +++++++++++++++++++++++++++++++++++++
#define RUTACONFIGNODO "/home/utnso/TPOperativos/nodo/config_nodo.cfg"
#define RUTAMAP "/tmp/"
#define EJECUCIONOK 1
#define EJECUCIONFALLO -1
#define NODO_NUEVO 1
#define NODO_NO_NUEVO 0
#define VEINTEMEGAS 20971520
//#define DESCONECTAR_NODO
#define CONECCIONES_ENTRANTES_PERMITIDAS 10
//+++++++tp n++++++++
#define BLOCK_SIZE 20971520 //block size 20MB
#define BUF_SIZE 50
#define MAPPER_SIZE 4096
// +++++++++++++++++++++++++++++++++++++++ Estructuras +++++++++++++++++++++++++++++++++++++

typedef struct nodo {
	int idNodo; //nuemero del nodo


} t_nodo;

typedef char bufferTemp;
typedef char bufferVeinteMegas [VEINTEMEGAS];//bufer de 20 megas que devolvera contenido del bloque
// +++++++++++++++++++++++++++++++++++++++ Prototipos +++++++++++++++++++++++++++++++++++++
// Funciones Constructoras hace el malloc de la estrutura e inicializa
t_nodo* crearNodo();

// Funciones Destructoras  libera con free la estructura solamente
void liberaMemoriaNodo();

// Funciones Auxiliares recorre la lista y va liberando elemento por elemento mediante la func_destructura
void liberaMemoriaLista(t_list* lista, int* cantElementos,
		void (*funcionLiberaElemento)(void*)) ;
void testleerArchivoDeConfiguracion();
//nodoFunciones
void levantarArchivoConfiguracion(); //levanta configuración y se lo pasa a las variables globales
int informarEjecucionAJob(t_nodo* datosDelNodo,
		char* ipJob, int puertoJob,	int comoTerminoLaEjecucion);//le contesta al job como fue el trabajo realizado
int ejecutarReduce(int soportaCombiner); // Falta implementar
int ejecutarMap(char * nombreArchivoTemporal, char * ptrDireccionMapeo);// esta función ejecuta el map sobre un <<--ver observacion en .c
void conectarNodo(t_nodo* datosDelNodo); //se conecta el nodo al filesystem
//bufferVeinteMegas* getBloque(int numeroDeBloque); // devuelve un bloque determinado devuelve un puntero al buffer echo con malloc, se debe hacer luego el free
//int setBloque(int numeroDeBloque, bufferVeinteMegas buffer) ;//pone un la info de un bloque en el archivo
void setBloque(int bloque,char* datos);
char* getBloque(int bloque);
char* getFileContent(char* nombreDelArchivo) ; //devuelve archivo del tmp
//++++++++++++++++++++++++++++++++++++funciones envio +++++++++++++++++++++++++++++++++++++++
void* recibir(int fdReceptor);
void enviar(int tipoDeMensaje, void* t_estructura,int fdDestinatario);
void* interpretarPaquete(Paquete* unPaquete, int fdReceptor);
// +++++++++++++++++++++++++++++++++++ Variables Globales +++++++++++++++++++++++++++++++++++
int vg_puerto_FS,
	vg_nodo_Nuevo,
	vg_puerto_Nodo,
	vg_puerto_job,
  vg_desconectar;
char *vg_ip_FS;
char *vg_archivo_Bin;
char	 *vg_dirTemp;
char	 *vg_ip_Nodo;
long vg_tamanioArchivo;
t_nodo *vg_nodo;
//--------------funciones declarada tp n-----------------
char* mapearFileDeDatos();
void setBloque(int bloque,char* datos);
char* getBloque(int bloque);
char* getFileContent(char* nombre);
void* manejador_de_escuchas(); //Hilo que va a manejar las conexiones

int estaEnListaNodos(int socket);
int estaEnListaMappers(int socket);
int estaEnListaReducers(int socket);
//-------------------------------------
unsigned int sizeFileDatos;//VARIABLES GLOBALES
char* fileDeDatos;//VARAIBLES GLOBALES
t_log* logger_archivo;
t_log* logger; //log en pantalla y archivo de log
fd_set master; // conjunto maestro de descriptores de fichero
fd_set read_fds; // conjunto temporal de descriptores de fichero para select()
int fdmax;//Numero maximo de descriptores de fichero
int conectorFS; //socket para conectarse al FS
int listener; //socket encargado de escuchar nuevas conexiones
struct sockaddr_in remote_client; //Direccion del cliente que se conectará
char mensaje[BUF_SIZE]; //Mensaje que recivirá de los clientes
t_list* listaNodosConectados; //Lista con los nodos conectados
t_list* listaMappersConectados; //Lista con los mappers conectados
t_list* listaReducersConectados; //lista con los reducers conectados
int* socketNodo; //para identificar los que son nodos conectados
int* socketMapper; //para identificar los que son mappers conectados
int* socketReducer;
#endif /* NODO2_SRC_NODO_H_ */
