/*
 * consola.h
 *
 *  Created on: 27/4/2015
 *      Author: utnso
 */

#ifndef CONSOLA_CONSOLA_H_
#define CONSOLA_CONSOLA_H_

void cargarFunciones();
void aplicarFunciones();
int buscarFunciones(char* a);
void mostrarFunciones();
int levantaConsola();

typedef struct Funciones {
	char* comandos;
	char* descripcion;
} Funciones;

Funciones listaComandos[19];

#endif /* CONSOLA_CONSOLA_H_ */