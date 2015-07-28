#include "nodo.h"

void liberaMemoriaLista(t_list* lista, int* cantElementos,
		void (*funcionLiberaElemento)(void*)) {
	int posicion;
	for (posicion = 0; posicion <= *cantElementos; posicion++) {
		list_remove_and_destroy_element(lista, posicion, funcionLiberaElemento);
	}

}

void testleerArchivoDeConfiguracion() {
	printf(
			"*********************** Valores Seteados ***********************\n");
	printf("Puerto de Nodo:\t[%d]\n", vg_puerto_Nodo);
	printf("IP Nodo:\t\t[%s]\n", vg_ip_Nodo);
	printf("Puerto de FS:\t[%d]\n", vg_puerto_FS);
	printf("IP FS:\t\t[%s]\n", vg_ip_FS);
	printf("Puerto a JOb:\t[%d]\n", vg_puerto_job);

	printf("Archivo Bin:\t[%s]\n", vg_archivo_Bin);
	printf("Ruta archivos temp:\t\t[%s]\n", vg_dirTemp);
	printf("Nodo nuevo:\t\t[%d]\n", vg_nodo_Nuevo);

	printf(
			"****************************** FIN ******************************\n");
}

void recibir(int fdReceptor) {
	size_t tamanioMensaje;
	recibirPorSocket(fdReceptor, &tamanioMensaje, sizeof(int));
	void* buffer = malloc(tamanioMensaje);
	recibirPorSocket(fdReceptor, buffer, tamanioMensaje);
	Paquete* unPaquete = deserializar(buffer, tamanioMensaje); //primer deserializado

	interpretarPaquete(unPaquete, fdReceptor);

}

void interpretarPaquete(Paquete* unPaquete, int fdReceptor) {

	switch (unPaquete->tipoDeMensaje) {
	case (LECTURA): { //se debe previamente haber habierto el archivo bin del nodo
		// acceder al bloque del nodo y ese string es el que se manda de vuelta.
		//enviar();     // envia por socket el bloque al servidor
		break;
	}
		case(DESCONECTAR_NODO):{// quizas se deba poner en el nodo.h, --- verificar al hacer pull

          cerrarSocket(fdReceptor);
          vg_desconectar = 1;// para salir del while en el hilo para el clienteFS
		}

			break;
	}
}


