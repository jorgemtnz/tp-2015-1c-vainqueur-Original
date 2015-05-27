#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

/*
 #define NUMERO_PIPES 2
 #define NUMERO_CANALES 2
 #define LECTURA_PADRE 0
 #define ESCRITURA_PADRE 1
 Siempre que se usen pipes:
 1 para escribir
 0 para leer

 #define ESCRIBIR 1
 #define LEER 0
 #define CANAL_LECTURA_PADRE (pipes[LECTURA_PADRE][LEER])
 #define CANAL_ESCRITURA_PADRE (pipes[ESCRITURA_PADRE][ESCRIBIR])
 #define CANAL_LECTURA_HIJO (pipes[ESCRITURA_PADRE][LEER])
 #define CANAL_ESCRITURA_HIJO (pipes[LECTURA_PADRE][ESCRIBIR])

 int pipes[NUMERO_PIPES][NUMERO_CANALES];
 */
//Si no se usan los pipes los voy a borrar despues para optimizar mas el codigo
//void ejecutarRedireccionandoIO (entrada,salida,funcion);
int ejecutarScriptRedireccionandoIO(char *, char *, char *, char *);

int main()
{
	printf("Ejecutando \n");
	if(ejecutarScriptRedireccionandoIO("Salida.txt", "Entrada.txt", "/usr/bin/sort","sort") == 0)
	{
		printf("Ejecucion correcta \n");
		return 0;
	}
}

int ejecutarScriptRedireccionandoIO(char * dirArchivoSalida,
		char * dirArchivoEntrada, char * dirScript, char * nombreScript) {

	int fdArchivoSalida, fdArchivoEntrada;
	char *parametrosScript[] = { nombreScript, NULL };
	//Inicializacion pipes de lectura y escritura
	/*pipe(pipes[ESCRITURA_PADRE]);
	 pipe(pipes[LECTURA_PADRE]);*/

	if (fork() == 0) {
		//Abro el archivo que voy a usar como salida
		fdArchivoSalida = open(dirArchivoSalida, O_RDWR | O_CREAT);
		//Abro el archivo que voy a usar como entrada
		fdArchivoEntrada = open(dirArchivoEntrada, O_RDONLY);
		char *argv[] = { dirScript};
		//Duplico el fd de lectura del hijo al fd de la entrada standar
		if (dup2(fdArchivoEntrada, STDIN_FILENO) == -1) {
			perror(
					"[ERROR] Funcion DUP2: No se pudo duplicar el File Descriptor para la entrada\n");
			exit(-1);
		}
		//Duplico el fd de escritura del hijo al fd de la salida standar
		if (dup2(fdArchivoSalida, STDOUT_FILENO) == -1) {
			perror(
					"[ERROR] Funcion DUP2: No se pudo duplicar el File Descriptor para la salida\n");
			exit(-1);
		}
		//Cierro los pipes que no se van a usar
		/*close(CANAL_LECTURA_PADRE);
		 close(CANAL_ESCRITURA_PADRE);
		 close(CANAL_LECTURA_HIJO);
		 close(CANAL_ESCRITURA_HIJO);*/
		//Ejecuto proceso en argv[0]
		if(execv(dirScript, parametrosScript) == -1)
		{
			perror(
			"[ERROR] Funcion EXECV: No se pudo ejecutar el script ingresado\n");
			exit(-1);
		}

	} else {

		/* Cierro los pipes que le hijo no va a usar */
		//close(CANAL_ESCRITURA_HIJO);
		//close(CANAL_LECTURA_HIJO);
	}
	return 0;
}
