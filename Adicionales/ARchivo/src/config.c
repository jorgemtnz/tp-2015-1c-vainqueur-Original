#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <src/commons/config.h>

int main(void) {
	t_config * archivoConfiguracion;
	int num,num2;

	archivoConfiguracion = config_create("cat.cat");
	num = config_get_int_value(archivoConfiguracion,"NUMERO");
	printf("Valor del campo %d\n",num); /* prints !!!Hello World!!! */
	num2 = config_get_int_value(archivoConfiguracion,"NUMERO");
	printf("Valor del campo %d\n",num2); /* prints !!!Hello World!!! */
	config_destroy(archivoConfiguracion);
	return EXIT_SUCCESS;
}

