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




