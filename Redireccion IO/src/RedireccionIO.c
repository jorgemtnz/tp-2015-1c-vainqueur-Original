#include <stdio.h>
#include <unistd.h>
#include "/home/utnso/TpOperativos/mapeoAMemoria/mapeoAMemoria.h"

#define NUMERO_PIPES 2
#define PIPE_LECTURA_PADRE 0
#define PIPE_ESCRITURA_PADRE 1
/* Siempre que se usen pipes:
 * 1 para escribir
 * 0 para leer
 */
#define ESCRIBIR_FD 1
#define LEER_FD 0
#define PADRE_LECTURA_FD (pipes[PIPE_LECTURA_PADRE][LEER_FD])
#define PADRE_ESCRITURA_FD (pipes[PIPE_ESCRITURA_PADRE][ESCRIBIR_FD])
#define HIJO_LECTURA_FD (pipes[PIPE_ESCRITURA_PADRE][LEER_FD])
#define HIJO_ESCRITURA_FD (pipes[PIPE_LECTURA_PADRE][ESCRIBIR_FD])

int pipes[NUMERO_PIPES][2];

//void ejecutarRedireccionandoIO (entrada,salida,funcion);

int main( entrada, salida, funcion) {
	//Definido para el mapeo
	char* ptrComienzoMemoriaMapeada;
	int * ptrTamanioPagina;
	//Inicializacion pipes de lectura y escritura
	pipe(pipes[PIPE_ESCRITURA_PADRE]);
	pipe(pipes[PIPE_LECTURA_PADRE]);
	mapeoAmemoria("ArchivoPrueba.txt", ptrComienzoMemoriaMapeada, ptrTamanioPagina);
	if (fork() == 0) {
		//Proceso Hijo
		/*Asigno el proceso "bc" a argv, bc permite hacer cuentas y demas
		 * , lo inicializo con el argumento -q asi no muestra mensaje de bienvenida
		 y le paso una cuenta por pipe desde el padre por entrada standar
		 */
		char *argv[] = { "/usr/bin/bc", "-q", 0 };
		//Duplico el fd de lectura del hijo al fd de la entrada standar
		if (dup2(HIJO_LECTURA_FD, STDIN_FILENO) == -1) {
			perror(
					"[ERROR] Funcion DUP2: No se pudo duplicar el File Descriptor para la entrada\n");
			exit(-1);
		}
		//Duplico el fd de escritura del hijo al fd de la salida standar
		dup2(HIJO_ESCRITURA_FD, STDOUT_FILENO);
		if (dup2(HIJO_LECTURA_FD, STDIN_FILENO) == -1) {
			perror(
					"[ERROR] Funcion DUP2: No se pudo duplicar el File Descriptor para la salida\n");
			exit(-1);
		}

		//Cierro los pipes que no se van a usar

		close(PADRE_LECTURA_FD);
		close(PADRE_ESCRITURA_FD);
		close(HIJO_LECTURA_FD);
		close(HIJO_ESCRITURA_FD);

		//Ejecuto proceso en argv[0]
		execv(argv[0], argv);

	} else {
		//Proceso Padre
		char buffer[100];
		int contador = 0;

		/* Cierro los pipes que le hijo no va a usar */
		close(HIJO_ESCRITURA_FD);
		close(HIJO_LECTURA_FD);

		// Escribo a la entrada del hijo
		write(PADRE_ESCRITURA_FD, "1000 * 8\n", 9);

		// Leo de la salida standar del hijo
		contador = read(PADRE_LECTURA_FD, buffer, sizeof(buffer) - 1);
		if (contador >= 0) {
			buffer[contador] = 0;
			printf("%s", buffer);
		} else {
			printf("Error I/O\n");
		}
	}
}
