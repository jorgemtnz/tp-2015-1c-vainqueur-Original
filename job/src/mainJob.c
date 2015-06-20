#include "job.h"

int main(int argc, char **argv){

	char nomArchivo[LONGPATH];

	printf("Ingrese el nombre del archivo de configuracion del job: ");
	fgets(nomArchivo,LONGPATH,stdin); // /home/utnso/TPOperativos/job/archivo.configuracion
	borrarBarraEneAString(nomArchivo);

	leerArchivoDeConfiguracion(nomArchivo); // Falta el arrays de archivos

	int fdJob = crearSocket();
	conectarSocket(fdJob,vg_ipMarta,vg_puertoMarta);

	char msg[]="3 Marta, indicame a que archivos les habo un job";
	int bytes_enviados = enviarPorSocket(fdJob,msg,strlen(msg));

	return 0;
}
