#include <stdio.h>
#include <stdlib.h>
#include <time.h>



// Llenar la matriz y el vector
void llenar(int filas, int cols, int **mat, int *vec) {
    for (int i = 0; i < filas; i++) {
        for (int j = 0; j < cols; j++) {
            mat[i][j] = (rand() % 10) + 1;
        }
    }
    for (int i = 0; i < cols; i++) {
        vec[i] = (rand() % 10) + 1;
    }
}

// Multiplicación elemento a elemento de matriz por vector
void operaciones(int filas, int cols, int **mat, int *vec, int **matRes) {
    for (int i = 0; i < filas; i++) {
        for (int j = 0; j < cols; j++) {
            matRes[i][j] = mat[i][j] * vec[j];
        }
    }
}

// Imprimir una línea horizontal para la tabla
void imprimirLinea(int cols) {
    printf("+");
    for (int j = 0; j < cols; j++) {
        printf("----+");
    }
    printf("\n");
}

// Mostrar matriz, vector y resultado con formato de tabla
void mostrar(int filas, int cols, int **mat, int vecLen, int *vec, int **matRes) {
    printf("\n---------- Matriz (%d x %d) ----------\n", filas, cols);
    imprimirLinea(cols);
    for (int i = 0; i < filas; i++) {
        printf("|");
        for (int j = 0; j < cols; j++) {
            printf(" %2d |", mat[i][j]);
        }
        printf("\n");
        imprimirLinea(cols);
    }

    printf("\n---------- Vector Original (%d elementos) ----------\n", vecLen);
    printf("+");
    for (int i = 0; i < vecLen; i++) printf("----+");
    printf("\n|");
    for (int i = 0; i < vecLen; i++) printf(" %2d |", vec[i]);
    printf("\n+");
    for (int i = 0; i < vecLen; i++) printf("----+");
    printf("\n");

    printf("\n---------- Matriz Resultado (%d x %d) ----------\n", filas, cols);
    imprimirLinea(cols);
    for (int i = 0; i < filas; i++) {
        printf("|");
        for (int j = 0; j < cols; j++) {
            printf(" %2d |", matRes[i][j]);
        }
        printf("\n");
        imprimirLinea(cols);
    }
}

int main() {
    int filas, cols;
    int *vec;
    int **mat;
    int **matRes;

    srand(time(NULL));
    printf("+---------------------+\n");
    printf("| 187855              |\n");
    printf("| Noe Castillo        |\n");
    printf("+---------------------+\n");
    printf("---------- PRODUCTO DE MATRIZ POR VECTOR ----------");
    printf("\nIngrese el numero de filas de la matriz: ");
    scanf("%d", &filas);

    printf("\nIngrese el numero de columnas de la matriz (tambien sera el numero de elementos del vector): ");
    scanf("%d", &cols);

    printf("\nAsignando memoria para la matriz, el vector y el resultado...espere\n");

    mat = (int **)malloc(filas * sizeof(int *));
    if (mat == NULL) {
        printf("ERROR!! No se logro asignar memoria para las filas :c\n");
        return 1;
    }
    for (int i = 0; i < filas; i++) {
        mat[i] = (int *)malloc(cols * sizeof(int));
        if (mat[i] == NULL) {
            printf("ERROR!! No se logro asignar memoria para la fila %d de la matriz \n", i);
            for (int j = 0; j < i; j++) free(mat[j]);
            free(mat);
            return 1;
        }
    }

    vec = (int *)malloc(cols * sizeof(int));
    if (vec == NULL) {
        printf("ERROR!! No se pudo asignar memoria para el vector de entrada :c\n");
        if (mat != NULL) {
            for (int i = 0; i < filas; i++) free(mat[i]);
            free(mat);
        }
        return 1;
    }

    matRes = (int **)malloc(filas * sizeof(int *));
    if (matRes == NULL) {
        printf("ERROR!! No se pudo asignar memoria para la matriz resultante.\n");
        if (mat != NULL) {
            for (int i = 0; i < filas; i++) free(mat[i]);
            free(mat);
        }
        if (vec != NULL) free(vec);
        return 1;
    }
    for (int i = 0; i < filas; i++) {
        matRes[i] = (int *)malloc(cols * sizeof(int));
        if (matRes[i] == NULL) {
            printf("ERROR!! No se logro asignar memoria para la fila %d de la matriz resultante\n", i);
            for (int j = 0; j < i; j++) free(matRes[j]);
            free(matRes);
            for (int k = 0; k < filas; k++) free(mat[k]);
            free(mat);
            free(vec);
            return 1;
        }
    }

    llenar(filas, cols, mat, vec);
    operaciones(filas, cols, mat, vec, matRes);
    mostrar(filas, cols, mat, cols, vec, matRes);

    printf("\nLiberando memoria....\n");
    for (int i = 0; i < filas; i++) {
        free(mat[i]);
        free(matRes[i]);
    }
    free(mat);
    free(matRes);
    free(vec);
    return 0;
}
