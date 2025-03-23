#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

int main() {
    int opcion;
    char continuar;
    srand(time(0));

    do {
        printf("****************************************\n");
        printf("* Desarrollado por: Noe Castillo Gaytan *\n");
        printf("* Matricula: 187855 *\n");
        printf("****************************************\n\n");

        printf("Menu de opciones:\n");
        printf("1. Arreglo 2x5 con valores aleatorios\n");
        printf("2. Arreglo 5x3 con valores ingresados por el usuario\n");
        printf("3. Arreglo 3x4 predefinido con suma\n");
        printf("4. Suma de dos matrices 3x5\n");
        printf("5. Matriz 6x2 con suma de filas y columnas\n");
        printf("6. Multiplicacion de matriz 4x2 por vector\n");
        printf("7. Contar repeticiones de valores en matriz 3x5\n");
        printf("8. Salir\n");
        printf("Seleccione un caso (1-8): ");
        cin >> opcion;

        switch (opcion) {
            case 1: {
                int arr[2][5];
                for (int i = 0; i < 2; i++) {
                    for (int j = 0; j < 5; j++) {
                        arr[i][j] = 8 + rand() % 13;
                    }
                }
                printf("Caso 1: Arreglo 2x5 con valores aleatorios\n");
                for (int i = 0; i < 2; i++) {
                    for (int j = 0; j < 5; j++) {
                        printf("%d ", arr[i][j]);
                    }
                    printf("\n");
                }
                break;
            }
            case 2: {
                int arr[5][3];
                printf("Ingrese 15 valores para un arreglo 5x3:\n");
                for (int i = 0; i < 5; i++) {
                    for (int j = 0; j < 3; j++) {
                        cin >> arr[i][j];
                    }
                }
                printf("Caso 2: Arreglo en orden inverso\n");
                for (int i = 4; i >= 0; i--) {
                    for (int j = 2; j >= 0; j--) {
                        printf("%d ", arr[i][j]);
                    }
                    printf("\n");
                }
                break;
            }
            case 3: {
                int arr[3][4] = {{1, 2, 3, 8}, {4, 5, 6, 2}, {3, 1, 7, 1}};
                int suma = 0;
                for (int i = 0; i < 3; i++) {
                    for (int j = 0; j < 4; j++) {
                        suma += arr[i][j];
                    }
                }
                printf("Caso 3: Arreglo predefinido y suma\n");
                for (int i = 0; i < 3; i++) {
                    for (int j = 0; j < 4; j++) {
                        printf("%d ", arr[i][j]);
                    }
                    printf("\n");
                }
                printf("Suma = %d\n", suma);
                break;
            }
            case 4: {
                int a[3][5], b[3][5], c[3][5];
                for (int i = 0; i < 3; i++) {
                    for (int j = 0; j < 5; j++) {
                        a[i][j] = 1 + rand() % 15;
                        b[i][j] = 1 + rand() % 15;
                        c[i][j] = a[i][j] + b[i][j];
                    }
                }
                printf("Caso 4: Suma de dos matrices\n");
                for (int i = 0; i < 3; i++) {
                    for (int j = 0; j < 5; j++) {
                        printf("%d ", c[i][j]);
                    }
                    printf("\n");
                }
                break;
            }
            case 5: {
                int arr[6][2], sumFilas[6] = {0}, sumColumnas[2] = {0};
                for (int i = 0; i < 6; i++) {
                    for (int j = 0; j < 2; j++) {
                        arr[i][j] = 1 + rand() % 10;
                        sumFilas[i] += arr[i][j];
                        sumColumnas[j] += arr[i][j];
                    }
                }
                printf("Caso 5: Matriz y suma de filas y columnas\n");
                for (int i = 0; i < 6; i++) {
                    for (int j = 0; j < 2; j++) {
                        printf("%d ", arr[i][j]);
                    }
                    printf("| %d\n", sumFilas[i]);
                }
                printf("----------------\n");
                printf("%d %d\n", sumColumnas[0], sumColumnas[1]);
                break;
            }
            case 6: {
                int matriz[4][2], vector[2] = {2, 3}, resultado[4] = {0};
                for (int i = 0; i < 4; i++) {
                    for (int j = 0; j < 2; j++) {
                        matriz[i][j] = 11 + rand() % 10;
                        resultado[i] += matriz[i][j] * vector[j];
                    }
                }
                printf("Caso 6: Multiplicacion de matriz por vector\n");
                for (int i = 0; i < 4; i++) {
                    printf("%d\n", resultado[i]);
                }
                break;
            }
            case 7: {
                int matriz[3][5], conteo[11] = {0};
                for (int i = 0; i < 3; i++) {
                    for (int j = 0; j < 5; j++) {
                        matriz[i][j] = 1 + rand() % 10;
                        conteo[matriz[i][j]]++;
                    }
                }
                printf("Caso 7: Repeticiones de valores\n");
                for (int i = 1; i <= 10; i++) {
                    printf("Numero %d: %d veces\n", i, conteo[i]);
                }
                break;
            }
            case 8:
                printf("Saliendo...\n");
                return 0;
            default:
                printf("Opcion no valida\n");
        }
    } while (true);
    return 0;
}
