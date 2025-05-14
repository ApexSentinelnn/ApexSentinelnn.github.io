#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
main()
{
FILE *archivo;
char caracter;
archivo = fopen("prueba.txt","r");
if (archivo == NULL)
{ printf("\nEl archivo prueba no existe \n\n");
getch();
exit(1);
}
printf("\nEl contenido del archivo de prueba es \n\n");
while (feof(archivo) == 0)
{
caracter = fgetc(archivo);
printf("%c",caracter);
}
//cerramos el archivo para liberar memoria
fclose(archivo);
return 0;
}
