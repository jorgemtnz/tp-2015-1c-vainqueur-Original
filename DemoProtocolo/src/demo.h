#ifndef DEMO_H_
#define DEMO_H_

#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <semaphore.h>
#include <sockets/sockets.h>
#include <protocolo/protocolo.h>

#define NO_IMPORTA_NUMERO 4
#define PUERTO 8989

typedef struct {
	int edad;
	float promedio;
	char * nombre;
}unaStr;

void imprimirAlumno(unaStr* alumno){
	printf("Nombre del alumno:\t[%s]\n",alumno->nombre);
	printf("Edad del alumno:\t[%d]\n",alumno->edad);
	printf("Promedio del alumno:\t[%.2f]\n",alumno->promedio);
	printf("\n");
}

#endif /* DEMO_H_ */
