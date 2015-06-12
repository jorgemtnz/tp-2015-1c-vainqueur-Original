#include "filesystem.h"

/*------------------FUNCIONES CONSTRUCTORAS----------------------*/
nod* crearNodo() {
	nod* nodo      = malloc(sizeof(nod));
	nodo -> numero = 0;
	nodo -> estado = OPERATIVO;
	nodo -> listaBloques = list_create();
	strcpy(nodo -> dirEspacioNodo , UBICACIONNODO);
	return nodo;
}

bloq* crearBloque() { //constructor del bloque
	bloq* bloque      = malloc(sizeof(bloq));
	bloque -> numero  = 0;
	bloque -> tamanio = VEINTEMEGAS; //20 mb
	return bloque;
}

element* crearElemento() { //crea un elemento generico para despues configurarlo como archivo o carpeta
	element* elemento = malloc(sizeof(element)); //liberamos espacio para el elemnto
	elemento -> directorioPadre = 0;
	if(list_is_empty(FILESYSTEM -> listaElementos)){
		elemento -> index = 0;
	}
	else{
		elemento -> index += 1;
	}
	elemento -> estado = DISPONIBLE;
	elemento -> listaNodoBloque = '\0';
	elemento -> nombre[25] = '\0';
	elemento -> tamanio = 0; // Si es directorio siempre pesa 0. Si es archivo va a engordar
	return elemento;
}

void crearFileSystem() {
	fs* filesystem = malloc(sizeof(fs));
	filesystem -> estado = OPERATIVO;
	FILESYSTEM = filesystem; // Modifica variable global
}

void inicializarFilesystem(){		// Se inicializa cuando se formatea
		FILESYSTEM -> estado = DISPONIBLE;
		FILESYSTEM -> listaNodosConectados = list_create();
		FILESYSTEM -> listaElementos = list_create();
		FILESYSTEM -> espacioDisponible = 0;
}

/*-----------------------------------------------------------------------*/




/*------------------------FUNCIONES DESTRUCTORAS-------------------------*/
void liberaMemoriaBloque(bloq* bloque) { //libera memoria del tipo bloque
	free(&bloque -> numero);
	free(&bloque -> tamanio);
	free(bloque);
}

void liberaMemoriaNodo(nod* nodo) { //libera la memoria del nodo
	int i = 0;

	free(&nodo->estado);fs* inicializarFs(int fdArchConfig) {

		return FILESYSTEM;
	}
	free(&nodo->numero);
	free(&nodo->dirEspacioNodo);
	for (; i <= nodo->listaBloques->elements_count; i++) { //libero memoria de los bloques
		list_destroy_and_destroy_elements(nodo->listaBloques,
				(void*) liberaMemoriaBloque); //consultar porque no agarra el index
	}
	free(nodo);
}

void liberaNodoBloque(nodBloq* nodoBloque) {
	free(&(nodoBloque->numeroBloque));
	free(&(nodoBloque->numeroCopia));
	free(&(nodoBloque->numeroNodo));
	free(nodoBloque);
}


void liberaMemoriaElement(element* elemento) {
	int i = 0;
	free(&(elemento->directorioPadre));
	free(&(elemento->tipoElemento));
	free(&(elemento->estado));
	free(&(elemento->index));
	free(&(elemento->nombre));
	free(&(elemento->tamanio));
	for (; i <= elemento->listaNodoBloque->elements_count; i++) { //libero memoria de los Nodobloques
		list_destroy_and_destroy_elements(elemento->listaNodoBloque, (void*)liberaNodoBloque);
	}  //consultar el uso de list_destroy que no esta recibiendo el index i
	free(elemento);
}

void liberaMemoriaFS(){
	int i=0;
	free(&FILESYSTEM->espacioDisponible);
	free(&FILESYSTEM->estado);
	for (; i <= FILESYSTEM->listaNodosConectados->elements_count; i++) { //libero memoria de los Nodobloques
			list_destroy_and_destroy_elements(FILESYSTEM->listaNodosConectados, (void*)liberaMemoriaNodo);
		}  //consultar el uso de list_destroy que no esta recibiendo el index i

	for (; i <= FILESYSTEM->listaElementos->elements_count; i++) { //libero memoria de los Nodobloques
			list_destroy_and_destroy_elements(FILESYSTEM->listaElementos, (void*)liberaMemoriaElement);
		} //consultar el uso de list_destroy que no esta recibiendo el index i
	free(FILESYSTEM);
}

/*-----------------------------------------------------------------------*/





/*------------------------FUNCIONES AUXILIARES---------------------------*/
void cargarBloques(t_list *listaBloques) {
	int i = 0;
	for (; i <= NUMEROBLOQUES; i++) { //ciclo de for para cargar los 102 bloques
		bloq* bloque;  //varaible para almacenar el bloque creado
		bloque = crearBloque();  //crea el bloque
		list_add(listaBloques, bloque);  //lo agrega a la lista
	}
}

void leerRegistro(int arch) {
	read(arch, FILESYSTEM, sizeof(fs)); //lee el archivo y pone la estructura en la estructura fs
}

void mostrarElementos(){
	int elementosEnLista = FILESYSTEM -> listaElementos -> elements_count;
	int i;
	for(i=0; i <= elementosEnLista ; i++){
		element* elementoi;
		elementoi = list_get(FILESYSTEM -> listaElementos, i);
		printf("Index:%d Elemento:%s\n",elementoi -> index, elementoi -> nombre);
	}
}

void guardarRegistro(int arch) { //esto mientras este el archivo abierto sino lo abrimos aca

	write(arch, FILESYSTEM, sizeof(fs)); //le paso el registro fileSystem,y el archivo y lo escribe
}

/*----------------------------------------------------------------------*/






/*------------------- CONSOLA------------------------*/
//	    "formatearMDFS", "eliminarArchivo", "renombrarArchivo",
//		"moverArchivos",				    // Archivos
//		"crearDirectorio", "eliminarDirectorio", "renombrarDirectorio",
//		"moverDirectorio",      // Directorios
//		"copiarArchivoLocalAlMDFS", "copiarArchivoDelMDFSAlFSLocal",
//		"solicitarMD5deUnArchivoenMDFS", "verBloque", "borrarBloque",
//		"copiarBloque",										          // Bloques
//		"agregarNodo", "eliminarNodo",								// Nodos
//		"mostrarComandos"


void levantarConsola() {
	char comando[50];
	int idFunc;

	mostrarFunciones();

	while (1) {

		printf("Ingrese un comando >> ");
		fgets(comando, 50, stdin);

		idFunc = idFuncion(comando);
		aplicarFuncion(idFunc);
	}
}

void agregarN(char* nombre) { //FALTA VER EL TEMA DE SOCKETS
	nod* nodo;
	nodo = crearNodo(nombre); //se usa el constructor para crear el nodo
	list_add(FILESYSTEM->listaNodosConectados, nodo); //agrega al nodo a la lista de nodos del FS
//agregarDir(fileSystem->listaDirectorios,nodo->nombre);//se agrega un dir con el nombre del nodo[EN PROCESO]-quizas no se haría

}

void eliminarN(char* nombre) { //faltaria la condicion pero nose como ponerla
//list_remove_by_condition(FILESYSTEM->listaNodos), condicion(nombre) );//remueve de la lista el nodo que concuerda con el nombre ingresado eso creo
}

void formatearMDFS(int fdArchConfig) { //recive una entidad FS , libera su memoria y despues la crea devuelta, habia que ver sino inicilizarla[EN PROCESO TODAVIA LE FALTA]
	liberaMemoriaFS();
	inicializarFilesystem();
}

void crearDirectorio() {
	element* carpeta;
	int dirPadre;
	char* nombre;

	printf("Ingrese el nombre de la carpeta: ");
	scanf("%s",nombre);


	printf("Ingrese directorio del padre: ");
	scanf("%d",&dirPadre);

	if(dirPadre < 0){
		perror("Numero invalido de directorio padre\n");
		exit(-1);
	}

	carpeta = crearElemento();
	strcpy(carpeta -> nombre , nombre);
	carpeta -> directorioPadre = dirPadre;
	list_add(FILESYSTEM->listaElementos, carpeta);
}


void mostrarFunciones() {
	int contador = 0;
	do {
		contador += 1;
		printf("*------------------------------------------*\n");
		printf("COMANDO 	= %s\n", funciones[contador]);
		printf("DESCRIPCION = %s\n", descripciones[contador]);
		printf("*------------------------------------------*\n");
	} while (contador <= NUMEROFUNCIONESCONSOLA);
}

int idFuncion(char* funcion) {
	int i;
	for (i = 0;
			(i < NUMEROFUNCIONESCONSOLA) && (strcmp(funcion, funciones[i]) != 0);
			i++)
		;
	return (i <= NUMEROFUNCIONESCONSOLA - 1) ? (i + 1) : -1;
}


void aplicarFuncion(int idFuncion) { //selecciona un case en base al numero que llevaba el contador y aplica la funcion recibe el dir
	switch (idFuncion) {

	case FORMATEAR_MDFS:
		printf(
				"Esta es la funcion formatear \n y el directorio ingresado es = %s \n"); //no todas las funciones usan el dir pero yo lo puse por las dudas
		break;

	case ELIMINAR_ARCHIVO:
		printf(
				"Esta es la funcion eliminar \n y el directorio ingresado es = %s \n");
		break;
	case RENOMBRAR_ARCHIVO:
		printf(
				"Esta es la funcion renombrar \n y el directorio ingresado es = %s \n");
		break;
	case MOVER_ARCHIVOS:
		printf(
				"Esta es la funcion mover \n y el directorio ingresado es = %s \n");
		break;
	case CREAR_DIRECTORIO:
		printf(
				"Esta es la funcion crearD \n y el directorio ingresado es = %s \n");
		break;
	case ELIMINAR_DIRECTORIO:
		printf(
				"Esta es la funcion eliminarD \n y el directorio ingresado es = %s \n");
		break;
	case RENOMBRAR_DIRECTORIO:
		printf(
				"Esta es la funcion renombrarD \n y el directorio ingresado es = %s \n");
		break;
	case MOVER_DIRECTORIO:
		printf(
				"Esta es la funcion moverD \n y el directorio ingresado es = %s \n");
		break;
	case COPIAR_ARCHIVO_LOCAL_AL_MDFS:
		printf(
				"Esta es la funcion copiar \n y el directorio ingresado es = %s \n");
		break;
	case COPIAR_ARCHIVO_DEL_MDFS_AL_FS_LOCAL:
		printf(
				"Esta es la funcion copiarFSL \n y el directorio ingresado es = %s \n");
		break;
	case SOLICITAR_MD5_DE_UN_ARCHIVO_EN_MDFS:
		printf(
				"Esta es la funcion md5 \n y el directorio ingresado es = %s \n");
		break;
	case VER_BLOQUE:
		printf(
				"Esta es la funcion verB \n y el directorio ingresado es = %s \n");
		break;
	case BORRAR_BLOQUE:
		printf(
				"Esta es la funcion borrarB \n y el directorio ingresado es = %s \n");
		break;
	case COPIAR_BLOQUE:
		printf(
				"Esta es la funcion copiarB \n y el directorio ingresado es = %s \n");
		break;
	case AGREGAR_NODO:
		printf(
				"Esta es la funcion agregarN \n y el directorio ingresado es = %s \n");
		break;

	case ELIMINAR_NODO:
		printf(
				"Esta es la funcion eliminarN \n y el directorio ingresado es = %s \n");
		break;

	case MOSTRAR_COMANDOS:
		mostrarFunciones();
		break;

	case -1:
		printf("--Ojo ese comando no existe!! proba con mostrarComandos\n");
		break;
	}

}



