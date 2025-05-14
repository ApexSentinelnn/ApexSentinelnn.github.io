#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
main ()
{
FILE *fp;
char caracter;
fp = fopen ( "fichero.txt", "w+" );
printf("\nIntroduce un texto al archivo: ");
while((caracter = getchar()) != '\n')
{
printf("%c", fputc(caracter, fp));
}
fclose ( fp );

FILE *file1;
file1 = fopen("fichero.txt","r");
if (file1 == NULL)
{ printf("\nEl archivo prueba no existe \n\n");
getch();
exit(1);
}
printf("\n\n---------- USANDO FGETC ---------\n");
printf("\nEl contenido del archivo de prueba es \n\n");
while (feof(file1) == 0)
{
caracter = fgetc(file1);
printf("%c",caracter);
}
//cerramos el archivo para liberar memoria
fclose(file1);

fp = fopen ( "fichero.txt", "w+" );
printf("\nIntroduce un texto al archivo: ");
while((caracter = getchar()) != '\n')
{
printf("%c", fputc(caracter, fp));
}

printf(" ");
printf("\n");
fclose ( fp );

file1;
file1 = fopen("fichero.txt","r");
if (file1 == NULL)
{ printf("\nEl archivo prueba no existe \n\n");
getch();
exit(1);
}
printf("\n\n---------- USANDO FGETC ---------\n");
printf("\nEl contenido del archivo de prueba es \n\n");
while (feof(file1) == 0)
{
caracter = fgetc(file1);
printf("%c",caracter);
}
//cerramos el archivo para liberar memoria
fclose(file1);

fp = fopen ( "fichero.txt", "w+" );
printf("\nIntroduce un texto al archivo: ");
while((caracter = getchar()) != '\n')
{
printf("%c", fputc(caracter, fp));
}

printf(" ");
printf("\n");
fclose ( fp );


//Lectura del archivo
return 0;
}
