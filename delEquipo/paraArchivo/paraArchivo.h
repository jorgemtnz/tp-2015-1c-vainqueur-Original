/*
 * paraArchivo.h
 *
 *  Created on: 31/7/2015
 *      Author: utnso
 */




#ifndef PARAARCHIVO_H_
#define PARAARCHIVO_H_

#include <stdbool.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <src/commons/string.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <stdlib.h>

#define handle_error(msj) \
	do{perror(msj);exit(EXIT_FAILURE);} while(0)

bool file_exists(const char* filename);
void free_null(void* data);
char* file_combine(char* f1, char* f2);
int file_get_size(char* filename);
void* file_get_mapped(char* filename);
void file_mmap_free(void* mapped, char* filename);



#endif


