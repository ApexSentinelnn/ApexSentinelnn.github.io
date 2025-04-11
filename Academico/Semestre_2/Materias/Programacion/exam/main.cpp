#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define numVen 5
#define numMes 3

//almacenar la información
typedef struct {
    char nombre[50];
    int ventas[numMes];
    int venT;
    float comi;
} Vendedor;

void matri(void) {
    printf("****************************************\n");
    printf("* Desarrollado por: Noe Castillo Gaytan *\n");
    printf("* Matricula: 187855 *\n");
    printf("****************************************\n\n");
}

//nombres de vendedores
void solNom(Vendedor vendedores[]) {
    int i;
    for (i = 0; i < numVen; i++) {
        printf("Ingrese el nombre del vendedor %d: ", i + 1);
        scanf("%s", vendedores[i].nombre);
    }
}

//registrar las ventas
void regVen(Vendedor vendedores[]) {
    int i, j;
    
    for (i = 0; i < numVen; i++) {
        vendedores[i].venT = 0;
        
        // Registrar ventas para cada mes
        for (j = 0; j < numMes; j++) {
            //ventas aleatorias entre 50 y 100
            vendedores[i].ventas[j] = rand() % 51 + 50;
            vendedores[i].venT += vendedores[i].ventas[j];
        }
        
        //Calcular comision
        if (vendedores[i].venT > 200) {
            vendedores[i].comi = vendedores[i].venT * 0.15;
        } else {
            vendedores[i].comi = 0.0;
        }
    }
}

//informacion en tabla
void mostInf(Vendedor vendedores[]) {
    int i, j;
    
    printf("\nResumen de Ventas y comisiones:\n\n");
    printf("Vendedor\tVentas\t\tVentas\t\tVentas\t\tVentas\t\tcomision\n");
    printf("\t\tMes 1\t\tMes 2\t\tMes 3\t\tTotales\n");
    printf("--------------------------------------------------------------------------------\n");
    
    for (i = 0; i < numVen; i++) {
        printf("%s\t", vendedores[i].nombre);
        
        for (j = 0; j < numMes; j++) {
            printf("%d\t\t", vendedores[i].ventas[j]);
        }
        
        printf("%d\t\t%.2f\n", vendedores[i].venT, vendedores[i].comi);
    }
}

void indRan(void) {
    srand(time(NULL));
}

int main(void) {
    //arreglo de vendedores
    Vendedor vendedores[numVen];
    int r;
    
    do
    {
            
        //numeros aleatorios
        indRan();
        
        //matrícula
        matri();
        
        //nombres de vendedores
        solNom(vendedores);
        
        //Registrar ventas
        regVen(vendedores);
        
        //información en tabla
        mostInf(vendedores);
        
        printf("\nDesea repetir el programa:\n");
        printf("1.SI    |   2.NO\n");
        scanf("%d",&r);
    } while (r == 2);

    return 0;
}