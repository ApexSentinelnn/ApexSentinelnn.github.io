#include <stdio.h>
#include <locale.h>

void Muestraarreglo_Uni(int valores[], int datos);
void Muestraarreglo_Bidi(int matriz[][3], int a, int b);

int main() {
    setlocale(LC_CTYPE, "Spanish");

    int ar_numeros[4];  // Declaración del arreglo unidimensional
    int ar_bidi_numeros[2][3]; // Declaración del arreglo bidimensional

    // Trabajo con arreglo unidimensional
    printf("Introduzca los 4 números enteros que se almacenarán en el arreglo UNI:\n");
    for (int x = 0; x < 4; x++) {
        printf("Valor para el elemento [%d]: ", x);
        scanf("%d", &ar_numeros[x]);
    }

    Muestraarreglo_Uni(ar_numeros, 4); // Llamado a la función llevando el arreglo unidimensional

    printf("\nEl arreglo después de la función:\n");
    for (int x = 0; x < 4; x++) {
        printf("%d ", ar_numeros[x]);
    }
    printf("\n");

    // Trabajo con arreglo bidimensional 2 x 3
    printf("\nIntroduzca los 6 números enteros que se almacenarán en el arreglo BIDIM:\n");
    for (int x = 0; x < 2; x++) {
        for (int y = 0; y < 3; y++) {
            printf("Valor para el elemento [%d][%d]: ", x, y);
            scanf("%d", &ar_bidi_numeros[x][y]);
        }
    }

    Muestraarreglo_Bidi(ar_bidi_numeros, 2, 3); // Llamado a la función llevando el arreglo bidimensional

    printf("\nFIN DEL PROGRAMA\n");

    return 0;
}

void Muestraarreglo_Uni(int valores[], int datos) {
    int i;
    for (i = 0; i < datos; i++) {
        valores[i] *= 2;
        printf("%d ", valores[i]);
    }
    printf("\n");
}

void Muestraarreglo_Bidi(int matriz[][3], int a, int b) {
    int x, y;
    for (x = 0; x < a; x++) {
        for (y = 0; y < b; y++) {
            matriz[x][y] *= 2;
            printf("Elemento [%d][%d] = %d ", x, y, matriz[x][y]);
        }
        printf("\n");
    }
}