#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>
#define p printf


// Prototipos de las funciones
void llenarArreglos(int valores[], int matriz[][3]);
void mostrarArreglos(const int valores[], const int matriz[][3]);
void modificarArreglos(int valores[], int matriz[][3]);

int main() {
    setlocale(LC_CTYPE, "Spanish");

    int ar_numeros[5];
    int Ar_bidi_Numeros[2][3];

    //Nombre y matricula
    p("******************************************\n");
    p("*          PROGRAMA DE CADENAS          *\n");
    p("******************************************\n");
    p("* NOMBRE   : Noe Castillo Gaytan        *\n");
    p("* MATRICULA: 187855                     *\n");
    p("******************************************\n\n");

    // Llenar los arreglos
    llenarArreglos(ar_numeros, Ar_bidi_Numeros);

    // Mostrar los arreglos
    p("\nContenido de los arreglos:\n");
    mostrarArreglos(ar_numeros, Ar_bidi_Numeros);

    // Modificar los arreglos
    modificarArreglos(ar_numeros, Ar_bidi_Numeros);

    // Mostrar los arreglos modificados
    p("\nContenido de los arreglos después de la modificacion:\n");
    mostrarArreglos(ar_numeros, Ar_bidi_Numeros);

    p("\n\nFIN DEL PROGRAMA\n");

    return 0;
}

// Función para llenar los arreglos
void llenarArreglos(int valores[], int matriz[][3]) {
    int x, y;

    // Llenar el arreglo unidimensional con datos del usuario
    p("\nIntroduzca 5 números enteros para el arreglo unidimensional:\n");
    for (x = 0; x < 5; ++x) {
        p("Elemento [%d]: ", x);
        if (scanf("%d", &valores[x]) != 1) { // Validacion de entrada
            p("Error: Entrada invalida. Por favor, ingrese un numero entero.\n");
            exit(1); // Salir del programa en caso de error
        }
    }

    // Llenar el arreglo bidimensional con números aleatorios entre 50 y 80
    srand(time(NULL));
    for (x = 0; x < 2; ++x) {
        for (y = 0; y < 3; ++y) {
            matriz[x][y] = rand() % 31 + 50;
        }
    }
}

// Función para mostrar los arreglos
void mostrarArreglos(const int valores[], const int matriz[][3]) {
    int x, y;

    // Mostrar el arreglo unidimensional
    p("\nArreglo unidimensional:\n");
    for (x = 0; x < 5; ++x) {
        p("%d\t", valores[x]);
    }
    p("\n");

    // Mostrar el arreglo bidimensional
    p("\nArreglo bidimensional:\n");
    for (x = 0; x < 2; ++x) {
        for (y = 0; y < 3; ++y) {
            p("[%d][%d] = %d\t", x, y, matriz[x][y]);
        }
        p("\n");
    }
}

// Función para modificar los arreglos
void modificarArreglos(int valores[], int matriz[][3]) {
    int x, y;

    // Modificar el arreglo unidimensional (multiplicar por 4 los múltiplos de 3)
    for (x = 0; x < 5; ++x) {
        if (valores[x] % 3 == 0) {
            valores[x] *= 4;
        }
    }

    // Modificar el arreglo bidimensional (cambiar impares por 100)
    for (x = 0; x < 2; ++x) {
        for (y = 0; y < 3; ++y) {
            if (matriz[x][y] % 2 != 0) {
                matriz[x][y] = 100;
            }
        }
    }
}