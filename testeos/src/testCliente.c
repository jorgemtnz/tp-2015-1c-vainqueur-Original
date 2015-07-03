//#include <sockets/sockets.h>
//#include<string.h>
//#include<stdlib.h>
//
//typedef struct persona {
//	char* nombre;
//	int edad;
//} persona;

//int main() {
//	persona* alumno = malloc(sizeof(persona));
//	int i;
//	char* tmp;
//	tmp = malloc(sizeof(alumno->edad));
////tmp = '\0';
//
//	alumno->nombre = "jorge";
//	alumno->edad = 33;
//	sprintf(tmp, "%d", alumno->edad);
//	int tamanioPrimerCampo;
//	int tamanioSegundoCampo;
//	int tamanioMensaje;
//	char mensaje[1024];
//
////para que setee con vacios.
//	memset(mensaje, '\0', sizeof(char) * 1024);
//
////for(i=0; i < 300; i++){
////	mensaje[0] = '\0';
////}
//
////void *buffer = malloc(5);
////memcpy(buffer, &(myStruct.aChar), 1);
////memcpy(buffer + 1, &(myStruct.anInt), 4);
////send(mySocket, buffer, 5, ...);
//
//	strcat(mensaje, alumno->nombre);
//	strcat(mensaje, tmp);
//
//	tamanioPrimerCampo = strlen(alumno->nombre);
//	tamanioSegundoCampo = strlen(tmp);
//	tamanioMensaje = strlen(mensaje);
//
//	int fdCliente = crearSocket();
////conectarSocket(fdCliente,"127.0.0.1",8889);
//
//	size_t tipoMensaje = 5;
//	int tamanioTipoMensaje = 0;
//	tamanioTipoMensaje = sizeof(tipoMensaje);
////char *buffer = malloc (4 + tamanioMensaje + tamanioPrimerCampo + tamanioSegundoCampo);
//	char buffer[1024];
//
//	memset(buffer, '\0', 1024);
//
//	//size_t messageLength = strlen(message);
////void *buffer = malloc (4 + messageLength);
////memcpy(buffer, messageLength, 4);
////memcpy(buffer + 4, message, messageLength);
////send(mySocket, buffer, 4 + messageLength, ...);
//	memcpy(buffer, &tipoMensaje, tamanioTipoMensaje);
//
//	memcpy(buffer + tamanioTipoMensaje, &tamanioPrimerCampo,
//			tamanioPrimerCampo);
//
//	memcpy(buffer + tamanioTipoMensaje + tamanioPrimerCampo,
//			&tamanioSegundoCampo, tamanioSegundoCampo);
//
//	memcpy(
//			buffer + tamanioTipoMensaje + tamanioPrimerCampo
//					+ tamanioSegundoCampo, mensaje, tamanioPrimerCampo);
//
//	memcpy(buffer + 12 + tamanioPrimerCampo, mensaje + tamanioPrimerCampo,
//			tamanioSegundoCampo);
//
////	enviarPorSocket(fdCliente, buffer,
////			4 + tamanioPrimerCampo + tamanioSegundoCampo + tamanioMensaje);
////enviarPorSocket(fdCliente,"LucasCadena", 24);
//	printf("el buffer enviado %s  \n", buffer);
//
////enviarPorSocket(fdCliente, buffer, 300);
//
//	cerrarSocket(fdCliente);
//
//	return 0;
//}
