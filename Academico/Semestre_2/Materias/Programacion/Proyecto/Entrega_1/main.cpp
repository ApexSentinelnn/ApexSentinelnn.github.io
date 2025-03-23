#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

// Definición de constantes
#define MAX_BLT 100  // Máximo de boletos que se pueden vender
#define TBLR_SIZE 25 // Tamaño del tablero de sorteo
#define PRM_CNT 10   // Número de premios (aunque no se usa en el código)

// Estructura que representa un boleto
typedef struct
{
    char nom[50];  // Nombre del comprador
    char dom[100]; // Domicilio del comprador
    char cod[6];   // Código único del boleto
    char tipo[10]; // Tipo de boleto (Básico, Premium, Oro)
} Blt;

// Arreglo que almacena los boletos vendidos
Blt bltsVend[MAX_BLT];
int totBlts = 0; // Contador de boletos vendidos

// Función para imprimir las matrículas y nombres
void impMat()
{
    printf("\n|==============================================|\n");
    printf("|         Matriculas de estudiantes            |\n");
    printf("|==============================================|\n");
    printf("| 187855 | Castillo Gaytan Noe                 |\n");
    printf("| 187339 | Tristan Contreras David Alejandro   |\n");
    printf("|==============================================|\n");
}

// Funcion para mostrar el tablero del sorteo
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

// Genera un código aleatorio de 5 caracteres para el boleto
void genCod(char *cod)
{
    for (int i = 0; i < 5; i++)
    {
        cod[i] = 'A' + rand() % 26; // Caracteres aleatorios entre 'A' y 'Z'
    }
    cod[5] = '\0'; // Terminador de cadena
}

// Función para vender boletos
void ventaBlts()
{
    // Verifica si aún hay boletos disponibles
    if (totBlts >= MAX_BLT)
    {
        printf("No hay mas boletos disponibles.\n");
        return;
    }

    Blt nuevo; // Nuevo boleto

    // Solicita los datos del comprador
    printf("\n=== Venta de boletos ===\n");
    printf("Ingrese su nombre: ");
    getchar();
    fgets(nuevo.nom, sizeof(nuevo.nom), stdin);
    nuevo.nom[strcspn(nuevo.nom, "\n")] = 0;

    printf("Ingrese su domicilio: ");
    fgets(nuevo.dom, sizeof(nuevo.dom), stdin);
    nuevo.dom[strcspn(nuevo.dom, "\n")] = 0;

    int cat;
    // Selección de la categoría del boleto
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

    genCod(nuevo.cod); // Genera código aleatorio para el boleto
    mostrarTblr();     // Muestra el tablero del sorteo

    bltsVend[totBlts++] = nuevo; // Almacena el boleto vendido

    // Muestra los datos registrados
    printf("\nDatos registrados:\n");
    printf("Nombre: %s\n", nuevo.nom);
    printf("Domicilio: %s\n", nuevo.dom);
    printf("Categoria de boleto: %s\n", nuevo.tipo);
    printf("Codigo asignado: %s\n", nuevo.cod);
}

// Función para consultar los boletos vendidos
void consultaBltsVend()
{
    printf("\n=== Consulta de boletos vendidos ===\n");
    if (totBlts == 0)
    {
        printf("No se han vendido boletos aun.\n");
        return;
    }

    // Muestra una tabla con la información de los boletos vendidos
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
    impMat();

    // Bucle del menú principal
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
            ventaBlts(); // Llamada a la venta de boletos
            break;
        case 2:
            consultaBltsVend(); // Llamada a la consulta de boletos vendidos
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
            printf("\n=== Configuracion ===\n"); // Sección de configuración (sin funcionalidades aún)
            break;
        case 6:
            printf("Saliendo del programa...\n"); // Salida del programa
            break;
        default:
            printf("Opcion no valida. Intente de nuevo.\n"); // Mensaje de error si la opción no es válida
        }
    } while (opc != 6); // Repite hasta que el usuario seleccione salir

    return 0;
}
