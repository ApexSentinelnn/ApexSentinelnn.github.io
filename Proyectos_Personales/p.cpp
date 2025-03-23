#include <stdio.h>

void intercambio(int, int);
main()
{
    int a=1, b=2;
    printf("a=%d y b=%d\n",a,b);
    intercambio(a,b);
    printf("a=%d y b=%d\n",a,b);
}