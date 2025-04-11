#include <stdio.h>

int factorial(int a);

main()
{
    int a;

    printf("Numero entero: ");
    scanf("%d",&a);
    if (a<=1)
    {
        return (1);
    }
        else
        {
            return(a*factorial(a-1));
        }

    printf("El factorial de %d es %d..:",a,factorial(a));
    return 0;
}
