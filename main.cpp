#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#define MAX_BLT 100
#define TBLR_SIZE 25
#define PRM_CNT 10

typedef struct
{
    char nom[50];
    char dom[100];
    char cod[6];
    char tipo[10];
} Blt;

Blt bltsVend[MAX_BLT];
int totBlts = 0;


void imprimirMatriculas() {
    printf("\n|==============================================|\n");
    printf("|         Matriculas de estudiantes            |\n");
    printf("|==============================================|\n");
    printf("| 187855 | Castillo Gaytan Noe                 |\n");
    printf("| 187339 | Tristan Contreras David Alejandro   |\n");
    printf("|==============================================|\n");
}

void mostrarTblr()
{
    printf("\n=== Tablero de Sorteo ===\n");
    for (int i = 0; i < TBLR_SIZE; i++)
    {
        if (i % 5 == 0)
            printf("\n");
        printf("[%2d] ", i + 1);
    }
    printf("\n");
}

void genCod(char *cod)
{
    for (int i = 0; i < 5; i++)
    {
        cod[i] = 'A' + rand() % 26;
    }
    cod[5] = '\0';
}

void ventaBlts()
{
    if (totBlts >= MAX_BLT)
    {
        printf("No hay mas boletos disponibles.\n");
        return;
    }

    Blt nuevo;
    printf("\n=== Venta de boletos ===\n");
    printf("Ingrese su nombre: ");
    getchar();
    fgets(nuevo.nom, sizeof(nuevo.nom), stdin);
    nuevo.nom[strcspn(nuevo.nom, "\n")] = 0;

    printf("Ingrese su domicilio: ");
    fgets(nuevo.dom, sizeof(nuevo.dom), stdin);
    nuevo.dom[strcspn(nuevo.dom, "\n")] = 0;

    int cat;
    do
    {
        printf("Seleccione la categoria del boleto:\n");
        printf("1. Basico\n2. Premium\n3. Oro\n");
        printf("Ingrese el numero de la opcion: ");
        scanf("%d", &cat);
        switch (cat)
        {
        case 1:
            strcpy(nuevo.tipo, "Basico");
            break;
        case 2:
            strcpy(nuevo.tipo, "Premium");
            break;
        case 3:
            strcpy(nuevo.tipo, "Oro");
            break;
        default:
            printf("Opcion no valida. Intente de nuevo.\n");
        }
    } while (cat < 1 || cat > 3);

    genCod(nuevo.cod);
    mostrarTblr();

    bltsVend[totBlts++] = nuevo;

    printf("\nDatos registrados:\n");
    printf("Nombre: %s\n", nuevo.nom);
    printf("Domicilio: %s\n", nuevo.dom);
    printf("Categoria de boleto: %s\n", nuevo.tipo);
    printf("Codigo asignado: %s\n", nuevo.cod);
}

void consultaBltsVend()
{
    printf("\n=== Consulta de boletos vendidos ===\n");
    if (totBlts == 0)
    {
        printf("No se han vendido boletos aun.\n");
        return;
    }
    printf("\n -----------------------------------------------------------------\n");
    printf("| %-20s | %-20s | %-5s | %-7s |\n", "Nombre", "Domicilio", "Codigo", "Tipo");
    printf(" -----------------------------------------------------------------\n");
    for (int i = 0; i < totBlts; i++)
    {
        printf("| %-20s | %-20s | %-5s | %-7s |\n",
               bltsVend[i].nom, bltsVend[i].dom,
               bltsVend[i].cod, bltsVend[i].tipo);
    }
    printf(" -----------------------------------------------------------------\n");
}

int main()
{
    srand(time(NULL));
    int opc;
    imprimirMatriculas();
    do
    {
        printf("\n===== SISTEMA DE SORTEO =====\n");
        printf("1. Venta de boletos\n");
        printf("2. Consulta de boletos vendidos\n");
        printf("3. Consulta de premios ganados\n");
        printf("4. Fondos recaudados\n");
        printf("5. Configuracion\n");
        printf("6. Salir\n");
        printf("Seleccione una opcion: ");
        scanf("%d", &opc);

        switch (opc)
        {
        case 1:
            ventaBlts();
            break;
        case 2:
            consultaBltsVend();
            break;
        case 3:
            printf("\n -----------------------------------------------------------------\n");
            printf("| %-20s | %-20s | %-5s | %-7s |\n", "Nombre", "Domicilio", "Codigo", "Tipo");
            printf(" -----------------------------------------------------------------\n");
            break;
        case 4:
            printf("\n -----------------------------------------------------------------\n");
            printf("| %-20s | %-20s | %-5s | %-7s |\n", "Nombre", "Domicilio", "Codigo", "Tipo");
            printf(" -----------------------------------------------------------------\n");
            break;
        case 5:
            printf("\n=== Configuracion ===\n");
            break;
        case 6:
            printf("Saliendo del programa...\n");
            break;
        default:
            printf("Opcion no valida. Intente de nuevo.\n");
        }
    } while (opc != 6);

    return 0;
}
