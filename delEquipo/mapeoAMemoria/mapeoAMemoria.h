/*
 * mapeoAMemoria.h
 *
 *  Created on: 4/6/2015
 *      Author: utnso
 */

#ifndef MAPEOAMEMORIA_H_
#define MAPEOAMEMORIA_H_

// ++++++ Manejo de Archivos ++++++
int  abreArchivo(char* dirArchivo); // Retorna un file descriptor
int  tamanio_archivo(int fd); 	    // Retorna el tamanio del archivo
void cierraArchivo(int fdArchivo);

// +++++++++++++++++++++++++ Funciones mapeo +++++++++++++++++++++++++
void* mapeaAMemoria(int tamanioPagina, int fdArchivo, char* ptrDirArchivo);
void  mapeoAmemoria(char* dirArchivo, void* ptrComienzoMemoriaMapeada, int* ptrTamanioDePagina); // Abre un archivo lo mapea a memoria y cierra el archivo
void  imprimeMapeo(int tamanioDelArchivo, char* ptrAMapeo);
void  desMapea(int tamanio, char* ptrAMapeo);

#endif /* MAPEOAMEMORIA_H_ */
