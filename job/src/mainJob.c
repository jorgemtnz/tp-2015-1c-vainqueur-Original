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
	enviarPorSocket(fdJob,msg,strlen(msg));

	// Recibir
	char bufer[20];
	int bytes_recibidos = recibirPorSocket(fdJob,bufer,sizeof(bufer));
	comprobarDesconexion(bytes_recibidos);
	printf("%s",bufer);

	return 0;
}
