#include "nodo.h"
#include <protocolo/protocolo.h>

void levantarArchivoConfiguracion() {
	char* temporal;

	t_config* archivoConfig;
	archivoConfig = config_create(RUTACONFIGNODO);
	vg_puerto_FS = config_get_int_value(archivoConfig, "PUERTO_FS");
	vg_ip_FS = strdup(config_get_string_value(archivoConfig, "IP_FS"));
	vg_puerto_Nodo = config_get_int_value(archivoConfig, "PUERTO_NODO_BASE");
	vg_ip_Nodo = strdup(config_get_string_value(archivoConfig, "IP_NODO"));
	vg_puerto_job = config_get_int_value(archivoConfig, "PUERTO_JOB");
	vg_archivo_Bin = strdup(config_get_string_value(archivoConfig, "ARCHIVO_BIN"));
	vg_puerto_job = config_get_long_value(archivoConfig, "TAMANIO_ARCHIVO");
	vg_dirTemp = strdup(config_get_string_value(archivoConfig, "DIR_TEMP"));

	temporal = strdup(config_get_string_value(archivoConfig, "NODO_NUEVO"));

	if (strcmp(temporal, "SI") == 0) {
		vg_nodo_Nuevo = NODO_NUEVO;
	}
	if (strcmp(temporal, "NO") == 0) {
		vg_nodo_Nuevo = NODO_NO_NUEVO;
	}

	free(temporal);
	config_destroy(archivoConfig);
}

int informarEjecucionAJob(t_nodo* datosDelNodo, char* ipJob, int puertoJob,
		int comoTerminoLaEjecucion) {
	int fdNodo = crearSocket();
	conectarSocket(fdNodo, ipJob, puertoJob);
	printf("Nodo: %d conectado al Job con ip %s mediante el puerto %d \n",
			datosDelNodo->idNodo, ipJob, puertoJob);
	enviarPorSocket(fdNodo, (void *) comoTerminoLaEjecucion, sizeof(int));
	printf("Nodo: Mensaje Enviado al Job \n");
	cerrarSocket(fdNodo);
	return 0;
}

int ejecutarReduce(int soportaCombiner) {
	if (soportaCombiner) {

	}
	return 0;
}
//revisar el funcionamiento de esta funcion porque el map solo se hace sobre un bloque
int ejecutarMap(char * nombreArchivoTemporal, char * ptrDireccionMapeo) {
	char *ruta;
	ruta = RUTAMAP;
	strcpy(ruta, vg_dirTemp);
	ruta = strcat(ruta, nombreArchivoTemporal);
	if (ejecutarScriptRedireccionandoIO(ruta, ptrDireccionMapeo,
	RUTAMAP, "") < 0) {
		perror("[ERROR] Funcion ejecutarScriptRedireccionandoIO\n");
		exit(EJECUCIONFALLO);
	}
	return EJECUCIONOK;
}

//void conectarNodo(t_nodo* datosDelNodo) { se hace en el hilo clienteFS
//	int fdNodo = crearSocket();
//	int numNodo = datosDelNodo->idNodo;
//	conectarSocket(fdNodo, vg_ip_FS, vg_puerto_FS);
//	printf("Nodo: %d conectado al FS con ip %s mediante el puerto %d \n",
//			numNodo, vg_ip_FS, vg_puerto_FS);
//}
//no se puede devolver un array, da error, por eso mejor seria que devuelva un ptr al array
void setBloque(int numBloque,char* datosAEscribir){
	/*
	* El puntero ubicacionEnElFile, se va a posicionar en el bloque que se desea escribir el archivo
	* datosAEscribir, recibido por parametro, tiene los datos que quiero escribir
	* Con el memcpy a ubicacionEnElFile, escribo en ese bloque
	*/

	char *ubicacionEnElFile;
	ubicacionEnElFile=malloc(BLOCK_SIZE);
	ubicacionEnElFile=fileDeDatos+(BLOCK_SIZE*(numBloque-1));
	memcpy(ubicacionEnElFile,datosAEscribir,BLOCK_SIZE); //Copia el valor de BLOCK_SIZE bytes desde la direccion de memoria apuntada por datos a la direccion de memoria apuntada por fileDeDatos
	log_info(logger_archivo,"Se escribió el bloque %d",numBloque);
	return;
}

char* getBloque(int numBloque){
	/*
	* El puntero ubicacionEnElFile, se va a posicionar en el bloque de donde deseo leer los datos
	* El puntero datosLeidos, tendrá los datos que lei, y será devuelto por la funcion
	* Con el memcpy a datosLeidos, copio ese bloque
	*/

	char* datosLeidos;
	char *ubicacionEnElFile;
	datosLeidos=malloc(BLOCK_SIZE);
	ubicacionEnElFile=malloc(BLOCK_SIZE);
	ubicacionEnElFile=fileDeDatos+(BLOCK_SIZE*(numBloque-1));
	memcpy(datosLeidos,ubicacionEnElFile,BLOCK_SIZE); //Copia el valor de BLOCK_SIZE bytes desde la direccion de memoria apuntada por fileDeDatos a la direccion de memoria apuntada por datosLeidos
	log_info(logger_archivo,"Se leyó el bloque %d",numBloque);
	return datosLeidos;
}
/*FUNCIONES VIEJAS
bufferVeinteMegas* getBloque(int numeroDeBloque) {
	int fdDatosBin = open(vg_archivo_Bin, O_RDONLY, 0);
	bufferVeinteMegas* buffer = malloc(sizeof(bufferVeinteMegas));
	long pos = (numeroDeBloque - 1) * VEINTEMEGAS;
	if (lseek(fdDatosBin, pos, SEEK_SET) == 0) {
		read(fdDatosBin, &buffer, sizeof(VEINTEMEGAS));

	} else {
		perror("[ERROR] error al leer un bloque\n");
		exit(-1);
	}
	close(fdDatosBin);
	return buffer;
}
int setBloque(int numeroDeBloque, bufferVeinteMegas buffer) {
	int fdDatosBin = open(vg_archivo_Bin, O_RDWR, 0);
	long pos = (numeroDeBloque - 1) * VEINTEMEGAS;
	if (lseek(fdDatosBin, pos, SEEK_SET) == 0) {
		write(fdDatosBin, &buffer, sizeof(VEINTEMEGAS));

	} else {
		perror("[ERROR] error al escribir un bloque\n");
		exit(-1);
	}
	close(fdDatosBin);
	return EJECUCIONOK;
}
*/
/*----------MAPEO DATOS.BIN---------------------*/
char* mapearFileDeDatos(){
	char* fileDatos;

	/*
	 * Abro el archivo de datos. Éste archivo se crea localmente en la máquina que ejecutará el proceso Nodo
	 * y luego se configura el nombre en el archivo de configuracion(ARCHIVO_BIN).
	 * Una manera sencilla de crearlo es truncate -s "tamaño" nombrearchivo.bin
	 * Por ejemplo el que use para las pruebas: truncate -s 50 datos.bin --> crea un file de 50 bytes
	 */

	int fileDescriptor = open((vg_archivo_Bin),O_RDWR);
	/*Chequeo de apertura del file exitosa*/
		if (fileDescriptor==-1){
			perror("open");
			log_error(logger,"Fallo la apertura del file de datos");
			exit(-1);
		}
	struct stat estadoDelFile; //declaro una estructura que guarda el estado de un archivo
	if(fstat(fileDescriptor,&estadoDelFile)==-1){//guardo el estado del archivo de datos en la estructura
		perror("fstat");
		log_error(logger,"Falló el fstat");
	}
	sizeFileDatos=estadoDelFile.st_size; // guardo el tamaño (necesario para el mmap)

	/*se mapea a memoria,fileDatos apuntará a una direccion en donde empieza el archivo, con permisos de
	lectura escritura y ejecucion, los cambios en las direcciones de memoria a donde apunta se verán reflejados
	 en el archivo*/

	fileDatos=mmap(0,sizeFileDatos,(PROT_WRITE|PROT_READ|PROT_EXEC),MAP_SHARED,fileDescriptor,0);
	/*Chequeo de mmap exitoso*/
		if (fileDatos==MAP_FAILED){
			perror("mmap");
			log_error(logger,"Falló el mmap, no se pudo asignar la direccion de memoria para el archivo de datos");
			exit(-1);
		}
	close(fileDescriptor); //Cierro el archivo
	return fileDatos;
}


char* getFileContent(char* nombreFile){
	char* path;
	char* fileMapeado;
	int fileDescriptor;
	struct stat estadoDelFile; //declaro una estructura que guarda el estado de un archivo
	path=strdup("");
	strcpy(path,vg_dirTemp);
	strcat(path,"/");
	strcat(path,nombreFile);
	fileDescriptor = open(path,O_RDWR);
		/*Chequeo de apertura del file exitosa*/
			if (fileDescriptor==-1){
				perror("open");
				log_error(logger,"Fallo la apertura del file de datos");
				exit(-1);
			}
	if(fstat(fileDescriptor,&estadoDelFile)==-1){//guardo el estado del archivo de datos en la estructura
			perror("fstat");
			log_error(logger,"Falló el fstat");
		}
	fileMapeado=mmap(0,estadoDelFile.st_size,(PROT_WRITE|PROT_READ|PROT_EXEC),MAP_SHARED,fileDescriptor,0);
	/*Chequeo de mmap exitoso*/
		if (fileMapeado==MAP_FAILED){
			perror("mmap");
			log_error(logger,"Falló el mmap, no se pudo asignar la direccion de memoria para el archivo solicitado");
			exit(-1);
		}
	close(fileDescriptor); //Cierro el archivo
	log_info(logger_archivo,"Fue leído el archivo /tmp/%s",nombreFile);
	return fileMapeado;
}


/*viejo get file contetn
char* getFileContent(char* nombreDelArchivo) { //devuelve archivo del tmp
	char* dirArchiv = string_new();
	string_append(&dirArchiv, vg_dirTemp);
	string_append(&dirArchiv, nombreDelArchivo);
	int fdArchvTmp = open(dirArchiv, O_RDONLY, 0);
	int tamanioArch = lseek(fdArchvTmp, 0, SEEK_END); //cuenta tamanio del archivo
//	bufferTemp buffer[tamanioArch];
	char* buffer = malloc(sizeof(tamanioArch));
	if (lseek(fdArchvTmp, 0, SEEK_SET) == 0) { //se posiciona devuelta en el inicio del archivo
		read(fdArchvTmp, buffer, sizeof(tamanioArch));
	} else {
		perror("[ERROR] no se pudo abrir el archivo temporal del nodo\n");
		exit(-1);
	}
	close(fdArchvTmp);
	return buffer; // esto que se regresa es un ptr a la primera posición del arreglo
}
*/
//+++++++++++++++++++++++funciones tp n+++++++++++++++++++++
int estaEnListaNodos(int socket){
	int i,tamanio;
	int* nodoDeLaLista;
	tamanio=list_size(listaNodosConectados);
	for(i=0;i<tamanio;i++){
		nodoDeLaLista=list_get(listaNodosConectados,i);
		if(*nodoDeLaLista==socket){
			return 0;
		}
	}
	return -1;
}

int estaEnListaMappers(int socket){
	int i,tamanio;
	int* mapperDeLaLista;
	tamanio=list_size(listaMappersConectados);
	for(i=0;i<tamanio;i++){
		mapperDeLaLista=list_get(listaMappersConectados,i);
		if(*mapperDeLaLista==socket){
			return 0;
		}
	}
	return -1;
}

int estaEnListaReducers(int socket){
	int i,tamanio;
	int* reducerDeLaLista;
	tamanio=list_size(listaReducersConectados);
	for(i=0;i<tamanio;i++){
		reducerDeLaLista=list_get(listaReducersConectados,i);
		if(*reducerDeLaLista==socket){
			return 0;
		}
	}
	return -1;
}
