#include <stdio.h>
#include <string.h>

int main() {
    char var1[15] = "hola"; 
    char var2[15]= "Hola"; 
    int result = strcmp (var1, var2);
    
    printf("Ingresa una palabra: ");
    scanf("%14s", var2);

    
    printf("\nPalabra 1: %s\n", var1);
    printf("Palabra 2: %s\n", var2);

    
    strcpy(var2, var1);

    
    printf("\nLos texto en cada variable son:\n");
    printf("Palabra 1: %s\n", var1); ;
    printf("Palabra 2: %s\n", var2);

        printf("El resultado de de la comparacion = %d\n", result);
    
        if (strcmp(var1, var2)==0)
            printf("Palabras iguales\n");
        else 
            if (strcmp(var1, var2)== 1) 
            printf("\nLa primera palabra es mayor a la segunda\n");
            else 
            printf("\nLa primera palabra es menor a la segunda\n");

        if(strcmp(var1, var2)==0)
            printf("Palabras iguales\n");
        else 
            printf("\nPalabras diferentes\n");
        

    return 0;
}