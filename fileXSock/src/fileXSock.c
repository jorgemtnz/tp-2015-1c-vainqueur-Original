#include <stdio.h>
#include <stdlib.h>
#include <sockets/sockets.h>
#include <pthread.h>
#include <semaphore.h>

#define PUERTO 7878

sem_t semaforoServidor;
sem_t semaforoCliente;

void* servidor();
void* cliente();

int main() {
	// Semaforos
	if ( (sem_init(&semaforoCliente, 0, 0)) < 0){
		perror("[ERROR]: Funcion sem_init : Error al inicializar el semaforo");
		return -1;
	}
	if ( (sem_init(&semaforoServidor, 0, 0)) < 0){
		perror("[ERROR]: Funcion sem_init : Error al inicializar el semaforo");
		return -1;
	}

	// Threads
	pthread_t tidServidor, tidCliente;
	pthread_attr_t atributos1, atributos2;

	pthread_attr_init(&atributos1);
	pthread_attr_init(&atributos2);

	pthread_create(&tidServidor, &atributos1, servidor, NULL);
	pthread_create(&tidCliente , &atributos2, cliente, NULL);

	pthread_join(tidServidor, NULL);
	pthread_join(tidCliente, NULL);

	return 0;
}

void* servidor(){
    char Buffer;

    // Conexion
    int sock = crearSocket();
    asociarSocket(sock,PUERTO);
    escucharSocket(sock,1);

    // Semaforeo para que el cliente haga connect
    sem_post(&semaforoCliente);
    sem_wait(&semaforoServidor);

    int sock2 = aceptarConexionSocket(sock);

    // Creo el archivito para recibir
    FILE *archivo =  fopen( "textoRecibido.txt", "wb" );
    if( archivo == NULL ){
    	printf( "Error al intenter de abrir el archivoRecibido" );
    }
    rewind( archivo ); // Voy al principio del archivoRecibido

    // Semaforeo para que el cliente me mande cosas
    sem_post(&semaforoCliente);
    sem_wait(&semaforoServidor);

    while ( 1 ) //mientras estemos conectados con el cliente
    {   memset( &Buffer, '\0', sizeof(Buffer) );
        recibirPorSocket(sock2,&Buffer,1);
        if(Buffer == 0) break; // Si recibo un 0 se desconecta el fd
        fwrite( &Buffer, sizeof(char), 1, archivo );
    }
    cerrarSocket(sock);
    fclose( archivo );

    return NULL;
}


void* cliente(){
    char Buffer;

    // Semaforeo para que primero ejecute el server
    sem_wait(&semaforoCliente);
    int sock = crearSocket();
    conectarSocket(sock,"127.0.0.1",PUERTO);
    // Abro y leo el archivito a mandar
    FILE *archivo;
    if( (archivo = fopen( "texto.txt", "rb" )) == NULL )
    {
        printf( "Error al abrir el archivo [texto.txt]\n" );
    }
    rewind( archivo );

    // Semaforeo para que me acepte el server
    sem_post(&semaforoServidor);
    sem_wait(&semaforoCliente);

    while ( !feof( archivo ) )
    {
        fread ( &Buffer, sizeof(char), 1, archivo ); //lee byte en byte
        if( !feof( archivo ) )
            enviarPorSocket(sock,&Buffer, sizeof(char));
    }
    sem_post(&semaforoServidor);

    cerrarSocket(sock);
    fclose( archivo );

    return NULL;
}
