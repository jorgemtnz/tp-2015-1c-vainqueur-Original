/*
 * consola.c
 *
 *  Created on: 21/4/2015
 *      Author: utnso
 */


#include <stdio.h>
#include <string.h>
#include "consola.h"

int main (int argc, char * argv[]){
		int cont = 1;
		int r1 ;// resultado de la evaluacion de string
		char* comandoIngresado;
		char* directorio;


		printf("Palabras Ingresadas por consola: \n");
		printf("Palabra 1: %s \n", argv[1]);
		printf("Palabra 2: %s \n", argv[2]);
		printf("Palabra 3: %s \n", argv[3]);
		printf("Palabra 4: %s \n", argv[4]);
/*
		cargarComandos();


		printf("-------Comandos cargados------- \n");

	//while(1){

		printf("Pedime lo que quieras>>>");

		stdin("%s",&comandoIngresado);

		//do{


		r1 = strcmp(&comandoIngresado, listaComandos [cont].comando);//compara si el comandoIngresado existe
		printf("%d",r1);


			cont = cont+1;
		//}while((r1 != 0) ||(cont > 30));//sale cuando r1 da 0 o cuando el cont supera los comandos

		/*
			if (r1 == 0){
				void aplicarComando(cont);
			}
			else
			{
				printf("Comando invalido, te recomiendo que uses la funcion man \n");
			}

*/









	return 0;
}


void aplicarComando (int a){ //selecciona un case en base al numero que llevaba el contador


	switch (a)
	{
	case 1:
		printf("Esta es la funcion formatear \n");
		break;
	}


}

void cargarComandos (void){ //deben cargarse las funciones respetando los numeros del case
	listaComandos [1].comando = "formatear";

}
