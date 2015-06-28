//LEEME aca se testea que agarre el archivo y luego lo divida en las oraciones o partes que terminan en \n y que
// forman el bloque
// lo subo comentado porque voy a ir haciendo varios testeos. para ponerlo a funcionar quita el comentario, y correlo.
//seleccionar el comentario  y ctrl + shift + 7 para quitar el comentario automaticamente.
//esta ok, pero si te da errores , reviza las configuraciones del run configuracion, para pthread, y las LD_LIBRARY_PATH

#include <stdio.h>
#include <stdlib.h>
#include <commons/log.h>
#include <commons/string.h>
#include <pthread.h>

//static void log_in_disk(char* temp_file) {
//    t_log* logger = log_create(temp_file, "TEST",true, LOG_LEVEL_INFO);
//
//    log_trace(logger, "LOG A NIVEL %s", "TRACE");
//    log_debug(logger, "LOG A NIVEL %s", "DEBUG");
//    log_info(logger, "LOG A NIVEL %s", "INFO");
//    log_warning(logger, "LOG A NIVEL %s", "WARNING");
//    log_error(logger, "LOG A NIVEL %s", "ERROR");
//
//    log_destroy(logger);
//}
//
//int main(int argc, char** argv) {
//    pthread_t th1, th2;
//
//    char* temp_file = "/tmp/log.txt";
//
//    if (temp_file != NULL) {
//        pthread_create(&th1, NULL, (void*) log_in_disk, temp_file);
//        pthread_create(&th2, NULL, (void*) log_in_disk, temp_file);
//
//        pthread_join(th1, NULL);
//        pthread_join(th2, NULL);
//        printf("\nRevisar el archivo de log que se creo en: %s\n", temp_file);
//    } else {
//        printf("No se pudo generar el archivo de log\n");
//    }
//
//
//    return (EXIT_SUCCESS);
//}
