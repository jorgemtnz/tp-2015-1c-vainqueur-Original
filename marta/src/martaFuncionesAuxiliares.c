#include "marta.h"


void testleerArchivoDeConfiguracion(){
	int i;
	printf("*********************** Valores Seteados ***********************\n");

	printf("Puerto de Marta:\t[%d]\n",vg_martaPuerto);
	printf("Puerto de FS:\t[%d]\n",vg_puertoFilesystem);
	printf("IP FS:\t\t[%s]\n",vg_ipFilesystem);
	printf("conexiones permitidas:\t[%d]\n",vg_conexionesPermitidas);

	printf("****************************** FIN ******************************\n");
}
