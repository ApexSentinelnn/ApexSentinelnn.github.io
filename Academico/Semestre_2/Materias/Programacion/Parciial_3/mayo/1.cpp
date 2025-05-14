#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>

FILE *file1;
FILE *file2;
FILE *file3;
FILE *file4;

void matricula(){
    printf("\n|==============================================|\n");
    printf("|         Matriculas de estudiantes            |\n");
    printf("|==============================================|\n");
    printf("| 187855 | Castillo Gaytan Noe                 |\n");
    printf("|==============================================|\n");
}

void archivo1(){
	char caracter;
	
	file1 = fopen("fgetc.txt","r");
	if (file1 == NULL){
		printf("\nEl archivo prueba no existe \n\n");
		exit(1);
	}
	
	printf("---------- USANDO FGETC ---------\n");
	printf("\nEl contenido del archivo de prueba es \n\n");
	
	while (feof(file1) == 0){
		caracter = fgetc(file1);
		printf("%c",caracter);
	}
	fclose(file1);
}
void archivo2(){
    char caracteres[100];

    file2 = fopen("fgets.txt","r");
	if (file2 == NULL){
		printf("\nEl archivo prueba no existe \n\n");
		exit(1);
	}
	
	printf("\n---------- USANDO FGETS ---------\n");
	printf("\nEl contenido del archivo de prueba es \n\n");
	
	while (feof(file2) == 0){
		fgets(caracteres,100,file2);
		printf("%s",caracteres);
	}
	fclose(file2);
}

void archivo3(){
	char buffer[100];

    file3 = fopen ( "fread.txt", "r+" );
	if (file3 == NULL){
		printf("\nEl archivo prueba no existe \n\n");
		exit(1);
	}
	
	printf("\n---------- USANDO FREAD ---------\n");
	printf("\nEl contenido del archivo de prueba es \n\n");
	fread ( buffer, sizeof ( char ), 100, file3 );
	printf("%s", buffer);
	fclose ( file3 );
}

void archivo4(){
    char pato[100];

    file4 = fopen ( "fscanf.txt", "r" );
	if (file4==NULL){ 
		printf("\nEl archivo prueba no existe \n\n");
		exit(1);
	}
	printf("\n---------- USANDO FSCANF ---------\n");
	printf("\nEl contenido del archivo de prueba es \n\n");
	fscanf(file4, " %[^\n]" ,pato);
	printf("%s", pato);
	fclose ( file4 );
}


void casos(){
        archivo1();
        archivo2();
        archivo3();
        archivo4();
}


int main(){
	matricula();
    casos();
	return 0;
}
