#include "job.h"

/*
 **					DOCUMENTACION - mainJob.c
 **
 **		Funcion leerArchivoDeConfiguracion();
 **	[ Test OK ] - leerArchivoDeConfiguracion();
 **	[ Test OK ] - testleerArchivoDeConfiguracion();
 **	NOTA: Cuando se haga el archivo de configuracion, NO poner espacio antes y despues del =
 **
 **		Funcion indicarArchivosAMarta();
 **		incluye
 **			Funcion [void sendTamanioDe(char* cadena);]
 **			Funcion [void conectarConMarta();]
 **	[ Test OK ] - sendTamanioDe(char* cadena);
 **	[ Test OK ] - conectarConMarta();
 **
 */
sem_t semCliAMartha;
sem_t semCliANodo;

//prototipos
void* clienteAMartha();
void* clienteANodos();

int main() {
  	int error, errorOtro;
  	logger = log_create("LOG_Job.log", "Job", false, LOG_LEVEL_INFO); //Inicializacion logger

  	leerArchivoDeConfiguracion(); // /home/utnso/TPOperativos/job/config_job.cfg
  	testleerArchivoDeConfiguracion();

	error = sem_init(&semCliAMartha, 0, 0);
	errorOtro = sem_init(&semCliANodo, 0, 0);
	if ((error < 0) || (errorOtro < 0)) {
		perror("[ERROR]: Inicializando semaforo");
		log_error(logger, "[ERROR]: Inicializando semaforo");
		exit(-1);
	}

	//-------harcodeo mapperstruc------
	t_mapper* punteroMapper;
	punteroMapper=malloc(sizeof(t_mapper));
	strcpy(punteroMapper->ip_nodo,"127.0.0.1");
	punteroMapper->bloque=1;
	punteroMapper->puerto_nodo=9000;
	strcpy(punteroMapper->nombreArchivoTemporal,"/home/utnso/Escritorio/soyMapper.txt");


	pthread_t mapperThread;
//crearJob() crear las estructuras
	pthread_t tidClienteAMartha;
	pthread_t tidClienteANodos;
	pthread_attr_t atributos1, atributos2;
	pthread_attr_init(&atributos1);
	pthread_attr_init(&atributos2);
	pthread_create(&tidClienteAMartha, &atributos1, clienteAMartha, NULL);
	pthread_create(&mapperThread, &atributos2,hilo_mapper(punteroMapper), NULL);

	pthread_join(tidClienteAMartha, NULL);
	pthread_join(mapperThread,NULL);
//	se deben crear dos hilos una clienteAMartha y el otro clienteANodo ambos manejan sus interacciones medinate socket
//todas la variables globales que sean compartidas entre los hilos deben ser sincronizadas.


	liberarMemoriaVG();
	log_destroy(logger); //Destruyo el logger
	return 0;
}
	//    clienteAMarta
void* clienteAMartha(){
	int sockTranferencia;
	int retorno = -1;
	sockTranferencia = crearSocket();
	conectarSocketPorPrimeraVez(sockTranferencia, vg_ipMarta,vg_puertoMarta);
	//empieza la comunicacion - marta le manda info de los nodos, IP en una variable que sera compartida
	//y region critica se debe usar mutex
	//indicarArchivosAMarta();
	cerrarSocket(sockTranferencia);
	return NULL;
}
//	clienteANodo se ejecuta solo despues que marta mande la info de los nodos
/*--------------------------hilo cliente mapper con nodo-----------------------------------------------*/

void* hilo_mapper(t_mapper* mapperStruct){
	printf("Se conectara al nodo con ip: %s\n",(char*)mapperStruct->ip_nodo);
	printf("En el puerto %d\n", mapperStruct->puerto_nodo);
	printf("Ejecutará la rutina mapper en el bloque %d\n",mapperStruct->bloque);
	printf("Guardará el resultado en el archivo %s\n",mapperStruct->nombreArchivoTemporal);

	//comienzo de conexion con nodo
	struct sockaddr_in nodo_addr;
	int nodo_sock;
	char identificacion[BUF_SIZE];


	if((nodo_sock=socket(AF_INET,SOCK_STREAM,0))==-1){ //si función socket devuelve -1 es error
		perror("[ERROR]: Fallo la creación del socket (conexión mapper-nodo)");
		log_error(logger,"[ERROR]: Fallo la creación del socket (conexión mapper-nodo)");
		exit(1);
	}

	nodo_addr.sin_family=AF_INET;
	nodo_addr.sin_port=htons(mapperStruct->puerto_nodo);
	nodo_addr.sin_addr.s_addr=inet_addr(mapperStruct->ip_nodo);
	memset(&(nodo_addr.sin_zero),'\0',8);

	if((connect(nodo_sock,(struct sockaddr *)&nodo_addr,sizeof(struct sockaddr)))==-1){
		perror("[ERROR]: Fallo la conexión con MaRTA");
		log_error(logger,"[ERROR]: Fallo la conexión con MaRTA");
		exit(1);
	}
	strcpy(identificacion,"soy mapper");
	if(send(nodo_sock,identificacion,sizeof(identificacion),0)==-1){
		perror("[ERROR]: Fallo el envío de identificación mapper-nodo");
		log_error(logger,"[ERROR]: Fallo el envío de identificación mapper-nodo");
	}
	/*Conexión mapper-nodo establecida*/
	log_info(logger,"[ERROR]: Hilo mapper conectado al Nodo con IP: %s,en el Puerto: %d",mapperStruct->ip_nodo,mapperStruct->puerto_nodo);

	if(send(nodo_sock,&(mapperStruct->bloque),sizeof(int),0)==-1){
		perror("[ERROR]: Fallo el envio del bloque a mapear hacia el Nodo");
		log_error(logger,"[ERROR]: Fallo el envio del bloque a mapear hacia el Nodo");
		exit(-1);
	}

	if(send(nodo_sock,&(mapperStruct->nombreArchivoTemporal),100,0)==-1){
		perror("[ERROR]: Fallo el envio del nombre del archivo temporal a guardar el Map");
		log_error(logger,"[ERROR]: Fallo el envio del nombre del archivo temporal a guardar el Map");
		exit(-1);
	}

	//envío la rutina mapper
	if(send(nodo_sock,vg_mapperPath,MAPPER_SIZE,0)==-1){
		perror("[ERROR]: Fallo el envio de la rutina mapper");
		log_error(logger,"[ERROR]: Fallo el envio de la rutina mapper");
		exit(1);
	}

	pthread_exit((void*)0);

}

char* getFileContent(char* path){
	char* fileMapeado;
	int fileDescriptor;
	struct stat estadoDelFile; //declaro una estructura que guarda el estado de un archivo
	fileDescriptor = open(path,O_RDWR);
		/*Chequeo de apertura del file exitosa*/
			if (fileDescriptor==-1){
				perror("[ERROR]: Fallo la apertura del file de datos");
				log_error(logger,"[ERROR]: Fallo la apertura del file de datos");
				exit(-1);
			}
	if(fstat(fileDescriptor,&estadoDelFile)==-1){//guardo el estado del archivo de datos en la estructura
			perror("[ERROR]: Falló el fstat");
			log_error(logger,"[ERROR]: Falló el fstat");
			exit(-1);
		}
	fileMapeado=mmap(0,estadoDelFile.st_size,(PROT_WRITE|PROT_READ|PROT_EXEC),MAP_SHARED,fileDescriptor,0);
	/*Chequeo de mmap exitoso*/
		if (fileMapeado==MAP_FAILED){
			perror("[ERROR]: Falló el mmap, no se pudo asignar la direccion de memoria para el archivo solicitado");
			log_error(logger,"[ERROR]: Falló el mmap, no se pudo asignar la direccion de memoria para el archivo solicitado");
			exit(-1);
		}
	close(fileDescriptor); //Cierro el archivo
//	log_info(logger,"Fue leído el archivo /home/utnso/%s",nombreFile);
	return fileMapeado;
}



//----------------------------------------------------------------------------------------------
//void* clienteANodos(){
//	int sockTranferencia;
//	int retorno = -1;
//	void* msg = "hola desde job";
//	sockTranferencia = crearSocket();
//	conectarSocketPorPrimeraVez(sockTranferencia,vg_ipNodo,vg_PuertoNodo);
//se van a lanzar n hilos que van a cada nodo, de los que se tenga que conectar


	/*int incrementador; estos hilos son como conexion para el nodo, dependen de lo recibido por marta.

	 for(incrementador = 0; incrementador < HILOS_A_LANZAR; incrementador ++){
	 pthread_t tidHiloJob;
	 pthread_attr_t atributosDeHilo;

	 pthread_attr_init(&atributosDeHilo);

	 pthread_create(&tidHiloJob,&atributosDeHilo,manejaHilo,NULL);
	 pthread_join(tidHiloJob,NULL);

	 //sockTranferencia = crearSocket();
		//conectarSocket(sockTranferencia,variable compartida con direccion IP que manda marta)
	 }*/
//	enviarPorSocket(sockTranferencia, msg, strlen(msg));
//	cerrarSocket(sockTranferencia);
//return NULL;
//}
