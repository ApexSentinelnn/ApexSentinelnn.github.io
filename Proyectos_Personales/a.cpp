//Desarrolado por Alejandro Tristan Contreras 187339		| Now Castillo Gaytan 187855
#include <stdio.h>


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
			else if(j==i+1 || (j==base-i-2)) 						
			printf("*");
			else
			printf(" ");
					
		}
		printf("\n");
	}
	//
}
