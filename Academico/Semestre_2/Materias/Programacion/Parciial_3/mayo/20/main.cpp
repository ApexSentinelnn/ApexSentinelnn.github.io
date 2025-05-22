//187855 noe castillo
#include<stdio.h>
#include<stdlib.h>
#include<conio.h>

void rellenarMatriz(int fil, int col, int **mat);
void visualizarMatriz(int fil, int col, int **mat);

void rellenarMatriz(int fil, int col, int **mat){
    int idx, jdx;
    for(idx=0; idx<fil; idx++){
        for(jdx=0; jdx<col; jdx++){
            printf("Introduzca el valor para la posicion [%d][%d]: ", idx, jdx);
            scanf("%d", &mat[idx][jdx]);
        }
        printf("\n");
    }
}

void visualizarMatriz(int fil, int col, int **mat){
    int idx, jdx;
    printf("\n--- Contenido de la matriz ---\n");
    for(idx=0; idx<fil; idx++){
        for(jdx=0; jdx<col; jdx++){
            printf("%d\t", mat[idx][jdx]);
        }
        printf("\n");
    }
    printf("----------------------------\n");
}
int main(){
    int idx, jdx;
    int **mat;
    int fil, col;
    
    printf("Digite la cantidad de filas para la matriz: ");
    scanf("%d", &fil);
    
    printf("Digite la cantidad de columnas para la matriz: ");
    scanf("%d", &col);
    
    mat = (int **)malloc(fil * sizeof(int*));
    
    if(mat == NULL){
        printf("Error: No hay suficiente memoria disponible");
        exit(1);
    }
    
    for(idx=0; idx<fil; idx++){
        mat[idx] = (int*)malloc(col * sizeof(int));
        if(mat[idx] == NULL){
            printf("Error: No hay suficiente memoria disponible\n");
            return -1;
        }
    }
    
    printf("\n\nAsignacion de memoria completada correctamente\n\n");
    printf("\n\nMatriz de %d filas y %d columnas creada\n\n", fil, col);
    getch();
    
    rellenarMatriz(fil, col, mat);
    
    visualizarMatriz(fil, col, mat);
    
    for(idx=0; idx<fil; idx++){
        free(mat[idx]);
    }
    free(mat);
    
    return 0;
}