#include "job.h"

int main(int argc, char **argv)
{
	char nomArchivo[LONGPATH];

	printf("Ingrese el nombre del archivo de configuracion del job: ");
	fgets(nomArchivo,LONGPATH,stdin);
	// /home/utnso/TPOperativos/job/archivo.configuracion
	sinBarraEne(nomArchivo);

	leerArchivoDeConfiguracion(nomArchivo);

	printf("Puerto:          %d\n",vg_puertoMarta);
	printf("IP marta:        %s\n",vg_ipMarta);
	printf("Mapper:          %s\n",vg_mapperPath);
	printf("Reducer:         %s\n",vg_reducerPath);
	printf("Acepta Combiner: %d\n",vg_combiner);
	printf("Resultado:       %s\n",vg_resultado);
	// Los archivos por ahora no los leemos porque es un array de strings

	return 0;

}
