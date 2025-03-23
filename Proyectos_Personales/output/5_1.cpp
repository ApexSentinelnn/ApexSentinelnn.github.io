#include <stdio.h>

int main(){
    int col, alt, i, j;

    // Ingreso del número de filas (altura)
    printf("Ingrese las filas: ");
    scanf("%d", &alt);
    // El número de columnas es 2 veces las filas menos 1
    col = (2 * alt - 1);
    // Triángulo superior (contorno)
    for (i = 0; i < alt; i++)
    {
        // Recorrido por cada columna
        for (j = 0; j < col; j++)
        {
            // Condición para imprimir * solo en el contorno
            if (j == alt - i - 1 || j == alt + i - 1 || i == alt - 1)
            {
                printf("*");
            }
            else
            {
                printf(" ");
            }
        }
        printf("\n");
    }

        // Triángulo invertido (contorno)
        for (i = alt - 2; i >= 0; i--)
        {
            for (j = 0; j < col; j++)
            {
                if (j == alt - i - 1 || j == alt + i - 1)
                {
                    printf("*");
                }
                else
                {
                    printf(" ");
                }
            }
            printf("\n");
        }

    return 0;
}
