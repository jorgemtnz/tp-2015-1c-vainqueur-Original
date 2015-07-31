#include "filesystem.h"



#include <sys/wait.h>


char *dame_md5(char *archivo){
	int fd[2];
	int pidHijo;
	char *resultado;
	pipe(fd);
	char result[1000];
	memset(result,'\0',1000);
	if ( (pidHijo = fork() ) == -1){
		fprintf(stderr, "Fallo el FORK");
	} else if( pidHijo == 0) {
		close(1);
		dup2(fd[1], 1);
		close(fd[0]);
		execlp("/usr/bin/md5sum","md5sum",archivo,NULL);
	}
	wait(NULL);
	read(fd[0], result, sizeof(result));
	printf("%s",result);
	resultado=malloc(sizeof(result));
	strcpy(resultado,result);
	return resultado;
}
