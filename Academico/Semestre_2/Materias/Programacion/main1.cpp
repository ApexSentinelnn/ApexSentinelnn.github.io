#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>

// Prototipos de las funciones
void llenarArreglos(int valores[], int datos, int matriz[][3], int a, int b);
void mostrarArreglos(const int valores[], int datos, const int matriz[][3], int a, int b);
void modificarArreglos(int valores[], int datos, int matriz[][3], int a, int b);

int main() {
    setlocale(LC_CTYPE, "Spanish");

    int ar_numeros[5];
    int Ar_bidi_Numeros[2][3];

    // Llenar los arreglos
    llenarArreglos(ar_numeros, 5, Ar_bidi_Numeros, 2, 3);

    // Mostrar los arreglos
    printf("\nContenido de los arreglos:\n");
    mostrarArreglos(ar_numeros, 5, Ar_bidi_Numeros, 2, 3);

    // Modificar los arreglos
    modificarArreglos(ar_numeros, 5, Ar_bidi_Numeros, 2, 3);

    // Mostrar los arreglos modificados
    printf("\nContenido de los arreglos después de la modificación:\n");
    mostrarArreglos(ar_numeros, 5, Ar_bidi_Numeros, 2, 3);

    printf("\n\nFIN DEL PROGRAMA\n");

    return 0;
}

// Función para llenar los arreglos
void llenarArreglos(int valores[], int datos, int matriz[][3], int a, int b) {
    int x, y;

    // Llenar el arreglo unidimensional con datos del usuario
    printf("\nIntroduzca %d números enteros para el arreglo unidimensional:\n", datos);
    for (x = 0; x < datos; ++x) {
        printf("Elemento [%d]: ", x);
        if (scanf("%d", &valores[x]) != 1) { // Validacion de entrada
            printf("Error: Entrada inválida. Por favor, ingrese un número entero.\n");
            exit(1); // Salir del programa en caso de error
        }
    }

    // Llenar el arreglo bidimensional con números aleatorios entre 50 y 80
    srand(time(NULL));
    for (x = 0; x < a; ++x) {
        for (y = 0; y < b; ++y) {
            matriz[x][y] = rand() % 31 + 50;
        }
    }
}

// Función para mostrar los arreglos
void mostrarArreglos(const int valores[], int datos, const int matriz[][3], int a, int b) {
    int x, y;

    // Mostrar el arreglo unidimensional
    printf("\nArreglo unidimensional:\n");
    for (x = 0; x < datos; ++x) {
        printf("%d\t", valores[x]);
    }
    printf("\n");

    // Mostrar el arreglo bidimensional
    printf("\nArreglo bidimensional:\n");
    for (x = 0; x < a; ++x) {
        for (y = 0; y < b; ++y) {
            printf("[%d][%d] = %d\t", x, y, matriz[x][y]);
        }
        printf("\n");
    }
}

// Función para modificar los arreglos
void modificarArreglos(int valores[], int datos, int matriz[][3], int a, int b) {
    int x, y;

    // Modificar el arreglo unidimensional
    for (x = 0; x < datos; ++x) {
        if (valores[x] % 3 == 0) {
            valores[x] *= 4;
        }
    }

    // Modificar el arreglo bidimensional
    for (x = 0; x < a; ++x) {
        for (y = 0; y < b; ++y) {
            if (matriz[x][y] % 2 != 0) {
                matriz[x][y] = 100;
            }
        }
    }
}
