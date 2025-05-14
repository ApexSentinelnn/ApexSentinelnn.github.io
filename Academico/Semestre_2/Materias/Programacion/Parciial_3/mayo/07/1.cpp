#include<stdio.h>
#include<stdlib.h>
#include<string.h>

//Declaración de la estructura cd:

struct cd
{
    char titulo[30];
    char artista[25];
    int num_canciones;
    float precio;
    char fecha_compra[10];
};

cd mis_cds[3];


void matricula(){
    printf("\n|==============================================|\n");
    printf("|         Matriculas de estudiantes            |\n");
    printf("|==============================================|\n");
    printf("| 187855 | Castillo Gaytan Noe                 |\n");
    printf("|==============================================|\n");
}
void leer() {
    printf("\n------LEER DATOS------\n");
    for (int i = 0; i < 3; i++) {
        printf("\n--NUMERO DE CD: #%d--", i + 1);
        printf("\n\nIngresa el titulo: ");
        fgets(mis_cds[i].titulo, sizeof(mis_cds[i].titulo), stdin);
        strtok(mis_cds[i].titulo, "\n");

        printf("\nIngresa el artista: ");
        fgets(mis_cds[i].artista, sizeof(mis_cds[i].artista), stdin);
        strtok(mis_cds[i].artista, "\n");

        printf("\nIngresa el numero de canciones: ");
        while (scanf("%d", &mis_cds[i].num_canciones) != 1) {
            printf("Entrada invalida. Ingresa un numero: ");
            while (getchar() != '\n'); 
        }

        printf("\nIngresa el precio: ");
        while (scanf("%f", &mis_cds[i].precio) != 1) {
            printf("Entrada invalida. Ingresa un numero: ");
            while (getchar() != '\n'); 
        }
        getchar(); 

        printf("\nIngresa la fecha de compra: ");
        fgets(mis_cds[i].fecha_compra, sizeof(mis_cds[i].fecha_compra), stdin);
        strtok(mis_cds[i].fecha_compra, "\n");
    }
}

void mostrar() {
    printf("\n-----MOSTRAR DATOS-----");
    for (int i = 0; i < 3; i++) {
        printf("\n\n--NUMERO DE CD: #%d--", i + 1);
        printf("\nTitulo: %s", mis_cds[i].titulo);
        printf("\nArtista: %s", mis_cds[i].artista);
        printf("\nNumero de Canciones: %d", mis_cds[i].num_canciones);
        printf("\nPrecio: $%.2f", mis_cds[i].precio);
        printf("\nFecha de compra: %s", mis_cds[i].fecha_compra);
    }
}

void menu() {
    int opc;
    do {
        printf("\n\n1. Leer Datos\n2. Mostrar datos\n3. Salir\nElige una opcion: ");
        while (scanf("%d", &opc) != 1) {
            printf("Entrada invalida. Ingresa un numero: ");
            while (getchar() != '\n'); // Clear input buffer
        }
        getchar(); 

        switch (opc) {
            case 1:
                leer();
                break;
            case 2:
                mostrar();
                break;
            case 3:
                printf("\n...Saliste del programa...\n");
                return;
            default:
                printf("\n...Ingresa una opcion correcta...\n");
                break;
        }
    } while (1);
}

main()
{
    matricula();
    menu();
}