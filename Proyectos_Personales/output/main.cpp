#include <stdio.h>

int main(){
    int col, alt, i, j;

    printf("Ingrese las filas: ");
    scanf("%d", &alt);

    col = (2 * alt - 1);

    for (i = 0; i < alt; i++)
    {
        for (j = 0; j < col; j++)
        {
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

    return 0;
}
