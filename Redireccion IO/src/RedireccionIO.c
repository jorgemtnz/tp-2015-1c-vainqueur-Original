#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
//#include "../home/utnso/TpOperativos/mapeoAMemoria/mapeoAMemoria.h"

#define NUMERO_PIPES 2
#define NUMERO_CANALES 2
#define LECTURA_PADRE 0
#define ESCRITURA_PADRE 1
/* Siempre que se usen pipes:
 * 1 para escribir
 * 0 para leer
 */
#define ESCRIBIR 1
#define LEER 0
#define CANAL_LECTURA_PADRE (pipes[LECTURA_PADRE][LEER])
#define CANAL_ESCRITURA_PADRE (pipes[ESCRITURA_PADRE][ESCRIBIR])
#define CANAL_LECTURA_HIJO (pipes[ESCRITURA_PADRE][LEER])
#define CANAL_ESCRITURA_HIJO (pipes[LECTURA_PADRE][ESCRIBIR])

int pipes[NUMERO_PIPES][NUMERO_CANALES];

//void ejecutarRedireccionandoIO (entrada,salida,funcion);

int main() {
	int fdArchivoSalida,fdArchivoEntrada;

	//Inicializacion pipes de lectura y escritura
	pipe(pipes[ESCRITURA_PADRE]);
	pipe(pipes[LECTURA_PADRE]);
	/*mapeoAmemoria("ArchivoPrueba.txt", ptrComienzoMemoriaMapeada,
			ptrTamanioPagina);*/
	if (fork() == 0) {
		//Proceso Hijo
		/*Asigno el proceso "bc" a argv, bc permite hacer cuentas y demas
		 * , lo inicializo con el argumento -q asi no muestra mensaje de bienvenida
		 y le paso una cuenta por pipe desde el padre por entrada standar
		 */
		fdArchivoSalida = open("/tmp/Salida.txt", O_RDWR  | O_CREAT);
		fdArchivoEntrada = open("Entrada.txt", O_RDONLY);
		char *argv[] = { "/usr/bin/bc", "-q", 0 };
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

		close(CANAL_LECTURA_PADRE);
		close(CANAL_ESCRITURA_PADRE);
		close(CANAL_LECTURA_HIJO);
		close(CANAL_ESCRITURA_HIJO);

		//Ejecuto proceso en argv[0]
		execv(argv[0], argv);

	} else {

		/* Cierro los pipes que le hijo no va a usar */
		close(CANAL_ESCRITURA_HIJO);
		close(CANAL_LECTURA_HIJO);

		// Escribo a la entrada del hijo
		//write(CANAL_ESCRITURA_PADRE, "3000 * 8\n", 9);

		// Leo de la salida standar del hijo
		/*contador = read(CANAL_LECTURA_PADRE, buffer, sizeof(buffer) - 1);
		if (contador >= 0) {
			buffer[contador] = 0;
			printf("%s", buffer);
		} else {
			printf("Error I/O\n");
		}*/
	}
	return 0;
}
