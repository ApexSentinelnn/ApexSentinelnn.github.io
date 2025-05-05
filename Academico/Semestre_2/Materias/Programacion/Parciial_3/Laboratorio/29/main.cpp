#include <stdio.h>
#include <stdbool.h>

#define MAX_FILAS 10
#define MAX_COLUMNAS 10

void matriculas(){
    printf("\n|==============================================|\n");
    printf("|         Matriculas de estudiantes            |\n");
    printf("|==============================================|\n");
    printf("| 187855 | Castillo Gaytan Noe                 |\n");
    printf("| 187339 | Tristan Contreras David Alejandro   |\n");
    printf("|==============================================|\n");
}

void inicializarSala(int sala[MAX_FILAS][MAX_COLUMNAS]) {
    for (int i = 1; i < MAX_FILAS; i++) {
        for (int j = 1; j < MAX_COLUMNAS; j++) {
            sala[i][j] = 0;//0 el asiento está disponible
        }
    }
}

void mostrarSala(int sala[MAX_FILAS][MAX_COLUMNAS]) {
    printf("\n--- Sala de Cine ---\n");
    printf("   ");//Espacio filas
    for (int j = 1; j < MAX_COLUMNAS; j++) {
        printf(" %d  ", j);//Indicador de columnas
    }
    printf("\n");

    for (int i = 1; i < MAX_FILAS; i++) {
        printf(" %d ", i);//Indicador de filas
        for (int j = 1; j < MAX_COLUMNAS; j++) {
            if (sala[i][j] == 0) {
                printf("[O] ");//Asiento disponible
            } else {
                printf(" X  ");//Asiento reservado
            }
        }
        printf("\n");
    }
}

bool verificarDisponibilidad(int sala[MAX_FILAS][MAX_COLUMNAS], int fila, int columna) {
    if (fila <= 0 || fila >= MAX_FILAS || columna <= 0 || columna >= MAX_COLUMNAS) {
        return false;//Asiento invalido
    }
    return sala[fila][columna] == 0;//true si el asiento está disponible
}

bool reservarAsiento(int sala[MAX_FILAS][MAX_COLUMNAS], int fila, int columna) {
    if (verificarDisponibilidad(sala, fila, columna)) {
        sala[fila][columna] = 1;//Reservar el asiento
        return true;
    }
    return false;//Asiento ya reservado o inválido
}

int main() {
    int sala[MAX_FILAS][MAX_COLUMNAS];
    int opcion;
    int fila, columna;

    matriculas();
    inicializarSala(sala);
    

    do {
        printf("\n--- Sistema de Reservacion de Cine ---\n");
        printf("1. Mostrar Sala\n");
        printf("2. Reservar Asiento\n");
        printf("3. Verificar Disponibilidad de Asiento\n");
        printf("0. Salir\n");
        printf("Ingrese su opcion: ");
        scanf("%d", &opcion);

        switch (opcion) {
            case 1:
                mostrarSala(sala);
                break;
            case 2:
                printf("Ingrese la fila (1-%d): ", MAX_FILAS - 1);
                scanf("%d", &fila);
                printf("Ingrese la columna (1-%d): ", MAX_COLUMNAS - 1);
                scanf("%d", &columna);
                if (reservarAsiento(sala, fila, columna)) {
                    printf("Asiento reservado exitosamente.\n");
                } else {
                    printf("No se pudo reservar el asiento. Verifique si esta disponible o si los datos son validos.\n");
                }
                break;
            case 3:
                printf("Ingrese la fila (1-%d): ", MAX_FILAS - 1);
                scanf("%d", &fila);
                printf("Ingrese la columna (1-%d): ", MAX_COLUMNAS - 1);
                scanf("%d", &columna);
                if (verificarDisponibilidad(sala, fila, columna)) {
                    printf("El asiento esta disponible.\n");
                } else {
                    printf("El asiento no esta disponible o es invalido.\n");
                }
                break;
            case 0:
                printf("Saliendo del sistema...\n");
                break;
            default:
                printf("Opcion invalida. Intente de nuevo.\n");
        }
    } while (opcion != 0);

    return 0;
}