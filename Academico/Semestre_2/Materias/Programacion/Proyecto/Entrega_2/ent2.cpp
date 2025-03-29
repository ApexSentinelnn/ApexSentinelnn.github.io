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
    char nom[50];        // Nombre del comprador
    char dom[100];       // Domicilio del comprador
    char cod[6];         // Código del boleto
    char tipo[10];       // Tipo de boleto
    float precio;        // Precio del boleto
    int numBoleto[5];    // Números elegidos del tablero
    int cantNumeros;     // Cantidad de números seleccionados
    float premioAcumulado; // Premio acumulado en el boleto
} Blt;

// Variables globales
Blt bltsVend[MAX_BLT];
int totBlts = 0;
int tablero[TBLR_SIZE] = {0};
float premios[TBLR_SIZE] = {0};
float fondosRecaudados = 0.0;

// Función para limpiar el buffer de entrada
void limpiarBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

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
        if (tablero[i] == 0)
            printf("[%2d] ", i + 1);
        else
            printf("[XX] ");
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

// Función para inicializar los premios aleatoriamente
void inicializarPremios()
{
    int posicionesPremiadas[PRM_CNT] = {0};
    int posicion, i = 0;
    
    while (i < PRM_CNT) {
        posicion = rand() % TBLR_SIZE;
        
        // Verificar que esta posición no tenga ya un premio
        int repetido = 0;
        for (int j = 0; j < i; j++) {
            if (posicionesPremiadas[j] == posicion) {
                repetido = 1;
                break;
            }
        }
        
        if (!repetido) {
            posicionesPremiadas[i] = posicion;
            premios[posicion] = 5.0 + ((rand() % 50) * 5.0);
            i++;
        }
    }
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
    int intentos = 0;
    float acumulado = 0.0;

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
        printf("1. Basico ($%.2f) - 1 intento\n", PRECIO_BASICO);
        printf("2. Premium ($%.2f) - 3 intentos\n", PRECIO_PREMIUM);
        printf("3. Oro ($%.2f) - 5 intentos\n", PRECIO_ORO);
        printf("Ingrese el numero de la opcion: ");
        if (scanf("%d", &cat) != 1)
        {
            printf("Entrada invalida. Intente de nuevo.\n");
            limpiarBuffer();
            continue;
        }
        switch (cat)
        {
        case 1:
            strcpy(nuevo.tipo, "Basico");
            nuevo.precio = PRECIO_BASICO;
            intentos = 1;
            break;
        case 2:
            strcpy(nuevo.tipo, "Premium");
            nuevo.precio = PRECIO_PREMIUM;
            intentos = 3;
            break;
        case 3:
            strcpy(nuevo.tipo, "Oro");
            nuevo.precio = PRECIO_ORO;
            intentos = 5;
            break;
        default:
            printf("Opcion no valida. Intente de nuevo.\n");
        }
    } while (cat < 1 || cat > 3);
    
    nuevo.cantNumeros = intentos;
    
    // Selección de números del tablero
    for (int i = 0; i < intentos; i++) {
        mostrarTblr();
        int numSeleccionado;
        
        printf("Intento %d/%d - Monto acumulado: $%.2f\n", i+1, intentos, acumulado);
        do
        {
            printf("Seleccione un numero del tablero (1-%d): ", TBLR_SIZE);
            if (scanf("%d", &numSeleccionado) != 1 || numSeleccionado < 1 || numSeleccionado > TBLR_SIZE)
            {
                printf("Numero invalido. Intente de nuevo.\n");
                limpiarBuffer();
                continue;
            }
            
            if (tablero[numSeleccionado - 1] != 0) {
                printf("Ese numero ya fue seleccionado. Intente con otro.\n");
                continue;
            }
            
            break;
        } while (1);
        
        tablero[numSeleccionado - 1] = 1;
        nuevo.numBoleto[i] = numSeleccionado;
        
        if (premios[numSeleccionado - 1] > 0) {
            printf("¡Felicidades! Ha ganado $%.2f en esta casilla.\n", premios[numSeleccionado - 1]);
            acumulado += premios[numSeleccionado - 1];
        } else {
            printf("No hay premio en esta casilla.\n");
        }
    }

    genCod(nuevo.cod);
    nuevo.premioAcumulado = acumulado;
    bltsVend[totBlts++] = nuevo;
    fondosRecaudados += nuevo.precio;

    printf("\nDatos registrados:\n");
    printf("Nombre: %s\n", nuevo.nom);
    printf("Domicilio: %s\n", nuevo.dom);
    printf("Categoria de boleto: %s\n", nuevo.tipo);
    printf("Codigo asignado: %s\n", nuevo.cod);
    printf("Precio: $%.2f\n", nuevo.precio);
    printf("Total de premio acumulado: $%.2f\n", acumulado);
    
    printf("Numeros seleccionados del tablero: ");
    for (int i = 0; i < nuevo.cantNumeros; i++) {
        printf("%d ", nuevo.numBoleto[i]);
    }
    printf("\n");
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
    printf("\n -----------------------------------------------------------------------------\n");
    printf("| %-15s | %-15s | %-5s | %-7s | %-10s |\n", "Nombre", "Domicilio", "Codigo", "Tipo", "Premio");
    printf(" -----------------------------------------------------------------------------\n");
    for (int i = 0; i < totBlts; i++)
    {
        printf("| %-15s | %-15s | %-5s | %-7s | $%-9.2f |\n",
               bltsVend[i].nom, bltsVend[i].dom,
               bltsVend[i].cod, bltsVend[i].tipo, bltsVend[i].premioAcumulado);
    }
    printf(" -----------------------------------------------------------------------------\n");
}

// Función para consultar los premios ganados
void consultaPremios()
{
    printf("\n=== Consulta de premios ganados ===\n");
    printf("En desarrollo.....\n");
}


// Función principal del programa
int main()
{
    srand(time(NULL));
    inicializarPremios();
    
    int opc;
    impMat();
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
            consultaPremios();
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