#include <stdio.h>

void intercambio(int, int);
main()
{
    int a=1, b=2;
    printf("a=%d y b=%d\n",a,b);
    intercambio(a,b);
    printf("a=%d y b=%d\n",a,b);
}


void intercambio (int a,int b)
{
    int aux;
    aux=a;
    a=b;
    b=aux;
    printf("a=%d y b=%d\n",a,b);
}