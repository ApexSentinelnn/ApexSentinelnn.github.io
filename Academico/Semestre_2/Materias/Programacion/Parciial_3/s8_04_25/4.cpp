#include <stdio.h>
#include <string.h>

void proc1(int vector[]);

main(){
    int reng,list[5]={10,11,12,13,14};

    proc1(list);

    for(reng=0;reng<=4;reng++)
    printf("%d\n",list[reng]);

}

void proc1(int vector [])
{
    int reng;

    for(reng=0;reng<=4;reng++)
    vector[reng]=vector[reng]+50;
}