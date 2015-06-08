#define NUMERO_PIPES 1
#define NUMERO_CANALES 2
#define LECTURA_PADRE 0
#define ESCRITURA_PADRE 1
/*Siempre que se usen pipes:
 1 para escribir
 0 para leer
 */
#define ESCRIBIR 1
#define LEER 0
//#define CANAL_LECTURA_PADRE (pipes[LECTURA_PADRE][LEER])
#define CANAL_ESCRITURA_PADRE (pipes[ESCRITURA_PADRE][ESCRIBIR])
#define CANAL_LECTURA_HIJO (pipes[ESCRITURA_PADRE][LEER])
// #define CANAL_ESCRITURA_HIJO (pipes[LECTURA_PADRE][ESCRIBIR])

int pipes[NUMERO_PIPES][NUMERO_CANALES];

//Si no se usan los pipes los voy a borrar despues para optimizar mas el codigo
//void ejecutarRedireccionandoIO (entrada,salida,funcion);

int ejecutarScriptRedireccionandoIO(char * dirArchivoSalida,
		char * ptrDireccionMapeo, char * dirScript, char * nombreScript); //Recibe un archivo de entrada, uno de salida, direccion del script y nombre del script a ejecutar.
