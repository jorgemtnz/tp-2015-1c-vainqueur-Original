/*
 * consola.h
 *
 *  Created on: 27/4/2015
 *      Author: utnso
 */

#ifndef CONSOLA_CONSOLA_H_
#define CONSOLA_CONSOLA_H_

void cargarComandos ();
void aplicarComando();

typedef struct comandos{
	char* comando;
	char* descripcion;
}comandos;

comandos listaComandos [16];

#endif /* CONSOLA_CONSOLA_H_ */
