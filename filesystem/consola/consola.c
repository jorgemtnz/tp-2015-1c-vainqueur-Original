/*
 * consola.c
 *
 *  Created on: 21/4/2015
 *      Author: utnso
 */


#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "consola.h"


	int main (){
		int indiceComando;
		char* comando = malloc (200) ;
		char* funcion = malloc (200);
		char* dir = malloc(1000);

	cargarFunciones();


				printf("-------Comandos cargados------- \n");

	while(1)	{

		printf("Pedime lo que quieras>>>");

		fgets(comando,200,stdin);//se ingresa todo el comando
		sscanf(comando,"%s %s",funcion , dir);// divide el comando en funcion y directorio



			indiceComando = buscarFunciones(funcion);//busca la funcion

			aplicarFunciones (indiceComando,dir);




	}



return 0;
	}


void aplicarFunciones (int a, char* d){ //selecciona un case en base al numero que llevaba el contador y aplica la funcion recibe el dir


	switch (a)
	{
	case 1:
		printf("Esta es la funcion formatear \n y el directorio ingresado es = %s \n", d);
		break;
	case 2:
		printf("Esta es la funcion eliminar \n y el directorio ingresado es = %s \n", d);
				break;
	case 3:
		printf("Esta es la funcion renombrar \n y el directorio ingresado es = %s \n", d);
				break;
	case 4:
		printf("Esta es la funcion mover \n y el directorio ingresado es = %s \n", d);
				break;
	case 5:
		printf("Esta es la funcion crearD \n y el directorio ingresado es = %s \n", d);
				break;
	case 6:
		printf("Esta es la funcion eliminarD \n y el directorio ingresado es = %s \n", d);
				break;
	case 7:
		printf("Esta es la funcion renombrarD \n y el directorio ingresado es = %s \n", d);
				break;
	case 8:
		printf("Esta es la funcion moverD \n y el directorio ingresado es = %s \n", d);
				break;
	case 9:
		printf("Esta es la funcion copiar \n y el directorio ingresado es = %s \n", d);
				break;
	case 10:
		printf("Esta es la funcion copiarFSL \n y el directorio ingresado es = %s \n", d);
				break;
	case 11:
		printf("Esta es la funcion md5 \n y el directorio ingresado es = %s \n", d);
				break;
	case 12:
		printf("Esta es la funcion verB \n y el directorio ingresado es = %s \n", d);
				break;
	case 13:
		printf("Esta es la funcion borrarB \n y el directorio ingresado es = %s \n", d);
				break;
	case 14:
		printf("Esta es la funcion copiarB \n y el directorio ingresado es = %s \n", d);
				break;
	case 15:
		printf("Esta es la funcion agregarN \n y el directorio ingresado es = %s \n", d);
				break;
	case 16:
		printf("Esta es la funcion eliminarN \n y el directorio ingresado es = %s \n", d);
				break;
	case 17:
		mostrarFunciones();
				break;
	case 18:
		printf("--Ojo ese comando no existe!! proba con --man\n");
	}


}

void cargarFunciones (void){ //deben cargarse las funciones respetando los numeros del case
	  listaComandos [1].comandos = "formatear";
	  listaComandos [1].descripcion = "Funcion --formatear dir--";
	  listaComandos [2].comandos = "eliminar";
	  listaComandos [2].descripcion = "Funcion --eliminar dir/archv--";
	  listaComandos [3].comandos = "renombrar";
	  listaComandos [3].descripcion = "Funcion --renombrar dir/archv--";
	  listaComandos [4].comandos = "mover";
	  listaComandos [4].descripcion = "Funcion --mover dir/archv--";
	  listaComandos [5].comandos = "crearD";
	  listaComandos [5].descripcion = "Funcion --crearD dirNuevo--";
	  listaComandos [6].comandos = "eliminarD";
	  listaComandos [6].descripcion = "Funcion --eliminarD dir--";
	  listaComandos [7].comandos = "renombrarD";
	  listaComandos [7].descripcion = "Funcion --renombrarD dir dirNuevo";
	  listaComandos [8].comandos = "moverD";
	  listaComandos [8].descripcion = "Funcion --moverD dir Adir";
	  listaComandos [9].comandos = "copiar";
	  listaComandos [9].descripcion = "Funcion --copiar dir";
	  listaComandos [10].comandos = "copiarFSL";
	  listaComandos [10].descripcion = "Funcion --copiarFSL dir/archv dirFSlocal";
	  listaComandos [11].comandos = "md5";
	  listaComandos [11].descripcion = "Funcion --md5 dir/archv";
	  listaComandos [12].comandos = "verB";
	  listaComandos [12].descripcion = "Funcion --verB dir/archv(bloque)";
	  listaComandos [13].comandos = "borrarB";
	  listaComandos [13].descripcion = "Funcion --borrarB dir/archv(bloque)";
	  listaComandos [14].comandos = "copiarB";
	  listaComandos [14].descripcion = "Funcion --copiarB dir/archv(bloque)";
	  listaComandos [15].comandos = "agregarN";
	  listaComandos [15].descripcion = "Funcion --agregarN nombreNodo";
	  listaComandos [16].comandos = "eliminarN";
	  listaComandos [16].descripcion = "Funcion --eliminarN nombreNodo";
	  listaComandos [17].comandos = "man";
	  listaComandos [17].descripcion = "Funcion --manual de comandos(vamos boca)";
	  listaComandos [18].comandos ="\n";
}

int buscarFunciones(char* a){//busca la funcion ingresada
	int cont = 0, r ;

	do{
		cont = cont + 1;
		r = strcmp(a, listaComandos [cont].comandos);

	}while((cont < 18) && (r != 0));//sale si la encuentra o si cont supera las funciones buscadas

	if (cont >= 18){

		return 18;
	}

return cont;
}
void mostrarFunciones() {//va mostrando todas las funciones cargadas
	int cont2 = 0;
		do{
			cont2 = cont2 + 1;
			printf("*------------------------------------------*\n");
			printf("COMANDO = %s\n",listaComandos [cont2].comandos);
			printf("DESCRIPCION = %s\n",listaComandos [cont2].descripcion);
			printf("*------------------------------------------*\n");

		}while(cont2<=16);
}
