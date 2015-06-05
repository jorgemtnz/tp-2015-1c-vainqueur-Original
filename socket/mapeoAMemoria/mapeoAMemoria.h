/*
 * mapeoAMemoria.h
 *
 *  Created on: 4/6/2015
 *      Author: utnso
 */

#ifndef MAPEOAMEMORIA_H_
#define MAPEOAMEMORIA_H_

int tamanio_archivo(int);   			   // Da el tamaño del archivo en tamaño de pagina(es un tamaño para memoria)
int abreArchivo(char*); 				   // Abre un archivo, se le manda la ruta del archivo
char* mapeaAMemoria(int , int ,char* );    // Hace el mmap, recibe el tamaño pagina, ptr archivoAbierto, ptr DirArchivo
void imprimeMapeo(int , char* );   		   // Imprime lo que esta mapeado a memoria, para lo que recibe el tamaño de pagina y el ptr a lo mapeado.
void desMapea(int , char* ); 			   // Desmapea la memoria recibe tamaño pagina, ptr a lo mapeado
void cierraArchivo(int );   			   // Cierra archivo recibe el ptr Archivo abierto
void mapeoAmemoria(char* , char* , int* ); // Abre un archivo lo mapea a memoria y cierra el archivo,recibe dirección del archivo, un puntero al comienzo de la memoria mapeada, un puntero al tamaño de la pagina

#endif /* MAPEOAMEMORIA_H_ */
