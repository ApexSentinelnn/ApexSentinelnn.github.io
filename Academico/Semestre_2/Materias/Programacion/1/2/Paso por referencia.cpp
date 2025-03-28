#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

// Función 1: Modificación de valores por referencia
void fun1(float *valor1, int *valor2) {
    if (fmod(*valor1, 7) == 0) {
        *valor1 = sqrt(*valor1);
    }
    
    if (*valor2 < 20) {
        int producto = 1;
        for (int i = 1; i <= *valor2; i++) {
            producto *= i;
        }
        *valor2 = producto;
    }
}

// Función 2: Elevar a potencia y sumar número aleatorio
void fun2(int valor1, float *valor2, int potencia) {
    valor1 = pow(valor1, potencia); // Modificamos la copia local
    
    srand(time(0));
    int aleatorio = rand() % 15 + 1; // Número entre 1 y 15
    *valor2 += aleatorio;
    
}

// Versión alternativa de fun2 que devuelve ambos valores
void fun2_correcta(int *valor1, float *valor2, int potencia) {
    *valor1 = pow(*valor1, potencia);
    
    srand(time(0));
    int aleatorio = rand() % 15 + 1;
    *valor2 += aleatorio;
}

// Función 3: Cálculo de e^x usando la serie de Taylor
double fun3(int x, int n) {
    double resultado = 1.0;
    double termino = 1.0;
    
    for (int i = 1; i < n; i++) {
        termino *= (double)x / i;
        resultado += termino; 
    }
    
    return resultado;
}

int main() {
    int opcion;

    do {
        printf("\nSeleccione una opcion:\n");
        printf("1. Modificar valores con fun1\n");
        printf("2. Potencia y numero aleatorio con fun2\n");
        printf("3. Calcular e^x con fun3\n");
        printf("4. Salir\n");
        printf("Opcion: ");
        scanf("%d", &opcion);

        switch (opcion) {
            case 1: {
                float valor1;
                int valor2;

                printf("Ingrese un valor Numero: ");
                scanf("%f", &valor1);
                printf("Ingrese un valor Numero: ");
                scanf("%d", &valor2);

                fun1(&valor1, &valor2);
                printf("Nuevos valores -> Valor 1: %.2f, Valor 2: %d\n", valor1, valor2);
                break;
            }
            
            case 2: {
                int num1, potencia;
                float num2;

                printf("Ingrese un numero entero: ");
                scanf("%f", &num1);
                printf("Ingrese un numero flotante: ");
                scanf("%f", &num2);
                printf("ingrese la potencia: ");
                scanf("%d", &potencia);
                
                /*
                int num1, potencia;
                float num2;

                printf("Ingrese un numero entero: ");
                scanf("%d", &num1);
                printf("Ingrese un numero flotante: ");
                scanf("%f", &num2);
                printf("Ingrese la potencia: ");
                scanf("%d", &potencia);

                // Guardamos el valor original para mostrar
                int original_num1 = num1;
                float original_num2 = num2;
                
                // Llamamos a la función corregida
                fun2_correcta(&num1, &num2, potencia);
                
                // Mostramos resultados en main como pide el requerimiento
                printf("Resultados:\n");
                printf("Valor 1 original: %d elevado a %d = %d\n", original_num1, potencia, num1);
                printf("Valor 2 original: %.2f + aleatorio = %.2f\n", original_num2, num2);
                */
                break;
            }
            
            case 3: {
                int x, n;

                printf("Ingrese el valor de x para calcular e^x: ");
                scanf("%d", &x);
                printf("Ingrese el numero de terminos n: ");
                scanf("%d", &n);

                double resultado = fun3(x, n);
                printf("El resultado de e^%d con %d terminos es: %.4f\n", x, n, resultado);
                break;
            }
            
            case 4:
                printf("Saliendo del programa...\n");
                break;
            default:
                printf("Opcion no valida. Intente de nuevo.\n");
        }
    } while (opcion != 4);

    return 0;
}