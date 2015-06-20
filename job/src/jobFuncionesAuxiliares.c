#include"job.h"

void leerArchivoDeConfiguracion(char* nomArchivo) {
	// El archivo config de job tiene IP_MARTA PUERTO_MARTA MAPPER REDUCE COMBINER ARCHIVOS RESULTADO
	t_config* archivoConfig = config_create(nomArchivo);

	vg_puertoMarta 	= config_get_int_value(archivoConfig, "PUERTO_MARTA");

	vg_ipMarta 		= strdup(config_get_string_value(archivoConfig, "IP_MARTA"));
	vg_mapperPath 	= strdup(config_get_string_value(archivoConfig, "MAPPER"));
	vg_reducerPath	= strdup(config_get_string_value(archivoConfig, "REDUCER"));
	vg_resultado 	= strdup(config_get_string_value(archivoConfig, "RESULTADO"));

	// Usamos define para tratar al combiner con numeros
	char* temporal = strdup(config_get_string_value(archivoConfig, "COMBINER"));
	if (strcmp(temporal, "SI") == 0) {
		vg_combiner = ACEPTA_COMBINER;
	}
	if (strcmp(temporal, "NO") == 0) {
		vg_combiner = NO_ACEPTA_COMBINER;
	}

	//vg_archivos = config_get_array_value(archivoConfig, "ARCHIVOS");
	config_destroy(archivoConfig);
}

void liberaMemoriaLista(t_list* lista, int* cantElementos,
		void (*funcionLiberaElemento)(void*)) {
	int posicion;
	for (posicion = 0; posicion <= *cantElementos; posicion++) {
		list_remove_and_destroy_element(lista, posicion, funcionLiberaElemento);
	}

}

void sinBarraEne(char* cadena){
	char* p;
	p = strchr(cadena,'\n');
	if(p){
		*p = '\0';
	}
}

