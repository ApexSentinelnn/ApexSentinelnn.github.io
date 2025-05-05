#include <stdio.h>
main()
{
    int v=3;
    int *pv;

    pv=&v;
    printf("\n*pv=%d v=%d", *pv,v);

    *pv=0;
    printf("\n\n*pv=%d v=%d", *pv,v);
}