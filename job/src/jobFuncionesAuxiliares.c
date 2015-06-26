#include"job.h"

void leerArchivoDeConfiguracion() {
	// El archivo config de job tiene IP_MARTA PUERTO_MARTA MAPPER REDUCE COMBINER ARCHIVOS RESULTADO
	printf("Ingrese la ruta del archivo de configuracion del job: ");
	fflush(stdin);
	scanf("%s", vg_nombreArchivoConfigJob);
	t_config* archivoConfig = config_create(vg_nombreArchivoConfigJob);

	vg_puertoMarta = config_get_int_value(archivoConfig, "PUERTO_MARTA");

	vg_ipMarta 		= strdup(config_get_string_value(archivoConfig, "IP_MARTA"));
	vg_mapperPath 	= strdup(config_get_string_value(archivoConfig, "MAPPER"));
	vg_reducerPath 	= strdup(config_get_string_value(archivoConfig, "REDUCER"));
	vg_resultado 	= strdup(config_get_string_value(archivoConfig, "RESULTADO"));

	// Usamos define para tratar al combiner con numeros
	char* temporal = strdup(config_get_string_value(archivoConfig, "COMBINER"));
	if (strcmp(temporal, "SI") == 0) {
		vg_combiner = ACEPTA_COMBINER;
	}
	if (strcmp(temporal, "NO") == 0) {
		vg_combiner = NO_ACEPTA_COMBINER;
	}

	vg_archivos = config_get_array_value(archivoConfig, "ARCHIVOS");
	config_destroy(archivoConfig);
}

void* indicarArchivosAMarta(){
	int fdJob = crearSocket();
	conectarSocket(fdJob,vg_ipMarta,vg_puertoMarta);

	char msg[]="3 Marta, tengo este archivo [ARCHIVO], que hago";
	int msgSize = strlen(msg);
	enviarPorSocket(fdJob,msg,msgSize);

	char bufer[200];
	recibirPorSocket(fdJob,bufer,sizeof(bufer)); // Recibe los bloques a operar sus rutinas
	printf("%s",bufer);

	cerrarSocket(fdJob);

	return NULL;
}
