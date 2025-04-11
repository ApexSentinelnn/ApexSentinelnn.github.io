#include <stdio.h>
#include <string.h>
#include <iostream>

#define SIZE 5

// Función para comparar dos cadenas en orden ascendente
int compararAscendente(const void *a, const void *b) {
    return strcmp(*(const char **)a, *(const char **)b);
}

// Función para comparar dos cadenas en orden descendente
int compararDescendente(const void *a, const void *b) {
    return strcmp(*(const char **)b, *(const char **)a);
}

// Función para concatenar dos cadenas
void concatenarArreglos(char *destino, const char *a, const char *b) {
    strcpy(destino, a);
    strcat(destino, "-");
    strcat(destino, b);
}

int main() {
    char arreglo1[SIZE][100], arreglo2[SIZE][100], arreglo3[SIZE][100], arreglo4[SIZE * 2][100];
    char *ptrArreglo1[SIZE];
    char concatenado[200];

    // Solicitar 5 palabras al usuario
    printf("Ingresa 5 palabras:\n");
    for (int i = 0; i < SIZE; i++) {
        printf("Palabra %d: ", i + 1);
        scanf("%s", arreglo1[i]);
        ptrArreglo1[i] = arreglo1[i]; // Crear un arreglo de punteros para facilitar el ordenamiento
    }

    // Copiar palabras al arreglo2 y ordenarlas ascendentemente
    for (int i = 0; i < SIZE; i++) {
        strcpy(arreglo2[i], arreglo1[i]);
    }
    qsort(ptrArreglo1, SIZE, sizeof(char *), compararAscendente); // Ordenar arreglo1 de manera ascendente

    // Copiar palabras al arreglo3 y ordenarlas descendentemente
    for (int i = 0; i < SIZE; i++) {
        strcpy(arreglo3[i], arreglo1[i]);
    }
    qsort(ptrArreglo1, SIZE, sizeof(char *), compararDescendente); // Ordenar arreglo1 de manera descendente

    // Concatenar cada palabra de arreglo1 y arreglo2 en arreglo4
    int index = 0;
    for (int i = 0; i < SIZE; i++) {
        concatenarArreglos(concatenado, arreglo1[i], arreglo2[i]);
        strcpy(arreglo4[index++], concatenado);
    }

    // Mostrar los 4 arreglos
    printf("\nArreglo 1 (Palabras del usuario):\n");
    for (int i = 0; i < SIZE; i++) {
        printf("%s\n", arreglo1[i]);
    }

    printf("\nArreglo 2 (Ordenado ascendente):\n");
    for (int i = 0; i < SIZE; i++) {
        printf("%s\n", arreglo2[i]);
    }

    printf("\nArreglo 3 (Ordenado descendente):\n");
    for (int i = 0; i < SIZE; i++) {
        printf("%s\n", arreglo3[i]);
    }

    printf("\nArreglo 4 (Concatenado):\n");
    for (int i = 0; i < SIZE; i++) {
        printf("%s\n", arreglo4[i]);
    }

    return 0;
}

