#include <stdio.h>
int suma(int, int);

int main(){
    int a=10, b=25,t;
    t=suma(a,b);
    printf("%d", t);

    //printf("%d",suma(a,b));
    //suma(a,b);
}

int suma(int x, int y)
{
    int sum;
    sum=x+y;
    return(sum);
    //return 
}