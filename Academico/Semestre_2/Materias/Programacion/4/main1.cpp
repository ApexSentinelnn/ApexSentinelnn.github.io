#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int calcularProducto(int num1, int num2, int num3);
int calcularSumaCuadrados();
void contarMultiplos();
void calcularPromedio(int inicio, int fin);

int main() {
    int opcion;
    srand(time(NULL));

    do {
        printf("------------------------------------------\n");
        printf("Noe Castillo Gaytan.\n");
        printf("------------------------------------------\n");
        printf("\nMenu de operaciones:\n");
        printf("1. Calcular producto de tres valores aleatorios\n");
        printf("2. Calcular suma de cuadrados\n");
        printf("3. Contar multiplos de 3, 5 y 7\n");
        printf("4. Calcular promedio de numeros entre dos valores\n");
        printf("5. Salir\n");
        printf("Escoge una opcion: ");
        scanf("%d", &opcion);

        switch(opcion) {
            case 1: {
                int valor1 = rand() % 10 + 1;
                int valor2 = rand() % 10 + 1;
                int valor3 = rand() % 10 + 1;
                printf("El producto de %d, %d y %d es: %d\n", valor1, valor2, valor3, calcularProducto(valor1, valor2, valor3));
                break;
            }
            case 2:
                printf("La suma de los cuadrados es: %d\n", calcularSumaCuadrados());
                break;
            case 3:
                contarMultiplos();
                break;
            case 4: {
                int inicio, fin;
                do {
                    printf("Ingrese el valor de inicio (menor que fin): ");
                    scanf("%d", &inicio);
                    printf("Ingrese el valor de fin: ");
                    scanf("%d", &fin);
                    if (inicio >= fin) {
                        printf("El valor de inicio debe ser menor que fin. Intente nuevamente.\n");
                    }
                } while (inicio >= fin);
                calcularPromedio(inicio, fin);
                break;
            }
            case 5:
                printf("Saliendo del programa...\n");
                break;
            default:
                printf("Opcion no valida. Intente de nuevo.\n");
        }
    } while(opcion != 5);
   
    return 0;
}

int calcularProducto(int num1, int num2, int num3) {
    return num1 * num2 * num3;
}

int calcularSumaCuadrados() {
    int numero1, numero2, numero3;
    printf("Ingrese tres numeros: ");
    scanf("%d %d %d", &numero1, &numero2, &numero3);
    return (numero1 * numero1) + (numero2 * numero2) + (numero3 * numero3);
}

void contarMultiplos() {
    int multiplos3 = 0, multiplos5 = 0, multiplos7 = 0;
    for (int i = 1; i <= 50; i++) {
        if (i % 3 == 0) multiplos3++;
        if (i % 5 == 0) multiplos5++;
        if (i % 7 == 0) multiplos7++;
    }
    printf("Cantidad de multiplos: \n");
    printf("De 3: %d\n", multiplos3);
    printf("De 5: %d\n", multiplos5);
    printf("De 7: %d\n", multiplos7);
}

void calcularPromedio(int inicio, int fin) {
    int sumaTotal = 0, cantidadNumeros = 0;
    for (int i = inicio; i <= fin; i++) {
        sumaTotal += i;
        cantidadNumeros++;
    }
    printf("El promedio de los numeros entre %d y %d es: %.2f\n", inicio, fin, (float)sumaTotal / cantidadNumeros);
}
