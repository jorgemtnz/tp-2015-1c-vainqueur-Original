int tamanio_archivo(int);   //da el tamaño del archivo en tamaño de pagina(es un tamaño para memoria)
int abreArchivo(char*);  // abre un archivo, se le manda la ruta del archivo
char* mapeaAMemoria(int , int ,char* ); //hace el mmap, recibe el tamaño pagina, ptr archivoAbierto, ptr DirArchivo
void imprimeMapeo(int , char* );  //imprime lo que esta mapeado a memoria, para lo que recibe el tamaño de pagina y el ptr a lo mapeado.
void desMapea(int , char* ); // desmapea la memoria recibe tamaño pagina, ptr a lo mapeado
void cierraArchivo(int );  // cierra archivo recibe el ptr Archivo abierto
