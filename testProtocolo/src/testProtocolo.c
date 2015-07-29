/*
 ============================================================================
 Name        : testProtocolo.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <protocolo/protocolo.h>


int main(void) {
	char* testBuffer = "1TestHeaderYPayload";
	int pruebaHeader = 0;
	char* payload;

	// Carga datos test 1.2.1
	unNodoBloqueParaEnviar nodoBloqueuno;
	void* paraEnviar;

	void* paraRecibir;


	t_escrituraBloque* escribeEnNodo = (t_escrituraBloque*)malloc(37);

	nodoBloqueuno.numeroCopia = 1;
	nodoBloqueuno.numeroDeBloqueDelNodo = 1;
	nodoBloqueuno.numeroNodo = 1;

	escribeEnNodo->bloqueListo = "TestSerializacionEscrituraBloque";
	escribeEnNodo->unNodoBloque = nodoBloqueuno;

	(void *)escribeEnNodo;
	// Test 1.1.0 -- OK --
	paraEnviar = prepararParaEnviar(ESCRITURA_BLOQUE, escribeEnNodo);
	(char*)paraEnviar;
	printf("%s",paraEnviar);

	// Test 1.2.0 --NOK -- Segm Fault
	paraRecibir = obtenerEstructura(paraEnviar);


	// Test 1.1.1  -- OK --
	pruebaHeader = obtenerHeader(testBuffer);

	printf("%d\n", pruebaHeader);
	// Test 1.1.2  -- OK --
	payload = obtenerPayload(testBuffer);
	printf("%s \n", payload);

	return 0;
}
