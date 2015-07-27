#include "filesystem.h"

sem_t semServAMartha;
sem_t semSerANodos;
//prototipos
void* servidorAMartha();
void* servidorANodos();

int main(int argc, char **argv) {

	int error, errorOtro;

	 leerArchivoDeConfiguracion();
//	 testleerArchivoDeConfiguracion();

	error = sem_init(&semServAMartha, 0, 0);
	errorOtro = sem_init(&semSerANodos, 0, 0);
	if ((error < 0) || (errorOtro < 0)) {
		perror("[ERROR]: inicializando semaforo");
		exit(-1);
	}

	pthread_t tidServidorAMartha;
	pthread_t tidServidorANodos;
	pthread_attr_t atributos1, atributos2;
	pthread_attr_init(&atributos1);
	pthread_attr_init(&atributos2);
	pthread_create(&tidServidorAMartha, &atributos1, servidorAMartha, NULL);
	pthread_create(&tidServidorANodos, &atributos2, servidorANodos, NULL);

	pthread_join(tidServidorAMartha, NULL);
	pthread_join(tidServidorANodos, NULL);

//	se escribe en pseudocodigo lo que se debe hacer para luego irlo programando
//crearFilesystem
//inicializar filesystem
//leer archivoDeConfiguracion
//crear hilos, uno servidorAMartha y otro servidorANodos y hacer uso del join para que el hilo del main los espere
//
//servidorAMartha
//se encarga de las comunicaciones con Martha. debe ser un servidor que se conecta con un solo cliente
//dentro de un ciclo infinito -donde martha es quien se conecta.
//manejar los mensajes por socket
//1. mensaje de martha que pide ubicacion de archivos
//
//servidorANodos
//se encarga de las comunicaciones con los nodos, debe ser un hilo concurrente con select- donde se recibe
//una cantidad de nodos en el archivo de configuracion
//levantarConsola y en funcion de  lo que se va pidiendo se debe
//dentro de un ciclo infinito manejar mensajes por socket

	return 0;
}

void* servidorAMartha() {
	int sockEscucha;
	int sockTranferencia;
	void* buffer[1024];


	sockEscucha = crearSocket();
	asociarSocket(sockEscucha, vg_puerto_listen_marta);
	escucharSocket(sockEscucha, 1);
	sockTranferencia = aceptarConexionSocket(sockEscucha);
//sockTranferencia se puede usar para send y recv
//aca se debe implementar
	recibirPorSocket(sockTranferencia, buffer, 1024);
	printf("mensaje de marta: %s \n", buffer);

	cerrarSocket(sockEscucha);
	cerrarSocket(sockTranferencia);
	return NULL;
}

void* servidorANodos() {
	//servidor concurrente



	int master_socket, addrlen, sockTransferencia, client_socket[30],
			max_clients = 30, activity, i, valread, sd;
	int max_sd;
	struct sockaddr_in address;

	char buffer[1025];  //data buffer of 1K

	//set of socket descriptors
	fd_set readfds;
	//inicializar el arreglo de socket_clientes
	for (i = 0; i < max_clients; i++) {
		client_socket[i] = 0;
	}
	master_socket = crearSocket();
	asociarSocket(master_socket, vg_puerto_listen_nodo);
	escucharSocket(master_socket, CONECCIONES_ENTRANTES_PERMITIDAS);

	while (1) {
		//clear the socket set
		FD_ZERO(&readfds);

		//add master socket to set
		FD_SET(master_socket, &readfds);
		max_sd = master_socket;

		//add child sockets to set
		for (i = 0; i < max_clients; i++) {
			//socket descriptor
			sd = client_socket[i];

			//if valid socket descriptor then add to read list
			if (sd > 0)
				FD_SET(sd, &readfds);

			//highest file descriptor number, need it for the select function
			if (sd > max_sd)
				max_sd = sd;
		}

		//wait for an activity on one of the sockets , timeout is NULL , so wait indefinitely
		activity = select(max_sd + 1, &readfds, NULL, NULL, NULL);

		if ((activity < 0) && (errno != EINTR)) {
			printf("select error");
		}

		//If something happened on the master socket , then its an incoming connection
		if (FD_ISSET(master_socket, &readfds)) {
			sockTransferencia = aceptarConexionSocket(master_socket);
			//se empieza a hablar
			   recibirPorSocket(sockTransferencia,buffer, 1025);
			               printf("de nodo  %s,\n", buffer);

			//add new socket to array of sockets
			for (i = 0; i < max_clients; i++) {
				//if position is empty
				if (client_socket[i] == 0) {
					client_socket[i] = sockTransferencia;
					break;
				}
			}
		}
		//else its some IO operation on some other socket :)
		for (i = 0; i < max_clients; i++) {
			sd = client_socket[i];

			if (FD_ISSET(sd, &readfds)) {
				//Check if it was for closing , and also read the incoming message
				if ((valread = read(sd, buffer, 1024)) == 0) {
					//Somebody disconnected , get his details and print
					getpeername(sd, (struct sockaddr*) &address,
							(socklen_t*) &addrlen);
					printf("Host disconnected , ip %s , port %d \n",
							inet_ntoa(address.sin_addr),
							ntohs(address.sin_port));

					//Close the socket and mark as 0 in list for reuse
					close(sd);
					client_socket[i] = 0;
				}

				//Echo back the message that came in
				else {
					//set the string terminating NULL byte on the end of the data read
					buffer[valread] = '\0';
					send(sd, buffer, strlen(buffer), 0);
				}
			}

		}

	}

	return NULL;
}
