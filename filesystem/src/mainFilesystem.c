#include "filesystem.h"

int main() {
//	se escribe en pseudocodigo lo que se debe hacer para luego irlo programando
//crearFilesystem
//inicializar filesystem
//
//crear hilos, uno servidorAMartha y otro servidorANodos y hacer uso del join para que el hilo del main los espere
//
//servidorAMartha
//se encarga de las comunicaciones con Martha. debe ser un servidor que se conecta con un solo cliente
//dentro de un ciclo infinito -donde martha es quien se conecta.
//manejar los mensajes por socket
//1. mensaje de martha que pide ubicacion de archivos
//
//servidorANodos
//se encarga de las comunicaciones con los nodos, debe ser un hilo concurrente con select- donde se recibe
//una cantidad de nodos en el archivo de configuracion
//levantarConsola y en funcion de  lo que se va pidiendo se debe
//dentro de un ciclo infinito manejar mensajes por socket

return 0;
}
