#include <stdio.h>

void func1(int u, int v);
void func2(int *pu, int *pv);

main ()
{
    int u=1,v=3;

    printf("\n Antes de la llamda a func1: u=%d v=%d",u,v);
        func1(u,v);
    printf("\n Despues de la llamda a func1: u=%d v=%d",u,v);

    printf("\n Antes de la llamda a func2: u=%d v=%d",u,v);
        func2(&u,&v);
    printf("\n Despues de la llamda a func2: u=%d v=%d",u,v);

    return 0;
}

