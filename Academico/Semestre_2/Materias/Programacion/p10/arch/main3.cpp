#include <stdio.h>
#include <string.h>
#include <stdlib.h>


// Ordenar un arreglo en orden ascendente
void ordAsc(char arr[][50], int cant) {
    char temp[50];
    for(int i = 0; i < cant - 1; i++) {
        for(int j = i + 1; j < cant; j++) {
            if(strcmp(arr[i], arr[j]) > 0) {
                strcpy(temp, arr[i]);
                strcpy(arr[i], arr[j]);
                strcpy(arr[j], temp);
            }
        }
    }
}

// Ordenar un arreglo en orden descendente
void ordDes(char arr[][50], int cant) {
    char temp[50];
    for(int i = 0; i < cant - 1; i++) {
        for(int j = i + 1; j < cant; j++) {
            if(strcmp(arr[i], arr[j]) < 0) {
                strcpy(temp, arr[i]);
                strcpy(arr[i], arr[j]);
                strcpy(arr[j], temp);
            }
        }
    }
}

// Concatenar dos arreglos
void conArr(char arr1[][50], char arr2[][50], char res[][100], int cant) {
    for(int i = 0; i < cant; i++) {
        strcpy(res[i], arr1[i]);
        strcat(res[i], "-");
        strcat(res[i], arr2[i]);
    }
}

void mostrarres(){
	//Mostrar los arreglos
	char arrUser[5][50]; 
    char arrAsc[5][50]; 
    char arrDes[5][50]; 
    char arrCon[5][100]; 
    printf("\nPalabras del usuario\tOrdenado ascendente\tOrdenado descendente\tConcatenado\n");
    printf("------------------------------\t------------------------------\t------------------------------\t------------------------------\n");
    
    for(int i = 0; i < 5; i++) {
        printf("%-30s\t%-30s\t%-30s\t%-30s\n", arrUser[i], arrAsc[i], arrDes[i], arrCon[i]);
    }
}

int main() {
    char arrUser[5][50]; 
    char arrAsc[5][50]; 
    char arrDes[5][50]; 
    char arrCon[5][100]; 

    printf("* Desarrollado por:  *\n");
    printf("* Matricula:  *\n");
    
    //Solicitar al usuario 5 palabras
    printf("Ingrese 5 palabras:\n");
    for(int i = 0; i < 5; i++) {
        printf("Palabra %d: ", i+1);
        scanf("%s", arrUser[i]);
    }
    
    //Copiar palabras al segundo arreglo
    for(int i = 0; i < 5; i++) {
        strcpy(arrAsc[i], arrUser[i]);
    }
    ordAsc(arrAsc, 5);
    
    //Copiar palabras al tercer arreglo
    for(int i = 0; i < 5; i++) {
        strcpy(arrDes[i], arrUser[i]);
    }
    ordDes(arrDes, 5);
    
    //Concatenar
    conArr(arrUser, arrDes, arrCon, 5);
    
	mostrarres();
    
    return 0;
}

