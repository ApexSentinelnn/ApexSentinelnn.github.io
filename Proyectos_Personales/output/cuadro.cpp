#include <stdio.h>



/*int main(){
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
    } */
//////////////////////////////////////
main()
{
	
	int altura,i,j,base,h;
	h=1;
	printf("Ingresa la altura: ");
	scanf("%d", &altura);
	
	base=((altura*2)-1);
	
	/////////////////////////
	
	 // Triángulo superior (contorno)
    for (i = 0; i < altura; i++)
    {
        // Recorrido por cada columna
        for (j = 0; j < base; j++)
        {
            // Condición para imprimir * solo en el contorno
            if (j == altura - i - 1 || j == altura + i - 1 || i == altura - 1)
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
	
	
	
	//////////////////// CUADRADO
	
	
	
	
	for(i=0;i<(altura-1);i++) //i == piso
	{
		
		for(j=0;j<base;j++) //j=punto por piso
		{
			if(i==(altura-2))
			printf("*");
			else if(j==0 || j==(base-1))
			printf("*");
			else
			printf(" ");
					
		}
		printf("\n");
	}
	
}
