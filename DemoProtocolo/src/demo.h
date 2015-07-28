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

void imprimirAlumno(unaStr* alumno);

#endif /* DEMO_H_ */
