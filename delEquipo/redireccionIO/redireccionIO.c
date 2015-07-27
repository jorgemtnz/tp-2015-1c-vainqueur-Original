#include "redireccionIO.h"

int ejecutarScriptRedireccionandoIO(char * dirArchivoSalida,
		char * ptrDireccionMapeo, char * dirScript, char * nombreScript) {

	int  fdArchivoSalida;
	char *parametrosScript[] = { nombreScript, NULL };

	//Inicializacion pipes de lectura y escritura
	pipe(pipes[ESCRITURA_PADRE]);
	//pipe(pipes[LECTURA_PADRE]);

	pid_t pid;
	pid = fork();

	if (pid < 0) {
		perror("[ERROR] Fallo la funcion FORK\n");
		exit(-1);
	}

	if (pid == 0)
	{	// Comienza proceso Hijo
		// 1) Abro el archivo que voy a usar como salida
		fdArchivoSalida = open(dirArchivoSalida, O_RDWR | O_CREAT);

		// 2) Duplico el fd de lectura del hijo al fd de la entrada standar
		if (dup2(CANAL_LECTURA_HIJO, STDIN_FILENO) == -1) {
			perror("[ERROR] Funcion DUP2: No se pudo duplicar el File Descriptor para la entrada\n");
			exit(-1);
		}

		// 3) Duplico el fd de escritura del hijo al fd de la salida standar
		if (dup2(fdArchivoSalida, STDOUT_FILENO) == -1) {
			perror("[ERROR] Funcion DUP2: No se pudo duplicar el File Descriptor para la salida\n");
			exit(-1);
		}

		// 4) Cierro los pipes que no se van a usar
		/*close(CANAL_LECTURA_PADRE);
		 close(CANAL_ESCRITURA_HIJO);*/
		close(CANAL_ESCRITURA_PADRE);
		close(CANAL_LECTURA_HIJO);

		// 5) Ejecuto proceso en argv[0]
		if (execv(dirScript, parametrosScript) == -1) {
			perror("[ERROR] Funcion EXECV: No se pudo ejecutar el script ingresado\n");
			exit(-1);
		}

	} // Fin proceso hijo

	if (pid > 0)
	{ // Comienzo proceso padre
	  // 1) Cierro los pipes que le hijo no va a usar
		close(CANAL_LECTURA_HIJO);
		//close(CANAL_ESCRITURA_HIJO);

	  // 2) Recibo direccion de memoria del mapeo y lo mando por pipe al hijo
		if (write(CANAL_ESCRITURA_PADRE, ptrDireccionMapeo,
				sizeof(ptrDireccionMapeo)) == -1)
		{
			perror(	"[ERROR] Funcion WRITE: El padre no pudo escribir en el pipe\n");
			exit(-1);
		}
	} // Fin proceso padre

	return 0;
}

/* Esto es un ejemplo de como se puede llamar a la funcion
 int main() {
 printf("Ejecutando \n");

 if (ejecutarScriptRedireccionandoIO("Salida.txt", "Entrada.txt",
 "/usr/bin/sort", "") == 0) {
 printf("Ejecucion correcta \n");

 }
 return 0;
 }
 */
