#include "job.h"

void leerArchivoDeConfiguracion() {
	// El archivo config de job tiene IP_MARTA PUERTO_MARTA MAPPER REDUCE COMBINER ARCHIVOS RESULTADO

//	printf("Ingrese la ruta del archivo de configuracion del job: ");
//	fflush(stdin);
//	scanf("%s", vg_nombreArchivoConfigJob);
	// /home/utnso/TPOperativos/job/config_job.cfg
	vg_nombreArchivoConfigJob = "/home/utnso/TPOperativos/job/config_job.cfg";

	t_config* archivoConfig = NULL;

	if (checkearRutaArchivoConfig(vg_nombreArchivoConfigJob) == -1) {
		perror("[ERROR]: Archivo de configuracion no encontrado");
		log_error(logger, "[ERROR]: Archivo de configuracion no encontrado");
		exit(-1);
	} else {
		archivoConfig = config_create(vg_nombreArchivoConfigJob);
		vg_puertoMarta = config_get_int_value(archivoConfig, "PUERTO_MARTA");
		vg_PuertoNodo = config_get_int_value(archivoConfig, "PUERTO_NODO");
		vg_ipMarta = strdup(config_get_string_value(archivoConfig, "IP_MARTA"));
		vg_ipNodo = strdup(config_get_string_value(archivoConfig, "IP_NODO"));
		vg_mapperPath = strdup(
				config_get_string_value(archivoConfig, "MAPPER"));
		vg_reducerPath = strdup(
				config_get_string_value(archivoConfig, "REDUCER"));
		vg_resultado = strdup(
				config_get_string_value(archivoConfig, "RESULTADO"));

		// Usamos define para tratar al combiner con numeros
		char* temporal = strdup(
				config_get_string_value(archivoConfig, "COMBINER"));
		if (strcmp(temporal, "SI") == 0) {
			vg_combiner = ACEPTA_COMBINER;
		}
		if (strcmp(temporal, "NO") == 0) {
			vg_combiner = NO_ACEPTA_COMBINER;
		}
		free(temporal);
		vg_archivos = config_get_array_value(archivoConfig, "ARCHIVOS");
	}
	config_destroy(archivoConfig);
}

void testleerArchivoDeConfiguracion() {
	int i;
	printf(
			"*********************** Valores Seteados ***********************\n");
	printf("Path del Config de Jog:\t[%s]\n", vg_nombreArchivoConfigJob);
	printf("Puerto de Marta:\t[%d]\n", vg_puertoMarta);
	printf("Puerto de Nodo:\t[%d]\n", vg_PuertoNodo);
	printf("IP marta:\t\t[%s]\n", vg_ipMarta);
	printf("IP Nodo:\t\t[%s]\n", vg_ipNodo);
	printf("Acepta combiner:\t[%d]\n", vg_combiner);
	printf("Mapper path:\t\t[%s]\n", vg_mapperPath);
	printf("Reducer path:\t\t[%s]\n", vg_reducerPath);
	printf("Resultado:\t\t[%s]\n", vg_resultado);
	for (i = 0; vg_archivos[i] != '\0'; i++) {
		printf("Lista de archivos elemento [%d] Contenido: [%s]\n", i,
				vg_archivos[i]);
	}
	printf(
			"****************************** FIN ******************************\n");
}

void conectarConMarta() {
	vg_fdJob = crearSocket();
	conectarSocket(vg_fdJob, vg_ipMarta, vg_puertoMarta);
}

void sendTamanioDe(char* cadena) {
	int msgSize = strlen(cadena);
	char* cadenaMsgSize = malloc(sizeof(int));
	sprintf(cadenaMsgSize, "%d", msgSize);
	enviarPorSocket(vg_fdJob, cadenaMsgSize, sizeof(int));
	free(cadenaMsgSize);
}

void* indicarArchivosAMarta() {
	char msg[] = "3 Marta, tengo este archivo [ARCHIVO], que hago";

	conectarConMarta();
	sendTamanioDe(msg);

//	char bufer[200];
//	recibirPorSocket(fdJob,bufer,sizeof(bufer)); // Recibe los bloques a operar sus rutinas
//	printf("%s",bufer);

	cerrarSocket(vg_fdJob);

	return NULL;
}
