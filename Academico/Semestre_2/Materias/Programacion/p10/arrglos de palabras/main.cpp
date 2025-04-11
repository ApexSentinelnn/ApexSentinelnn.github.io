#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//matricula
void matricula(){
    printf("****************************************\n");
    printf("* Desarrollado por: Noe Castillo Gaytan *\n");
    printf("* Matricula: 187855 *\n");
    printf("****************************************\n\n");
}

// ordenar un arreglo
void ordAsce(char arreglo[][50], int n) {
    char temp[50];
    for(int i = 0; i < n - 1; i++) {
        for(int j = i + 1; j < n; j++) {
            if(strcmp(arreglo[i], arreglo[j]) > 0) {
                strcpy(temp, arreglo[i]);
                strcpy(arreglo[i], arreglo[j]);
                strcpy(arreglo[j], temp);
            }
        }
    }
}

// ordenar un arreglo en orden descendente
void ordDes(char arreglo[][50], int n) {
    char temp[50];
    for(int i = 0; i < n - 1; i++) {
        for(int j = i + 1; j < n; j++) {
            if(strcmp(arreglo[i], arreglo[j]) < 0) {
                strcpy(temp, arreglo[i]);
                strcpy(arreglo[i], arreglo[j]);
                strcpy(arreglo[j], temp);
            }
        }
    }
}

// concatenar dos arreglos
void concatArr(char arreglo1[][50], char arreglo2[][50], char arreglo4[][100], int n) {
    for(int i = 0; i < n; i++) {
        strcpy(arreglo4[i], arreglo1[i]);
        strcat(arreglo4[i], "-");
        strcat(arreglo4[i], arreglo2[i]);
    }
}

//mostrar
void mostrar(){
    char arreglo1[5][50]; 
    char arreglo2[5][50]; 
    char arreglo3[5][50]; 
    char arreglo4[5][100]; 
    // 5. Mostrar los 4 arreglos
    printf("\nArreglo 1 (Palabras del usuario)\tArreglo 2 (Ordenado ascendente)\tArreglo 3 (Ordenado descendente)\tArreglo 4 (Concatenado)\n");
    printf("------------------------------\t------------------------------\t------------------------------\t------------------------------\n");
        
    for(int i = 0; i < 5; i++) {
        printf("%-30s\t%-30s\t%-30s\t%-30s\n", arreglo1[i], arreglo2[i], arreglo3[i], arreglo4[i]);
    }
}

int main() {
    char arreglo1[5][50]; 
    char arreglo2[5][50]; 
    char arreglo3[5][50]; 
    char arreglo4[5][100]; 

    matricula();
    
    // 1. Solicitar al usuario 5 palabras
    printf("Ingrese 5 palabras:\n");
    for(int i = 0; i < 5; i++) {
        printf("Palabra %d: ", i+1);
        scanf("%s", arreglo1[i]);
    }
    
    // 2. Copiar palabras al segundo arreglo para ordenar ascendente
    for(int i = 0; i < 5; i++) {
        strcpy(arreglo2[i], arreglo1[i]);
    }
    ordAsce(arreglo2, 5);
    
    // 3. Copiar palabras al tercer arreglo para ordenar descendente
    for(int i = 0; i < 5; i++) {
        strcpy(arreglo3[i], arreglo1[i]);
    }
    ordDes(arreglo3, 5);
    
    // 4. Concatenar arreglo1 y arreglo3
    concatArr(arreglo1, arreglo3, arreglo4, 5);
    
    mostrar();
    
    return 0;
}