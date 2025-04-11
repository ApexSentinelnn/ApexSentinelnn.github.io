#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>

// Definiciones de constantes
#define maxbol 100      // Máximo número de boletos
#define tamtab 25       // Tamaño del tablero
#define prenum 10       // Número de premios

// Precios de los boletos (configurables)
float prebas = 25.0;
float preprem = 50.0;
float preoro = 100.0;

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
    float premio;        // Premio acumulado
} Blt;

// Variables globales
Blt bltsVend[maxbol];
int totBlts = 0;
int tablero[tamtab] = {0};
float premios[tamtab] = {0};
float fondRec = 0.0;

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
    printf("+-----+-----+-----+-----+-----+\n");
    for (int i = 0; i < tamtab; i++)
    {
        if (i % 5 == 0 && i != 0)
        {
            printf("|\n+-----+-----+-----+-----+-----+\n");
        }
        if (tablero[i] == 0)
        {
            printf("|%3d ", i + 1);
        }
        else
        {
            if (premios[i] > 0)
            {
                printf("|$%3.0f", premios[i]);
            }
            else
            {
                printf("| XX ");
            }
        }
    }
    printf("|\n+-----+-----+-----+-----+-----+\n");
}

// Función para generar un código aleatorio de boleto
void genCod(char *cod)
{
    const char letras[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    int usadas[26] = {0};
    
    for (int i = 0; i < 5; i++)
    {
        int idx;
        do {
            idx = rand() % 26;
        } while (usadas[idx]);
        
        cod[i] = letras[idx];
        usadas[idx] = 1;
    }
    cod[5] = '\0';
}

// Función para inicializar los premios aleatoriamente
void iniPre()
{
    int posicionesPremiadas[prenum] = {0};
    int posicion, i = 0;
    
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
            premios[posicion] = 5.0 + ((rand() % 50) * 5.0);
            i++;
        }
    }
}

// Función para validar entrada numérica
int validarEntradaNumerica(const char *mensaje, int min, int max) {
    int valor;
    while (1) {
        printf("%s", mensaje);
        if (scanf("%d", &valor) != 1) {
            printf("Entrada inválida. Debe ser un número.\n");
            limpbuf();
            continue;
        }
        if (valor < min || valor > max) {
            printf("Error: El valor debe estar entre %d y %d.\n", min, max);
            continue;
        }
        break;
    }
    return valor;
}

// Función para la venta de boletos
void ventaBlts()
{
    if (totBlts >= maxbol)
    {
        printf("No hay más boletos disponibles.\n");
        return;
    }

    Blt nuevo;
    nuevo.premio = 0.0; // Inicializar premio acumulado

    printf("\n=== Venta de boletos ===\n");
    
    // Validación de nombre (no vacío)
    do {
        printf("Ingrese su nombre: ");
        limpbuf();
        fgets(nuevo.nom, sizeof(nuevo.nom), stdin);
        nuevo.nom[strcspn(nuevo.nom, "\n")] = 0;
        if(strlen(nuevo.nom) == 0) {
            printf("Error: El nombre no puede estar vacío.\n");
        }
    } while(strlen(nuevo.nom) == 0);
    
    // Validación de domicilio (no vacío)
    do {
        printf("Ingrese su domicilio: ");
        fgets(nuevo.dom, sizeof(nuevo.dom), stdin);
        nuevo.dom[strcspn(nuevo.dom, "\n")] = 0;
        if(strlen(nuevo.dom) == 0) {
            printf("Error: El domicilio no puede estar vacío.\n");
        }
    } while(strlen(nuevo.dom) == 0);

    int cat;
    do
    {
        printf("\nSeleccione la categoria del boleto:\n");
        printf("1. Basico ($%.2f) - 1 intento\n", prebas);
        printf("2. Premium ($%.2f) - 3 intentos\n", preprem);
        printf("3. Oro ($%.2f) - 5 intentos\n", preoro);
        printf("4. Cancelar y volver al menú\n");
        
        cat = validarEntradaNumerica("Ingrese el número de la opción: ", 1, 4);
        
        if (cat == 4) {
            printf("Operación cancelada.\n");
            return;
        }

        switch (cat)
        {
        case 1:
            strcpy(nuevo.tipo, "Basico");
            nuevo.precio = prebas;
            nuevo.catnum = 1;
            break;
        case 2:
            strcpy(nuevo.tipo, "Premium");
            nuevo.precio = preprem;
            nuevo.catnum = 3;
            break;
        case 3:
            strcpy(nuevo.tipo, "Oro");
            nuevo.precio = preoro;
            nuevo.catnum = 5;
            break;
        default:
            printf("Opción no válida. Intente de nuevo.\n");
        }
    } while (cat < 1 || cat > 3);
    
    // Selección de números del tablero
    for (int i = 0; i < nuevo.catnum; i++) {
        mostrarTblr();
        printf("Intento %d/%d\n", i+1, nuevo.catnum);
        
        int numSeleccionado;
        do {
            numSeleccionado = validarEntradaNumerica(
                "Seleccione un número del tablero (1-25): ", 1, tamtab);
            
            if (tablero[numSeleccionado - 1] != 0) {
                printf("Ese número ya fue seleccionado. Intente con otro.\n");
                continue;
            }
            
            break;
        } while (1);
        
        tablero[numSeleccionado - 1] = 1;
        nuevo.numbol[i] = numSeleccionado;
        
        if (premios[numSeleccionado - 1] > 0) {
            printf("¡Felicidades! Ha ganado $%.2f en esta casilla.\n", 
                   premios[numSeleccionado - 1]);
            nuevo.premio += premios[numSeleccionado - 1];
        } else {
            printf("No hay premio en esta casilla.\n");
        }
    }

    genCod(nuevo.cod);
    bltsVend[totBlts++] = nuevo;
    fondRec += nuevo.precio;

    printf("\n=== Resumen del boleto ===\n");
    printf("Nombre: %s\n", nuevo.nom);
    printf("Domicilio: %s\n", nuevo.dom);
    printf("Categoria de boleto: %s\n", nuevo.tipo);
    printf("Codigo asignado: %s\n", nuevo.cod);
    printf("Precio: $%.2f\n", nuevo.precio);
    printf("Premio acumulado: $%.2f\n", nuevo.premio);
    
    printf("Números seleccionados: ");
    for (int i = 0; i < nuevo.catnum; i++) {
        printf("%d ", nuevo.numbol[i]);
    }
    printf("\n");
}

// Función para consultar los boletos vendidos
void consulBltsVend()
{
    printf("\n=== Consulta de boletos vendidos ===\n");
    if (totBlts == 0)
    {
        printf("No se han vendido boletos aún.\n");
        return;
    }
    
    printf("\n ---------------------------------------------------------------------------\n");
    printf("| %-20s | %-30s | %-6s | %-8s |\n", "Nombre", "Domicilio", "Código", "Tipo");
    printf(" ---------------------------------------------------------------------------\n");
    
    for (int i = 0; i < totBlts; i++)
    {
        printf("| %-20s | %-30s | %-6s | %-8s |\n",
               bltsVend[i].nom, bltsVend[i].dom,
               bltsVend[i].cod, bltsVend[i].tipo);
    }
    printf(" ---------------------------------------------------------------------------\n");
    printf("Total de boletos vendidos: %d\n", totBlts);
}

// Función para consultar los premios ganados
void consulPremios()
{
    printf("\n=== Consulta de premios ganados ===\n");
    if (totBlts == 0)
    {
        printf("No se han vendido boletos aún.\n");
        return;
    }
    
    printf("\n -------------------------------------------------------------\n");
    printf("| %-20s | %-6s | %-8s | %-10s |\n", "Nombre", "Código", "Tipo", "Premio");
    printf(" -------------------------------------------------------------\n");
    
    for (int i = 0; i < totBlts; i++)
    {
        printf("| %-20s | %-6s | %-8s | $%-9.2f |\n",
               bltsVend[i].nom, bltsVend[i].cod, 
               bltsVend[i].tipo, bltsVend[i].premio);
    }
    printf(" -------------------------------------------------------------\n");
    
    float totalPremios = 0.0;
    for (int i = 0; i < totBlts; i++) {
        totalPremios += bltsVend[i].premio;
    }
    printf("Total de premios entregados: $%.2f\n", totalPremios);
}

// Función para mostrar fondos recaudados
void mostrarFondos()
{
    printf("\n=== Fondos recaudados ===\n");
    if (totBlts == 0)
    {
        printf("No se han vendido boletos aún.\n");
        return;
    }
    
    printf("\n ----------------------------------------------------------------------\n");
    printf("| %-6s | %-8s | %-10s | %-10s | %-10s |\n", 
           "Código", "Tipo", "Inversión", "Premio", "Ganancia");
    printf(" ----------------------------------------------------------------------\n");
    
    float totalInversion = 0.0;
    float totalPremios = 0.0;
    
    for (int i = 0; i < totBlts; i++)
    {
        float ganancia = bltsVend[i].precio - bltsVend[i].premio;
        
        printf("| %-6s | %-8s | $%-9.2f | $%-9.2f | $%-9.2f |\n",
               bltsVend[i].cod, bltsVend[i].tipo,
               bltsVend[i].precio, bltsVend[i].premio, ganancia);
        
        totalInversion += bltsVend[i].precio;
        totalPremios += bltsVend[i].premio;
    }
    
    float gananciaTotal = totalInversion - totalPremios;
    printf(" ----------------------------------------------------------------------\n");
    printf("| TOTAL: %45s $%-9.2f |\n", "", gananciaTotal);
    printf(" ----------------------------------------------------------------------\n");
    
    if (gananciaTotal < 0) {
        printf("* Se reporta PÉRDIDA\n");
    } else {
        printf("* Se reporta GANANCIA\n");
    }
}

// Función para configuración del sistema
void configuracion()
{
    int opc;
    do {
        printf("\n=== Configuración ===\n");
        printf("1. Participantes (límite de boletos por categoría)\n");
        printf("2. Costos de boletos\n");
        printf("3. Volver al menú principal\n");
        
        opc = validarEntradaNumerica("Seleccione una opción: ", 1, 3);
        
        switch(opc) {
            case 1:
                printf("\nConfiguración de participantes:\n");
                printf("Actualmente se permite un máximo de %d boletos en total.\n", maxbol);
                // Aquí se podría implementar la modificación de límites
                break;
            case 2: {
                printf("\nConfiguración de costos actual:\n");
                printf("1. Categoría Básica: $%.2f\n", prebas);
                printf("2. Categoría Premium: $%.2f\n", preprem);
                printf("3. Categoría Oro: $%.2f\n", preoro);
                
                int opcCosto;
                do {
                    opcCosto = validarEntradaNumerica(
                        "Seleccione categoría a modificar (1-3) o 4 para cancelar: ", 1, 4);
                    
                    if (opcCosto == 4) break;
                    
                    float nuevoPrecio;
                    printf("Ingrese nuevo precio para categoría %d: ", opcCosto);
                    scanf("%f", &nuevoPrecio);
                    
                    if (nuevoPrecio <= 0) {
                        printf("El precio debe ser mayor que cero.\n");
                        continue;
                    }
                    
                    switch(opcCosto) {
                        case 1: prebas = nuevoPrecio; break;
                        case 2: preprem = nuevoPrecio; break;
                        case 3: preoro = nuevoPrecio; break;
                    }
                    printf("Precio actualizado correctamente.\n");
                    break;
                } while (1);
                break;
            }
            case 3:
                printf("Volviendo al menú principal...\n");
                break;
        }
    } while(opc != 3);
}

// Función principal
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
        printf("5. Configuración\n");
        printf("6. Salir\n");
        
        opc = validarEntradaNumerica("Seleccione una opción: ", 1, 6);
        
        switch(opc)
        {
            case 1: ventaBlts(); break;
            case 2: consulBltsVend(); break;
            case 3: consulPremios(); break;
            case 4: mostrarFondos(); break;
            case 5: configuracion(); break;
            case 6: printf("Saliendo del programa...\n"); break;
        }
    } while(opc != 6);
    
    return 0;
}