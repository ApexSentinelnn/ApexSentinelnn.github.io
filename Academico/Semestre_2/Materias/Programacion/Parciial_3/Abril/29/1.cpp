#include <stdio.h>
#include <string.h>

struct datos
{
    char nombre[50];
    int edad_a;
    char categoria[20];
    int edad_m;
}datos_p;

int main()
{
    printf("\n|==============================================|\n");
    printf("|         Matriculas de estudiantes            |\n");
    printf("|==============================================|\n");
    printf("| 187855 | Castillo Gaytan Noe                 |\n");
    printf("|==============================================|\n");
    
    printf("Dame el nombre del narrador: ");
    scanf("%s", datos_p.nombre);
    printf("\nIngrese la edad del narrador: ");
    scanf("%d", &datos_p.edad_a);

    if (datos_p.edad_a<=18)
        strcpy(datos_p.categoria,"juvenil");
    else
        strcpy(datos_p.categoria,"veterano");
    
    datos_p.edad_m = (datos_p.edad_a * 12);

    printf("\nEl narrador %s tiene %d meses o %d anios de edad y es de categoria %s",datos_p.nombre,datos_p.edad_m, datos_p.edad_a,datos_p.categoria);

    return 0;
}

