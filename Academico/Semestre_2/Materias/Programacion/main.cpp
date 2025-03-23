#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

int main() {
    int opcion;
    char continuar;
    
    do {
        printf("****************************************\n");
        printf("*         Desarrollado por:            *\n");
        printf("*      Noe Castillo Gaytan             *\n");
        printf("*      Matricula: 187855               *\n");
        printf("****************************************\n\n");
        
        printf("Menu de opciones:\n");
        printf("1. Arreglo 2x5 con valores aleatorios\n");
        printf("2. Arreglo 5x3 con valores ingresados por el usuario\n");
        printf("3. Arreglo 3x4 predefinido con suma\n");
        printf("4. Arreglo ");
        printf("Seleccione un caso (1-3): ");
        cin >> opcion;
        
        switch (opcion) {
            case 1: {
                int arr[2][5];
                srand(time(0));
                
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
                int arr[3][4] = {{1, 2, 3, 8}, {4, 5, 6, 2}, {3, 1, 7, 1}};

            }
            default:
                printf("Opcion no valida\n");
        }
        
        printf("\nDesea continuar? (s/n): ");
        cin >> continuar;
        
    } while (continuar == 's' || continuar == 'S');
    
    return 0;
}
