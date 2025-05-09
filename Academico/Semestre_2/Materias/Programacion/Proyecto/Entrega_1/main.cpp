#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

// Definiciones de constantes
#define MAX_BLT 100      // Máximo número de boletos
#define TBLR_SIZE 25     // Tamaño del tablero
#define PRM_CNT 10       // Número de premios

// Precios de los boletos
#define PRECIO_BASICO 25.0
#define PRECIO_PREMIUM 50.0
#define PRECIO_ORO 100.0

// Estructura para los boletos
typedef struct
{
    char nom[50];   // Nombre del comprador
    char dom[100];  // Domicilio del comprador
    char cod[6];    // Código del boleto
    char tipo[10];  // Tipo de boleto
    float precio;   // Precio del boleto
} Blt;

// Arreglo para almacenar los boletos vendidos
Blt bltsVend[MAX_BLT];
int totBlts = 0; // Contador de boletos vendidos

// Función para imprimir las matrículas de los estudiantes
void impMat()
{
    printf("\n|==============================================|\n");
    printf("|         Matriculas de estudiantes            |\n");
    printf("|==============================================|\n");
    printf("| 187855 | Castillo Gaytan Noe                 |\n");
    printf("| 187339 | Tristan Contreras David Alejandro   |\n");
    printf("|==============================================|\n");
}

// Función para mostrar el tablero del sorteo
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

// Función para generar un código aleatorio de boleto
void genCod(char *cod)
{
    for (int i = 0; i < 5; i++)
    {
        cod[i] = 'A' + rand() % 26;
    }
    cod[5] = '\0';
}

// Función para la venta de boletos
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
    getchar(); // Captura el salto de línea
    fgets(nuevo.nom, sizeof(nuevo.nom), stdin);
    nuevo.nom[strcspn(nuevo.nom, "\n")] = 0;

    printf("Ingrese su domicilio: ");
    fgets(nuevo.dom, sizeof(nuevo.dom), stdin);
    nuevo.dom[strcspn(nuevo.dom, "\n")] = 0;

    int cat;
    do
    {
        printf("Seleccione la categoria del boleto:\n");
        printf("1. Basico ($%.2f)\n2. Premium ($%.2f)\n3. Oro ($%.2f)\n", PRECIO_BASICO, PRECIO_PREMIUM, PRECIO_ORO);
        printf("Ingrese el numero de la opcion: ");
        if (scanf("%d", &cat) != 1)
        {
            printf("Entrada invalida. Intente de nuevo.\n");
            while (getchar() != '\n'); // Limpiar buffer
            continue;
        }
        switch (cat)
        {
        case 1:
            strcpy(nuevo.tipo, "Basico");
            nuevo.precio = PRECIO_BASICO;
            break;
        case 2:
            strcpy(nuevo.tipo, "Premium");
            nuevo.precio = PRECIO_PREMIUM;
            break;
        case 3:
            strcpy(nuevo.tipo, "Oro");
            nuevo.precio = PRECIO_ORO;
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
    printf("Precio: $%.2f\n", nuevo.precio);
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

// Función principal del programa
int main()
{
    srand(time(NULL)); // Inicializa la semilla para la generación de números aleatorios
    int opc;
    impMat(); // Muestra matrículas
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
            printf("\nConsulta de premios ganados (en desarrollo)\n");
            break;
        case 4:
            printf("\nFondos recaudados (en desarrollo)\n");
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
