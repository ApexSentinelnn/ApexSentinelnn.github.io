#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

// Definiciones de constantes
#define maxbol 100      // Máximo número de boletos
#define tamtab 25     // Tamaño del tablero
#define prenum 10       // Número de premios

// Precios de los boletos (pueden ser modificados en configuración)
float prebas = 25.0;
float preprem = 50.0;
float preoro = 100.0;

// Límites de boletos por categoría (pueden ser modificados en configuración)
int maxBasicos = 40;
int maxPremium = 30;
int maxOro = 20;

// Contadores para cada tipo de boleto
int contBasicos = 0;
int contPremium = 0;
int contOro = 0;

// Estructura para los boletos
typedef struct
{
    char nom[50];        // Nombre del comprador
    char dom[100];       // Domicilio del comprador
    char cod[6];         // Código del boleto
    char tipo[10];       // Tipo de boleto
    float precio;        // Precio del boleto
    int numbol[5];       // Números elegidos del tablero
    int catnum;          // Cantidad de números seleccionados
    float premioGanado;  // Premio total ganado
} Blt;

// Variables globales
Blt bltsVend[maxbol];
int totBlts = 0;
int tablero[tamtab] = {0};
float premios[tamtab] = {0};
float fondRec = 0.0;
float totalPremios = 0.0;

// Función para limpiar el buffer de entrada
void limpbuf() {
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
    for (int i = 0; i < tamtab; i++)
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
    const char letras[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    char usado[26] = {0}; // Para marcar letras ya usadas
    int pos;
    
    for (int i = 0; i < 5; i++)
    {
        do {
            pos = rand() % 26;
        } while (usado[pos]); // Repetir si la letra ya fue usada
        
        usado[pos] = 1;
        cod[i] = letras[pos];
    }
    cod[5] = '\0';
}

// Función para inicializar los premios aleatoriamente
void iniPre()
{
    int posicionesPremiadas[prenum] = {0};
    int posicion, i = 0;
    
    // Limpiar premios previos
    for (int j = 0; j < tamtab; j++) {
        premios[j] = 0.0;
    }
    
    while (i < prenum) {
        posicion = rand() % tamtab;
        
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
            premios[posicion] = 5.0 + ((rand() % 50) * 5.0); // Premios entre $5.00 y $250.00
            i++;
        }
    }
}

// Función para la venta de boletos
void ventaBlts()
{
    if (totBlts >= maxbol)
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
        printf("1. Basico ($%.2f) - 1 intento [%d/%d disponibles]\n", prebas, contBasicos, maxBasicos);
        printf("2. Premium ($%.2f) - 3 intentos [%d/%d disponibles]\n", preprem, contPremium, maxPremium);
        printf("3. Oro ($%.2f) - 5 intentos [%d/%d disponibles]\n", preoro, contOro, maxOro);
        printf("Ingrese el numero de la opcion: ");
        if (scanf("%d", &cat) != 1)
        {
            printf("Entrada invalida. Intente de nuevo.\n");
            limpbuf();
            continue;
        }
        
        // Verificar disponibilidad de boletos por categoría
        if (cat == 1 && contBasicos >= maxBasicos) {
            printf("No hay boletos Basicos disponibles.\n");
            cat = 0;
            continue;
        } else if (cat == 2 && contPremium >= maxPremium) {
            printf("No hay boletos Premium disponibles.\n");
            cat = 0;
            continue;
        } else if (cat == 3 && contOro >= maxOro) {
            printf("No hay boletos Oro disponibles.\n");
            cat = 0;
            continue;
        }
        
        switch (cat)
        {
        case 1:
            strcpy(nuevo.tipo, "Basico");
            nuevo.precio = prebas;
            intentos = 1;
            contBasicos++;
            break;
        case 2:
            strcpy(nuevo.tipo, "Premium");
            nuevo.precio = preprem;
            intentos = 3;
            contPremium++;
            break;
        case 3:
            strcpy(nuevo.tipo, "Oro");
            nuevo.precio = preoro;
            intentos = 5;
            contOro++;
            break;
        default:
            printf("Opcion no valida. Intente de nuevo.\n");
        }
    } while (cat < 1 || cat > 3);
    
    nuevo.catnum = intentos;
    nuevo.premioGanado = 0.0;
    
    // Selección de números del tablero
    for (int i = 0; i < intentos; i++) {
        mostrarTblr();
        int numSeleccionado;
        
        printf("Intento %d/%d\n", i+1, intentos);
        printf("Premio acumulado hasta ahora: $%.2f\n", nuevo.premioGanado);
        do
        {
            printf("Seleccione un numero del tablero (1-%d): ", tamtab);
            if (scanf("%d", &numSeleccionado) != 1 || numSeleccionado < 1 || numSeleccionado > tamtab)
            {
                printf("Numero invalido. Intente de nuevo.\n");
                limpbuf();
                continue;
            }
            
            if (tablero[numSeleccionado - 1] != 0) {
                printf("Ese numero ya fue seleccionado. Intente con otro.\n");
                continue;
            }
            
            break;
        } while (1);
        
        tablero[numSeleccionado - 1] = 1;
        nuevo.numbol[i] = numSeleccionado;
        
        if (premios[numSeleccionado - 1] > 0) {
            printf("¡Felicidades! Ha ganado $%.2f en esta casilla.\n", premios[numSeleccionado - 1]);
            nuevo.premioGanado += premios[numSeleccionado - 1];
        } else {
            printf("No hay premio en esta casilla.\n");
        }
    }

    genCod(nuevo.cod);
    bltsVend[totBlts++] = nuevo;
    fondRec += nuevo.precio;
    totalPremios += nuevo.premioGanado;

    printf("\nDatos registrados:\n");
    printf("Nombre: %s\n", nuevo.nom);
    printf("Domicilio: %s\n", nuevo.dom);
    printf("Categoria de boleto: %s\n", nuevo.tipo);
    printf("Codigo asignado: %s\n", nuevo.cod);
    printf("Precio: $%.2f\n", nuevo.precio);
    
    printf("Numeros seleccionados del tablero: ");
    for (int i = 0; i < nuevo.catnum; i++) {
        printf("%d ", nuevo.numbol[i]);
    }
    printf("\n");
    
    printf("Premio total ganado: $%.2f\n", nuevo.premioGanado);
}

// Función para consultar los boletos vendidos
void consulBltsVend()
{
    printf("\n=== Consulta de boletos vendidos ===\n");
    if (totBlts == 0)
    {
        printf("No se han vendido boletos aun.\n");
        return;
    }
    printf("\n -----------------------------------------------------------------------------\n");
    printf("| %-20s | %-20s | %-5s | %-7s |\n", "Nombre", "Domicilio", "Codigo", "Tipo");
    printf(" -----------------------------------------------------------------------------\n");
    for (int i = 0; i < totBlts; i++)
    {
        printf("| %-20s | %-20s | %-5s | %-7s |\n",
               bltsVend[i].nom, bltsVend[i].dom,
               bltsVend[i].cod, bltsVend[i].tipo);
    }
    printf(" -----------------------------------------------------------------------------\n");
    printf("Total de boletos vendidos: %d\n", totBlts);
    printf("Boletos Basicos: %d/%d | Premium: %d/%d | Oro: %d/%d\n", 
           contBasicos, maxBasicos, contPremium, maxPremium, contOro, maxOro);
}

// Función para consultar los premios ganados
void consulPremios()
{
    printf("\n=== Consulta de premios ganados ===\n");
    if (totBlts == 0) {
        printf("No se han entregado premios aun.\n");
        return;
    }
    
    printf("\n -----------------------------------------------------------------------------\n");
    printf("| %-20s | %-5s | %-10s | %-7s |\n", "Nombre", "Codigo", "Tipo", "Premio");
    printf(" -----------------------------------------------------------------------------\n");
    
    for (int i = 0; i < totBlts; i++) {
        printf("| %-20s | %-5s | %-10s | $%-7.2f |\n",
               bltsVend[i].nom, bltsVend[i].cod,
               bltsVend[i].tipo, bltsVend[i].premioGanado);
    }
    printf(" -----------------------------------------------------------------------------\n");
    printf("Total de premios entregados: $%.2f\n", totalPremios);
}

// Función para mostrar los fondos recaudados
void fondosRecaudados() {
    printf("\n=== Fondos recaudados ===\n");
    if (totBlts == 0) {
        printf("No se han vendido boletos aun.\n");
        return;
    }
    
    printf("\n ----------------------------------------------------------------------\n");
    printf("| %-5s | %-10s | %-9s | %-8s | %-8s |\n", 
           "Codigo", "Tipo", "Inversion", "Premio", "Ganancia");
    printf(" ----------------------------------------------------------------------\n");
    
    float totalInversion = 0.0;
    float totalGanancia = 0.0;
    
    for (int i = 0; i < totBlts; i++) {
        float inversion = bltsVend[i].precio;
        float premio = bltsVend[i].premioGanado;
        float ganancia = inversion - premio;
        
        totalInversion += inversion;
        totalGanancia += ganancia;
        
        printf("| %-5s | %-10s | $%-8.2f | $%-7.2f | $%-8.2f |\n",
               bltsVend[i].cod, bltsVend[i].tipo,
               inversion, premio, ganancia);
    }
    
    printf(" ----------------------------------------------------------------------\n");
    printf("| %-28s | $%-8.2f | $%-7.2f | $%-8.2f |\n", 
           "Total:", totalInversion, totalPremios, totalGanancia);
    printf(" ----------------------------------------------------------------------\n");
    
    if (totalGanancia < 0) {
        printf("\n*Se reporta PÉRDIDA\n");
    } else {
        printf("\n*Se reporta GANANCIA\n");
    }
}

// Función para configuración
void configuracion() {
    int opcion;
    do {
        printf("\n=== Configuracion ===\n");
        printf("1. Participantes\n");
        printf("2. Costos\n");
        printf("3. Volver al menu principal\n");
        printf("Seleccione una opcion: ");
        scanf("%d", &opcion);
        
        switch(opcion) {
            case 1:
                printf("\n=== Configuracion de Participantes ===\n");
                printf("Configuracion actual:\n");
                printf("Boletos Basicos: %d\n", maxBasicos);
                printf("Boletos Premium: %d\n", maxPremium);
                printf("Boletos Oro: %d\n", maxOro);
                
                printf("\nIngrese el numero maximo de boletos Basicos: ");
                scanf("%d", &maxBasicos);
                printf("Ingrese el numero maximo de boletos Premium: ");
                scanf("%d", &maxPremium);
                printf("Ingrese el numero maximo de boletos Oro: ");
                scanf("%d", &maxOro);
                
                printf("Configuracion guardada.\n");
                break;
            case 2:
                printf("\n=== Configuracion de Costos ===\n");
                printf("Configuracion actual:\n");
                printf("Boleto Basico: $%.2f\n", prebas);
                printf("Boleto Premium: $%.2f\n", preprem);
                printf("Boleto Oro: $%.2f\n", preoro);
                
                printf("\nIngrese el costo del boleto Basico: $");
                scanf("%f", &prebas);
                printf("Ingrese el costo del boleto Premium: $");
                scanf("%f", &preprem);
                printf("Ingrese el costo del boleto Oro: $");
                scanf("%f", &preoro);
                
                printf("Configuracion guardada.\n");
                break;
            case 3:
                printf("Volviendo al menu principal...\n");
                break;
            default:
                printf("Opcion no valida. Intente de nuevo.\n");
        }
    } while (opcion != 3);
}

// Función para reiniciar el tablero
void reiniciarTablero() {
    printf("\n¿Desea reiniciar el tablero del sorteo? (1: Si, 0: No): ");
    int opcion;
    scanf("%d", &opcion);
    
    if (opcion == 1) {
        // Reiniciar tablero
        for (int i = 0; i < tamtab; i++) {
            tablero[i] = 0;
        }
        
        // Reinicializar premios
        iniPre();
        
        printf("Tablero reiniciado exitosamente.\n");
    }
}

// Función principal del programa
int main()
{
    srand(time(NULL));
    iniPre();
    
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
        printf("6. Reiniciar tablero\n");
        printf("7. Salir\n");
        printf("Seleccione una opcion: ");
        scanf("%d", &opc);
        
        switch (opc)
        {
        case 1:
            ventaBlts();
            break;
        case 2:
            consulBltsVend();
            break;
        case 3:
            consulPremios();
            break;
        case 4:
            fondosRecaudados();
            break;
        case 5:
            configuracion();
            break;
        case 6:
            reiniciarTablero();
            break;
        case 7:
            printf("Saliendo del programa...\n");
            break;
        default:
            printf("Opcion no valida. Intente de nuevo.\n");
        }
    } while (opc != 7);
    return 0;
}