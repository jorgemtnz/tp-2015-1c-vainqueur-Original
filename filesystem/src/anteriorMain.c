//#include "filesystem.h"
//
//sem_t semaforoServidor;
//sem_t semaforoCliente;
//
//// Prototipos
//void * servidorHilo();
//void * clienteHilo();
//
//int pruebmain() {
//
//	// Inicializo semaforos en 0
//	//levantarArchivoConfiguracion();
//	//printf("IP Nodo : %s \n", vg_dirTemp);
//	int error;
//	error = sem_init(&semaforoCliente, 0, 0);
//	if (error < 0) {
//		perror("[ERROR]: Funcion sem_init : Error al inicializar el semaforo");
//		return -1;
//	}
//	error = sem_init(&semaforoServidor, 0, 0);
//	if (error < 0) {
//		perror("[ERROR]: Funcion sem_init : Error al inicializar el semaforo");
//		return -1;
//	}
//
//	pthread_t tidServidor, tidCliente;
//	pthread_attr_t atributos1, atributos2;
//
//	pthread_attr_init(&atributos1);
//	pthread_attr_init(&atributos2);
//
//	pthread_create(&tidServidor, &atributos1, servidorHilo, NULL);
//	pthread_create(&tidCliente, &atributos2, clienteHilo, NULL);
//
//	pthread_join(tidServidor, NULL);
//	pthread_join(tidCliente, NULL);
//
//	return 0;
//}
//
//void * servidorHilo() {
//	int fdSocketEscucha, fdSocketNuevasConecciones; // Escuchar sobre fdSocketEscucha, nuevas conexiones sobre fdSocketNuevasConecciones
//	char buffer[100];
//
//	fdSocketEscucha = crearSocket();
//	asociarSocket(fdSocketEscucha, 9003);
//	escucharSocket(fdSocketEscucha, CONECCIONES_ENTRANTES_PERMITIDAS);
//
////	sem_post(&semaforoCliente);
////	sem_wait(&semaforoServidor);
//
//	fdSocketNuevasConecciones = aceptarConexionSocket(fdSocketEscucha);
//
////	sem_post(&semaforoCliente);
////	sem_wait(&semaforoServidor);
//
//	recibirPorSocket(fdSocketNuevasConecciones, buffer, sizeof(buffer));
//	printf("Mensaje Recibido por el servidor : %s \n", buffer);
//	strcpy(buffer, "Mensaje Para Cliente \n");
//
//	enviarPorSocket(fdSocketNuevasConecciones, buffer, sizeof(buffer));
//
////	sem_post(&semaforoCliente);
////	sem_wait(&semaforoServidor);
//
//	cerrarSocket(fdSocketEscucha);
//
//	pthread_exit(0);
//}
//
//void * clienteHilo() {
//	int fdCliente;
//	char buffer[100] = "Mensaje Para Servidor \n";
//	int retorno = -1;
//
//	fdCliente = crearSocket();
//
////	sem_wait(&semaforoCliente);
//	while(retorno<0)
//	{
//		 retorno = conectarSocket(fdCliente,"127.0.0.1", 9003);
//	}
//
////	sem_post(&semaforoServidor);
////	sem_wait(&semaforoCliente);
//
//	enviarPorSocket(fdCliente, buffer, sizeof(buffer));
////
////	sem_post(&semaforoServidor);
////	sem_wait(&semaforoCliente);
//
//	recibirPorSocket(fdCliente, buffer, sizeof(buffer));
//	printf("Mensaje Recibido por el Cliente: %s \n", buffer);
//
////	sem_post(&semaforoServidor);
////	sem_wait(&semaforoCliente);
//
//	cerrarSocket(fdCliente);
//	pthread_exit(0);
//}
//
///*
//int main(int argc, char **argv) {
//	int fdArchivo, fdEstructura, fdArchConfig;
//	fdArchivo = fdEstructura = fdArchConfig = 0;
//
//	char* dirArchivo 			= "/tmp/archivoProcesar.txt";
//	char* dirArchivoEstructura 	= "/tmp/archivoEstructura.txt";
//	char* dirArchivoConfig 		= "/tmp/archivoConfig.txt";
//
//
//    fdArchConfig = open(dirArchivoConfig, O_RDONLY);
//	fdArchivo 	 = open(dirArchivo, O_RDWR);
//	fdEstructura = open(dirArchivoEstructura, O_RDWR | O_CREAT);
//
//	crearFileSystem();
//	inicializarFilesystem();
//	levantarConsola();
//
//	return 0;
//
//}
//*/
