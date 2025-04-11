#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TAM 10

int main(){
    srand(time(0));
    int arreg[TAM], result[TAM / 2];
    int sum = 0, par_pri = 0, imp_pri = 0;
    int par_resul = 0, imp_resul = 0;
    int may = 0, posi = 0;

    //arrgelos aleatorios 1 al 10 
    for (int i = 0; i < TAM; i++)
    {
        arreg[i] = rand() % 10 + 1;
        sum += arreg[i];
        if (arreg[i] % 2 == 0) par_pri++;
        else imp_pri++;
    }

    //se llenan los arreglos resultados
    for (int i = 0; i < TAM / 2; i++)
    {
        result[i] = arreg[i] * arreg[TAM - 1 - i];
        if (result[i] % 2 == 0) par_resul++;
        else imp_resul++;
        if (result[i] > may)
        {
            may = result[i];
            posi = i;
        }
    }
    
    //Encabezado
    printf("****************************************\n");
    printf("* Desarrollado por: Noe Castillo Gaytan *\n");
    printf("* Matricula: 187855 *\n");
    printf("****************************************\n\n");

    //Mstramos los arreglos
    printf("Arreglo principal: \n");
    for (int i = 0; i< TAM; i++)
    {
        printf("%d ",arreg[i]);
    }
    
    printf("\nArreglo resultado: \n");
    for (int i = 0; i< TAM / 2; i++)
    {
        printf("%d ",result[i]);
    }
    printf("\n");
    
    //Mostramos salidas
    printf("\nPares e impares:\n");
    printf("Arreglo principal - Pares: %d Impares: %d\n", par_pri, imp_pri);
    printf("Arreglo resultado - Pares: %d Impares: %d\n", par_resul, imp_resul);
    printf("\nLa sumatoria del arreglo principal es: %d\n", sum);
    printf("El numero mayor del arreglo resultado es %d y se encuentra en la posicion %d\n", may, posi);

    return 0;
}

