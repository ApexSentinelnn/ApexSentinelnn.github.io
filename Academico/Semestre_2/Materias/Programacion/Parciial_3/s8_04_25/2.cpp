//Puntero 4
#include <stdio.h>
#include <conio.h>

main()
{
    char var1;
    char *pchar;
    pchar = &var1;

    for (var1 = 'a'; var1 <= 'z'; var1++)
        printf("%c ", *pchar);
        return (0);
}