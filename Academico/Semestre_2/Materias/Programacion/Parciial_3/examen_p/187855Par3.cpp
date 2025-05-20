#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define N_PROD 4 //num de productos

// estruc para almacenar información de un producto
typedef struct {
    char nom[30];     //nom prod
    int ex;           //existencias
    int pre;          //precio
    char fVenta[25];  //form de venta
} Prod;

//prot de func
void impMat();
void altaProd();
void repProd();
void guardarArch(const Prod p[], int n);
void detFormaVenta(Prod *p);
void impEnc(FILE *arch);
void casos();

void impMat()
{
    printf("\n|==============================================|\n");
    printf("|         Matricula de estudiante            |\n");
    printf("|==============================================|\n");
    printf("| 187855 | Castillo Gaytan Noe                 |\n");
    printf("|==============================================|\n");
}

//determina forma de venta
void detFormaVenta(Prod *p) {
    if (p->pre >= 300 && p->pre <= 400) {
        strcpy(p->fVenta, "Contado");
    } else if (p->pre >= 401 && p->pre <= 500) {
        strcpy(p->fVenta, "Meses sin intereses");
    } else {
        strcpy(p->fVenta, "Tiempo diferido");
    }
}

//imprime encabezado en el archivo
void impEnc(FILE *arch) {
    fprintf(arch, "%-25s%-15s%-10s%s\n", "Producto", "Existencias", "Precios", "FormaVenta");
    for (int i = 0; i < 60; i++) fputc('-', arch);
    fputc('\n', arch);
}

//guarda productos en archivo
void guardarArch(const Prod p[], int n) {
    FILE *arch = fopen("187855Par3.txt", "w");
    if (!arch) {
        printf("Error al abrir el archivo para escritura.\n");
        return;
    }

    fprintf(arch, "REPORTE DE PRODUCTOS (ARCHIVO)\n");
    impEnc(arch);//encabezado

    //producto en el archivo
    for (int i = 0; i < n; i++) {
        fprintf(arch, "%-25s%-15d%-10d%s\n",
            p[i].nom,
            p[i].ex,
            p[i].pre,
            p[i].fVenta
        );
    }

    fclose(arch);
}

//alta de producto
void altaProd() {
    Prod p[N_PROD] = {
        {"Camara de seguridad", 0, 0, ""},
        {"Contacto WI-FI", 0, 0, ""},
        {"Foco Led Multicolor", 0, 0, ""},
        {"Bocina Bluetooth", 0, 0, ""}
    };

    // asigna existencias, precio y forma de venta aleatoriamente
    for (int i = 0; i < N_PROD; i++) {
        p[i].ex = 20 + rand() % 11;      //existencias entre 20 y 30
        p[i].pre = 300 + rand() % 301;   //precio entre 300 y 600
        detFormaVenta(&p[i]);            //determina forma de venta
    }

    guardarArch(p, N_PROD); //guarda productos en archivo
    printf("Productos registrados exitosamente en el archivo 187855Par3.txt.\n");
}

void repProd() {
    FILE *arch = fopen("187855Par3.txt", "r");
    if (!arch) {
        printf("Error al abrir el archivo para lectura.\n");
        return;
    }

    char lin[128];
    printf("\nREPORTE DESDE ARCHIVO:\n");
    while (fgets(lin, sizeof(lin), arch)) {
        printf("%s", lin);
    }

    fclose(arch);
}

//casos de uso
void casos(){
    int op;
    do {
        printf("\nMENU DE INVENTARIO\n");
        printf("1. Alta de productos\n");
        printf("2. Reporte de productos\n");
        printf("3. Salir\n");
        printf("Seleccione una opcion: ");
        scanf("%d", &op);

        switch(op) {
            case 1: altaProd(); break;
            case 2: repProd(); break;
            case 3: printf("Saliendo del programa...\n"); break;
            default: printf("Opcion no valida. Intente de nuevo.\n");
        }
    } while (op != 3);
}

int main() {
    srand((unsigned int)time(0)); //semilla aleatoria
    impMat();
    casos(); //funcion de casos
    return 0;
}