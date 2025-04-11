#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TAM 10

int main() {
    srand(time(0)); // Inicializar la semilla para números aleatorios
    int arreglo[TAM], resultado[TAM / 2];
    int suma = 0, pares_principal = 0, impares_principal = 0;
    int pares_resultado = 0, impares_resultado = 0;
    int mayor = 0, posicion = 0;

    // Llenar el arreglo con números aleatorios del 1 al 10
    for (int i = 0; i < TAM; i++) {
        arreglo[i] = rand() % 10 + 1;
        suma += arreglo[i];
        if (arreglo[i] % 2 == 0) pares_principal++;
        else impares_principal++;
    }

    // Llenar el arreglo resultado
    for (int i = 0; i < TAM / 2; i++) {
        resultado[i] = arreglo[i] * arreglo[TAM - 1 - i];
        if (resultado[i] % 2 == 0) pares_resultado++;
        else impares_resultado++;
        if (resultado[i] > mayor) {
            mayor = resultado[i];
            posicion = i;
        }
    }

    // Mostrar los arreglos
    printf("Arreglo principal:\n");
    for (int i = 0; i < TAM; i++) {
        printf("%d ", arreglo[i]);
    }
    printf("\n");

    printf("Arreglo resultado:\n");
    for (int i = 0; i < TAM / 2; i++) {
        printf("%d ", resultado[i]);
    }
    printf("\n");

    // Mostrar estadísticas
    printf("\nPares e impares:\n");
    printf("Arreglo principal - Pares: %d Impares: %d\n", pares_principal, impares_principal);
    printf("Arreglo resultado - Pares: %d Impares: %d\n", pares_resultado, impares_resultado);
    printf("\nLa sumatoria del arreglo principal es: %d\n", suma);
    printf("El numero mayor del arreglo resultado es %d y se encuentra en la posicion %d\n", mayor, posicion);

    return 0;
}
