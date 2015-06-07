#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>

typedef struct temp
{
	char* nombre;
	char* dirArchivoTemporal;
	struct temp* ptrSgt;
} temp;

temp inicializa(int* fdArchivo, char* dirArchivoDatos)
{
	temp listaArchivoTemporal;
	listaArchivoTemporal.dirArchivoTemporal = "/tmp/";
	listaArchivoTemporal.nombre = "vacio";
	listaArchivoTemporal.ptrSgt = NULL;
	fdArchivo = open(dirArchivoDatos, O_RDWR | O_CREAT); //abre el datos.bin o lo crea

//	ftruncate(fdArchivo, 2000000000); //lo hace de n bytes

	return listaArchivoTemporal;

}

int main()
{

	char* dirArchivoDatos = "/tmp/datos.txt";
	temp listaArchivoTemporal;
	char* dirArchivoConfig;
	char* dirArchivoLog;
	int fdArchivo;

	listaArchivoTemporal = inicializa(fdArchivo, dirArchivoDatos);

	close(fdArchivo);

	return 0;
}
