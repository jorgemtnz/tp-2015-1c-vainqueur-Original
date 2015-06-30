//#include "filesystemTest/filesystem.h"

//int main(int argc, char **argv) {
//	int i;
//	nod* nodo = malloc(sizeof(nod));
//	bloq* bloque0 = malloc(sizeof(bloq));
//	bloq* bloque1 = malloc(sizeof(bloq));
//	bloq* bloque2 = malloc(sizeof(bloq));
//	bloq* bloqueDisponible = malloc(sizeof(bloq));
//
//	nodo = NULL;
//	bloque0 = NULL;
//	bloque1 = NULL;
//	bloque2 = NULL;
//	bloqueDisponible = NULL;
//	nodo = crearNodo();
//	bloque0 = crearBloque();
//	bloque1 = crearBloque();
//	bloque2 = crearBloque();
//	bloque0->numero = 0;
//	bloque1->numero = 1;
//	bloque2->numero = 2;
//
//	printf("nodo, numero:  %d\n", nodo->numero);
//
//	list_add(nodo->listaBloques, bloque0);
//	list_add(nodo->listaBloques, bloque1);
//	list_add(nodo->listaBloques, bloque2);
//
//	for (i = 0; i < 3; i++) {
//		printf(
//				"se marca bloque ocupado al primer bloque disponible de la lista\n (1 para ocupado) \n");
//		bloqueDisponible = buscaBloqueDisponible(nodo);
//		printf("estado de bloque 0  :%d\n", bloque0->estaOcupado);
//		printf("estado de bloque 1  :%d\n", bloque1->estaOcupado);
//		printf("estado de bloque 2   :%d\n", bloque2->estaOcupado);
//		printf("bloqueDisponible es ahora el bloque : %d \n\n", bloqueDisponible->numero);
//	}
//
//	liberaMemoriaNodo(nodo);
//	return 0;
//}

