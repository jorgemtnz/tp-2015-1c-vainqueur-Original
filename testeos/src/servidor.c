//#include <sockets/sockets.h>
//#include <stdio.h>
//#include<stdlib.h>
//
//typedef struct persona {
//	char* nombre;
//	int edad;
//} persona;

//int mainSOLO() {
//
//	persona* alumno = malloc(sizeof(persona));
//	int fdServidor = crearSocket();
//	asociarSocket(fdServidor, 8889);
//	escucharSocket(fdServidor, 3);
//	int fdCliente = aceptarConexionSocket(fdServidor);
//
////char buffer[4]; //tamnio del mensaje
////char buff[24];  // mensaje
////char nombre [300];
////char edad[30];
////char bufRecib[300];
//	char buffer[1024];
//	char* tmp = '\0';
//	int tamanioPrimerCampo=0;
//	int tamanioSegundoCampo=0;
//	int tamanioMensaje=0;
//
//	memset(buffer,'\0',sizeof(char)*1024);
//	recibirPorSocket(fdCliente, buffer, 1024);  // recibo y guardo 4 bytes
////int numeroREcibidos = atoi(buffer);
////printf("Bytes recibidos: %d\n",numeroREcibidos);
////del buffer los primeros 4 bytes son el tipo de mensaje
//// en este caso es una estructura, entonces  paso dos campos.
//// recibo los tamanios de cada campo.
//
//	memcpy(&tamanioPrimerCampo, buffer + 4, 4);
//	memcpy(&tamanioSegundoCampo, buffer + 4 + tamanioPrimerCampo, 4);
//
//	memcpy(&(alumno->nombre), buffer + 12, tamanioPrimerCampo);
//	memcpy(&(tmp), buffer + 12 + tamanioPrimerCampo, tamanioSegundoCampo);
//
//	alumno->edad = atoi(tmp);
////
////void *buffer = malloc(5);
////recv(mySocket, buffer, 5, ...);
////struct my_struct_t *myStruct = malloc(sizeof(struct my_struct_t));
////memcpy(&(myStruct->aChar), buffer, 1);
////memcpy(&(myStruct->anInt), buffer + 1, 4);
////
////size_t messageLength;
////recv(mySocket, &messageLength, 4, ...);
////void *message = malloc(messageLength);
////recv(mySocket, message, messageLength, ...);
//
////recibirPorSocket( fdCliente, buff, numeroREcibidos);
////printf("Cadena: %s\n",buff);
//
////recibirPorSocket( fdCliente, bufRecib, 300);
////printf("Cadena: %s\n",bufRecib);
////
//// memcpy(nombre, bufRecib, 5);
////
////printf("nombre: %s\n",nombre);
//
//	cerrarSocket(fdServidor);
//	return 0;
//}
