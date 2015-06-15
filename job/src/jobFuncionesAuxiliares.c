#include"job.h"

void leerArchivoDeConfiguracion(char* nomArchivo){
	// El archivo config de job tiene IP_MARTA PUERTO_MARTA MAPPER REDUCE COMBINER ARCHIVOS RESULTADO
	char* temporal;
	t_config* archivoConfig;

	archivoConfig = config_create(RUTACONFIGJOB);

	vg_ipMarta 		= config_get_string_value(archivoConfig, "IP_MARTA");
	vg_puertoMarta  = config_get_int_value(archivoConfig, "PUERTO_MARTA");
	vg_mapperPath 	= config_get_string_value(archivoConfig,"MAPPER");
	vg_reducerPath 	= config_get_string_value(archivoConfig,"REDUCER");
	temporal 		= config_get_string_value(archivoConfig, "COMBINER");

	if (strcmp(temporal, "SI") == 0) {
		vg_combiner = ACEPTA_COMBINER;
	}
	if (strcmp(temporal, "NO") == 0) {
		vg_combiner = NO_ACEPTA_COMBINER;
	}
	free(temporal);

	vg_archivos = config_get_array_value(archivoConfig, "ARCHIVOS");
	vg_resultado = config_get_string_value(archivoConfig,"RESULTADO");

	config_destroy(archivoConfig);
}

void liberaMemoriaLista(t_list* lista, int* cantElementos,
		void (*funcionLiberaElemento)(void*)) {
	int i = 0;
	for (; i <= *cantElementos; i++) {
		list_destroy_and_destroy_elements(lista, (void*) funcionLiberaElemento);
	}

}
