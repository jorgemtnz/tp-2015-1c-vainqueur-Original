#include <stdio.h>
#include <string.h>
#include <commons/commons.h>
#include <filesystem.h>
#include <marta.h>
#include <job.h>
#include <nodo.h>

void * retornarEstructura(buffer){

char* protocolo = NULL;
size_t tamano_buffer;

tamano_buffer = strlen(buffer);

//Tamaño máximo del array que se puede obtener.
char* bufferSerializado[tamano_buffer];


 bufferSerializado = string_split( buffer,SEPARADOR);
 
 
 // Obtengo el Header
 protocolo = string_substring_from(char * buffer, UN_BYTE);
 
 // convierto el protocolo a int
 (int)(*(protocolo));
 
 CASE (protocolo){

      ARCHIVO_CARGA_INICIAL:
      
      t_archivo archivo;
      
      // Es un archivo, por lo tanto la estructura que contiene el payload es t_archivo
      archivo.contenido = string_substring(char* buffer, 2, tamano_buffer);
      
      ESCRITURA_BLOQUE:
      
      
      
      INFORMAR_UBICACION_ARCHIVOS:
      
      
      
      SOLICITUD_JOB:
      
      
      
      RTA_SOLICITUD_JOB:
      
      
      
      NOTIFICACION_RESUL:
      
      
      
      EJECUTAR_MAP:
      
      
      
      EJECUTAR_RED:
      
      
      
      SOLICITUD_ARCHIVO:
      
      
      
      RTA_SOLICITUD_ARCHIVO:

 
 }
 
 }
