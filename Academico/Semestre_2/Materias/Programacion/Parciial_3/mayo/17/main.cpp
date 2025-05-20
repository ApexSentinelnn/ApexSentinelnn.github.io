//187855 Noe Castillo Gaytan.
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
void llenarArreglo(int* arreglo, int n) {
    for (int i = 0; i < n; ++i) {
        arreglo[i] = 10 + rand() % 41;  // Numeros entre 10 y 50
    }
}
void mostrarArreglo(const int* arreglo, int n) {
    for (int i = 0; i < n; ++i) {
        printf("%d ", arreglo[i]);
    }
    printf("\n");
}
int* obtenerMultiplosDe4(const int* arreglo, int n, int* tam2) {
    int* multiplos = (int*)malloc(n * sizeof(int));
    int contador = 0;
    for (int i = 0; i < n; ++i) {
        if (arreglo[i] % 4 == 0) {
            multiplos[contador++] = arreglo[i];
        }
    }
    *tam2 = contador;
    return (int*)realloc(multiplos, contador * sizeof(int));
}
int* obtenerArregloProducto(const int* arreglo1, int n1, const int* arreglo2, int n2) {
    int* producto = (int*)malloc(n1 * sizeof(int));
    int elemento4 = (n2 >= 4) ? arreglo2[3] : (n2 > 0 ? arreglo2[0] : 1);
    for (int i = 0; i < n1; ++i) {
        producto[i] = arreglo1[i] * elemento4;
    }
    return producto;
}

int main() {
    int n;
    printf("Ingrese el tamano del arreglo: ");
    scanf("%d", &n);

    srand(time(0));

    int* arreglo1 = (int*)malloc(n * sizeof(int));
    llenarArreglo(arreglo1, n);

    // Mostrar el primer arreglo
    printf("\nArreglo 1: ");
    mostrarArreglo(arreglo1, n);

    // Obtener el segundo arreglo (multiplos de 4)
    int tam2;
    int* arreglo2 = obtenerMultiplosDe4(arreglo1, n, &tam2);
    printf("\nArreglo 2 (multiplos de 4): ");
    mostrarArreglo(arreglo2, tam2);

    // Obtener el tercer arreglo (producto)
    int* arreglo3 = obtenerArregloProducto(arreglo1, n, arreglo2, tam2);
    printf("\nArreglo 3 (producto): ");
    mostrarArreglo(arreglo3, n);

    // Liberar memoria
    free(arreglo1);
    free(arreglo2);
    free(arreglo3);
    return 0;
}
