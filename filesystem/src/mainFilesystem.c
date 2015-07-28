#include "filesystem.h"

sem_t semServAMartha;
sem_t semSerANodos;
//prototipos
void* servidorAMartha();
void* servidorANodos();

int main(int argc, char **argv) {

	int error, errorOtro;
//  crearFileSystem();
//  inicializarFilesystem();
	leerArchivoDeConfiguracion();
	testleerArchivoDeConfiguracion();

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
	//recibir(sockTranferencia);
	recibirPorSocket(sockTranferencia, buffer, 1024);
	printf("mensaje de marta: %s \n", buffer);

	cerrarSocket(sockEscucha);
	cerrarSocket(sockTranferencia);
	return NULL;
}

void* servidorANodos() {
	//servidor concurrente

	levantarConsola();
	int fdConeccionesEntrantes, addrlen, sockTransferencia,
			listaClientesConectados[30], cantidadMaximaClientes = 30,
			numeroDeActividades, contador1, mensajeLeido, fdTemporal;
	int fdTemporalMaximo;
	struct sockaddr_in address;

	char buffer[1025];  //data buffer of 1K

	//set of socket descriptors
	//Set de sockets de lectura
	fd_set setFdLectura;
	//inicializar el arreglo de socket_clientes
	for (contador1 = 0; contador1 < cantidadMaximaClientes; contador1++) {
		listaClientesConectados[contador1] = 0;
	}
	//Creo un socket y lo pongo a escuchar
	fdConeccionesEntrantes = crearSocket();
	asociarSocket(fdConeccionesEntrantes, vg_puerto_listen_nodo);
	escucharSocket(fdConeccionesEntrantes, CONECCIONES_ENTRANTES_PERMITIDAS);

	while (1) {
		//clear the socket set
		//Seteo en 0 el set de sockets de lectura
		FD_ZERO(&setFdLectura);

		//add master socket to set
		//Agrego el socket de conecciones entrantes al set de lectura
		FD_SET(fdConeccionesEntrantes, &setFdLectura);
		fdTemporalMaximo = fdConeccionesEntrantes;

		//add child sockets to set
		//Agrego los sockets de clientes al set de lectura
		for (contador1 = 0; contador1 < cantidadMaximaClientes; contador1++) {
			//socket descriptor
			//Fd Temporal
			fdTemporal = listaClientesConectados[contador1];

			//if valid socket descriptor then add to read list
			//Si el fd temporal es valido lo agrego a la lista de lectura
			if (fdTemporal > 0)
				FD_SET(fdTemporal, &setFdLectura);

			//highest file descriptor number, need it for the select function
			//Se setea el numero maximo del file descriptor, se necesita para la funcion select
			if (fdTemporal > fdTemporalMaximo)
				fdTemporalMaximo = fdTemporal;
		}

		//wait for an numeroDeActividades on one of the sockets , timeout is NULL , so wait indefinitely
		//Espera indefinidamente actividad de uno de los sockets
		numeroDeActividades = select(fdTemporalMaximo + 1, &setFdLectura, NULL,
				NULL, NULL);

		if ((numeroDeActividades < 0) && (errno != EINTR)) {
			printf("[ERROR]: Error en select");
		}

		//If something happened on the fdConeccionesEntrantes , then its an incoming connection
		//Si se detecta actividad en fdConeccionesEntrantes, entonces hay una coneccion entrante
		if (FD_ISSET(fdConeccionesEntrantes, &setFdLectura)) {
			sockTransferencia = aceptarConexionSocket(fdConeccionesEntrantes);
			//se empieza a hablar
			recibirPorSocket(sockTransferencia, buffer, 1025);
			printf("Recibido del Nodo %s,\n", buffer);
			//debo recibir como primero , la IP y el puerto de este nodo y guardarlo en la lista de nodosConectados
			//add new socket to array of sockets
			//Se agrega el socket nuevo al vector de sockets
			for (contador1 = 0; contador1 < cantidadMaximaClientes;
					contador1++) {
				//if position is empty
				//Si la posicion en el vector de fd esta vacia (osea disponible)
				if (listaClientesConectados[contador1] == 0) {
					listaClientesConectados[contador1] = sockTransferencia;
					//guardar en la lista nodosconectados
					break;
				}
			}
		}
		// quizas aca se puede levantarConsola() , pero que no este en un while(1)
		//

		//else its some IO operation on some other socket :)
		//Si no es en la coneccion nueva es una operacion de IO en un socket que ya poseiamos
		for (contador1 = 0; contador1 < cantidadMaximaClientes; contador1++) {
			fdTemporal = listaClientesConectados[contador1];
			if (FD_ISSET(fdTemporal, &setFdLectura)) {
				//Check if it was for closing , and also read the incoming message
				//Se chequea si se perdio una coneccion o se cerro una coneccion
				if ((mensajeLeido = read(fdTemporal, buffer, 1024)) == 0) {
					//Somebody disconnected , get his details and print
					//Si alguien se desconecto se obtiene los detalles de quien se desconecto
					getpeername(fdTemporal, (struct sockaddr*) &address,
							(socklen_t*) &addrlen);
					printf("Host disconnected , ip %s , port %d \n",
							inet_ntoa(address.sin_addr),
							ntohs(address.sin_port));

					//Close the socket and mark as 0 in list for reuse
					//Se cierra el socket caido y se lo marca como no usado en la lista para volverlo a usar
					close(fdTemporal);
					listaClientesConectados[contador1] = 0;
				}

				//Echo back the message that came in
				//Se devuelve el mensaje a quien lo mando, se hace eco (el eco se hace solamente para enseñar,
				//no tiene sentido ni utilizacion real para nosotros)
				//Aca habria que hacer lo que nosotros queramos mandarle al socket
				else {
					//set the string terminating NULL byte on the end of the data read
					//Se agrega el '\0' al final de lo leido
					buffer[mensajeLeido] = '\0';
					send(fdTemporal, buffer, strlen(buffer), 0);
				}
			}

		}

	}

	return NULL;
}
