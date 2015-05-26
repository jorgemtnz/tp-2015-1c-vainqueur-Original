#include <stdio.h>

void crearArchivo(char* nombreArchivo)
{
	int a,b;
	char letra;
	FILE* archivo;
	archivo = fopen (nombreArchivo,"w+");
	for(a = 0;a<50;a++)
	{
		for(b = 0;b<4000000;b++)
		{
			letra = rand() % 'z';
			if (letra < 'A')
			{
				letra ='a';
			}

			fwrite(&letra , sizeof(letra),sizeof(letra),archivo);
		}
		printf("Creado Renglon %d \n",a+1);
	}
	fclose(archivo);
}

int uno()
{
	return 1;
}

