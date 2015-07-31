/*
 * mainNodoNuevo.c
 *
 *  Created on: 31/7/2015
 *      Author: utnso
 */
#include "nodo.h"

int main(int argc, char **argv) {
	pthread_attr_t atributos[1];
	levantarArchivoConfiguracion();
		pthread_t escucha;
		logger = log_create("./nodoLog.log", "Nodo", true, LOG_LEVEL_INFO);
		logger_archivo = log_create("./nodoLog.log", "Nodo", false, LOG_LEVEL_INFO);
	//	fileDeDatos=mapearFileDeDatos();//La siguiente función va a mapear el archivo de datos que esta especificado en el archivo conf a memoria, y asignarle al puntero fileDeDatos la direccion donde arranca el file. Utilizando mmap()
		FD_ZERO(&master); // borra los conjuntos maestro y temporal
		FD_ZERO(&read_fds);
		int yes=1; // para setsockopt() SO_REUSEADDR, más abajo
		char identificacion[BUF_SIZE]; //para el mensaje que envie al conectarse para identificarse, puede cambiar
		//char bloquesTotales[2]; //tendra la cantidad de bloques totales del file de datos
		int *bloquesTotales;
//		struct sockaddr_in filesystem; //direccion del fs a donde se conectará
	//	struct sockaddr_in nodoAddr;
//		memset(&filesystem, 0, sizeof(filesystem));
		bloquesTotales=malloc(sizeof(int));
		printf("llega hasta aca \n");
			*bloquesTotales=sizeFileDatos/20971520;
			printf("llega hasta aca2 \n");
			listaNodosConectados=list_create();
			listaMappersConectados=list_create();
			listaReducersConectados=list_create();
			printf("llega hasta aca 3\n");
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
			/*
			El nodo ya se conectó al FS, ahora queda a la espera de conexiones de hilos mapper/hilos reduce/otros nodos
			*/

			if ((listener = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
					perror("socket");
					log_error(logger,"FALLO la creacion del socket");
					exit(-1);
				}
			// obviar el mensaje "address already in use" (la dirección ya se está usando)
			if (setsockopt(listener, SOL_SOCKET, SO_REUSEADDR, &yes,sizeof(int)) == -1) {
				perror("setsockopt");
				log_error(logger,"FALLO la ejecucion del setsockopt");
				exit(-1);
			}
			// enlazar
			printf("llega hasta aca 4\n");
			asociarSocket(listener,vg_puerto_Nodo);
			// escuchar
			if (listen(listener, 10) == -1) {
				perror("listen");
				log_error(logger,"FALLO el Listen");
				exit(1);
			}
			printf("llega hasta aca5 \n");
			FD_SET(listener,&master); //Agrego al listener al conjunto maestro
			if(listener>fdmax){
				fdmax=listener; //el fd máximo hasta el momento es el listener
			}
			printf("llega hasta aca6 \n");
			pthread_attr_init(&atributos[1]);
			//Creación del hilo que va a manejar nuevas conexiones / cambios en las conexiones
			 pthread_create(&escucha, &atributos[1], manejador_de_escuchas, NULL);


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

	return NULL;
}

void *manejador_de_escuchas(){
	printf("llega hasta aca7 hilo \n");
	int socketModificado,nbytes,newfd,addrlen;
	printf("Nodo en la espera de conexiones/solicitudes del FS\n");
	while(1) {
		read_fds = master;
		if (select(fdmax+1, &read_fds, NULL, NULL, NULL) == -1) {
			perror("select");
			log_error(logger,"FALLO el Select");
			exit(-1);
		}
		// explorar conexiones existentes en busca de datos que leer
		for(socketModificado = 0; socketModificado <= fdmax; socketModificado++) {
			if (FD_ISSET(socketModificado, &read_fds)) {	// ¡¡tenemos datos!!

				/* -- Nuevas conexiones(o nodo, o hilo map, o hilo reducer) --*/

				if(socketModificado==listener){
					addrlen=sizeof(struct sockaddr_in);
					if ((newfd = accept(listener, (struct sockaddr*)&remote_client,(socklen_t*)&addrlen)) == -1) {
						perror("accept");
						log_error(logger,"FALLO el ACCEPT");
						exit(-1);
					} else {//llego una nueva conexion, se acepto y ahora tengo que tratarla
						if((nbytes=recv(newfd,mensaje,sizeof(mensaje),0))<=0){ //error
							perror("recive");
							log_error(logger,"Falló el receive");
							exit(-1);
						}
						else{
							// el nuevo conectado me manda algo, se identifica como mapper, reducer o nodo
							if(nbytes>0 && strncmp(mensaje,"soy nodo",9)==0){
								//se conectó un nodo
								socketNodo=malloc(sizeof(int));
								*socketNodo=newfd;
								list_add(listaNodosConectados,socketNodo); //agrego el nuevo socket a la lista de Nodos conectados
								FD_SET(newfd,&master); //añadir al conjunto maestro
								if(newfd>fdmax){ //actualizar el máximo
									fdmax=newfd;
								}
								log_info(logger,"Se conectó el nodo %s",inet_ntoa(remote_client.sin_addr));
							}
							if(nbytes>0 && strncmp(mensaje,"soy mapper",11)==0){
								//se conectó un hilo mapper
								socketMapper=malloc(sizeof(int));
								*socketMapper=newfd;
								list_add(listaMappersConectados,socketMapper); //agrego el nuevo socket a la lista de Mappers conectados
								FD_SET(newfd,&master); //añadir al conjunto maestro
								if(newfd>fdmax){ //actualizar el máximo
									fdmax=newfd;
								}
								log_info(logger,"Se conectó un hilo mapper desde %s",inet_ntoa(remote_client.sin_addr));
							}
							if(nbytes>0 && strncmp(mensaje,"soy reducer",12)==0){
								//se conectó un hilo reducer
								socketReducer=malloc(sizeof(int));
								*socketReducer=newfd;
								list_add(listaReducersConectados,socketReducer); //agrego el nuevo socket a la lista de Reducers conectados
								FD_SET(newfd,&master); //añadir al conjunto maestro
								if(newfd>fdmax){ //actualizar el máximo
									fdmax=newfd;
								}
								log_info(logger,"Se conectó un hilo reducer desde %s",inet_ntoa(remote_client.sin_addr));
							}
						}
					}
				}

				/*-- Conexión con el fileSystem --*/

				if(socketModificado==conectorFS){
					if ((nbytes=recv(conectorFS,mensaje,sizeof(mensaje),0))==-1){ //da error
						perror("recv");
						log_error(logger,"Falló el receive");
						exit(-1);
					}
					if(nbytes==0){ //se desconectó
						close(conectorFS);
						FD_CLR(conectorFS,&master);
					}
					else{
						/* -- el filesystem envío un mensaje a tratar -- */
						}
				}

				//-- Conexión con otro nodo --//

				if(estaEnListaNodos(socketModificado)==0){
					if ((nbytes=recv(socketModificado,mensaje,sizeof(mensaje),0))==-1){ //da error
						perror("recv");
						log_error(logger,"Falló el receive");
						exit(-1);
					}
					if(nbytes==0){ //se desconectó
						close(socketModificado);
						FD_CLR(socketModificado,&master);
					}
					else{

						/* -- el nodo envío un mensaje a tratar -- */

					}
				}

				//-- Conexión con hilo mapper --//

				if(estaEnListaMappers(socketModificado)==0){
					char nomArchTemp[100];
					if ((nbytes=recv(socketModificado,mensaje,sizeof(mensaje),0))==-1){ //da error
						perror("recv");
						log_error(logger,"Falló el receive");
						exit(-1);
					}
					if(nbytes==0){ //se desconectó
						close(socketModificado);
						FD_CLR(socketModificado,&master);
					}
					else{
						/* -- el mapper envío un mensaje a tratar -- */
						char* rutinaMapper;
						rutinaMapper=strdup("");
						int numeroBloque;
						/*En el mensaje recibio el bloque a donde aplicar mapper*/
						printf("Se aplicará la rutina mapper en el bloque %d\n",*mensaje);
						memcpy(&numeroBloque,(*mensaje),sizeof(int));
						printf("numero de bloque %d\n",numeroBloque);
						/*Recibe el nombre del archivo temporal a donde guardar el mapper*/
						if(recv(socketModificado,nomArchTemp,sizeof(nomArchTemp),0)==-1){
							perror("recv");
							log_error(logger,"Fallo al recibir el nombre del archivo temporal donde guardar el Map");
							exit(-1);
						}
						printf("Se guardará el resultado del mapper en el archivo temporal %s\n",nomArchTemp);
						//Recibirá la rutina mapper


						if(recv(socketModificado,rutinaMapper,MAPPER_SIZE,0)==-1){
							perror("recv");
							log_error(logger,"Fallo al recibir la rutina mapper");
							exit(1);
						}
						printf("se recibió la rutina mapper:%s",rutinaMapper);


						char* ptrDireccionMapeo = getBloque(numeroBloque);
						if(ejecutarMap(nomArchTemp,ptrDireccionMapeo)){
							printf("se ejecuto correctamente la rutina mapper\n");

						}

					}
				}

				//-- Conexión con hilo reducer --//

				if(estaEnListaReducers(socketModificado)==0){
					if ((nbytes=recv(socketModificado,mensaje,sizeof(mensaje),0))==-1){ //da error
						perror("recv");
						log_error(logger,"Falló el receive");
						exit(-1);
					}
					if(nbytes==0){ //se desconectó
						close(socketModificado);
						FD_CLR(socketModificado,&master);
					}
					else{

						/* -- el reducer envío un mensaje a tratar -- */

					}
				}
			}
		}
	}
}
