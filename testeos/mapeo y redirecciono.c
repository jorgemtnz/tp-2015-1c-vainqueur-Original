//LEEME aca se testea que agarre el archivo y luego lo divida en las oraciones o partes que terminan en \n y que
// forman el bloque
// lo subo comentado porque voy a ir haciendo varios testeos. para ponerlo a funcionar quita el comentario, y correlo.
//seleccionar el comentario  y ctrl + shift + 7 para quitar el comentario automaticamente.
//esta ok, pero si te da errores , reviza las configuraciones del run configuracion, para pthread, y las LD_LIBRARY_PATH

#include<stdlib.h>
#include<stdio.h>
#include<commons/txt.h>
#include<commons/string.h>
#include <mapeoAMemoria/mapeoAMemoria.h>

//int main(int argc, char **argv) {
//	char** buffer = NULL;
//	char* dirArchivo;
//	char* ptrComienzoMemoriaMapeada = NULL;
//	int* ptrTamanioDePagina = NULL;
//	char** ptrAMemoriaModificado = NULL; //pendiente modificar nombre, es la que modifica la direccion del ptrAMemoria
//	ptrAMemoriaModificado = &ptrComienzoMemoriaMapeada; //se usa para poder hacer el paso por referencia y modificar a lo que apunta ptrComienzoMemoriaMapeada.
//
//
//	dirArchivo = strdup("/tmp/prueba.txt"); // esta linea sustituye a las dos anteriores.
//
//	//dirArchivo = malloc(strlen("/tmp/prueba.txt"));
//	//strcpy(dirArchivo, "/tmp/prueba.txt");
//
//	mapeoAmemoria(dirArchivo, ptrAMemoriaModificado, ptrTamanioDePagina);
//	buffer = string_split(ptrComienzoMemoriaMapeada, "\n");
//
//
//	printf("Contenido:%s\n", ptrComienzoMemoriaMapeada);
//
//	printf(" solo el bloque cero %s, \n solo el bloque dos %s \n",buffer[0], buffer[2]);
//	printf("mensaje prueba\n");
//	puts(buffer[0]);//aca si pongo un printf entonces no sale por pantalla,
//
//	desMapea(*ptrTamanioDePagina, ptrComienzoMemoriaMapeada);
//
//	return 0;
//}


