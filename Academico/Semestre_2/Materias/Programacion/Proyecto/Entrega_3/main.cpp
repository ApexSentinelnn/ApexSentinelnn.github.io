#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#define MAXBOL 100 // Maximo de boletos
#define TAMTAB 25  // Tamano del tablero
#define PRENUM 10  // Numero de premios ocultos

// Precios configurables
float preBas = 25.0;
float prePrem = 50.0;
float preOro = 100.0;

// Estructura de boleto
typedef struct {
    char nom[50];       // Nombre del comprador
    char dom[100];      // Domicilio
    char cod[6];        // Codigo unico
    char tipo[10];      // Tipo de boleto
    float precio;       // Precio del boleto
    int numbol[5];      // Numeros seleccionados
    int catnum;         // Intentos permitidos
    int tablero[TAMTAB];// Tablero del jugador
    float premioGanado; // Premio ganado
} Blt;

// Variables globales
Blt bltsVend[MAXBOL];   // Lista de boletos vendidos
int totBlts = 0;        // Total de boletos vendidos
float premiosGlobales[TAMTAB] = {0}; // Premios ocultos
float fondRec = 0.0;    // Fondos recaudados

// Limpia el buffer de entrada
void limpbuf() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// Imprime informacion de matriculas
void impMat() {
    printf("\n|==============================================|\n");
    printf("|         Matriculas de estudiantes            |\n");
    printf("|==============================================|\n");
    printf("| 187855 | Castillo Gaytan Noe                 |\n");
    printf("| 187339 | Tristan Contreras David Alejandro   |\n");
    printf("|==============================================|\n");
}

// Genera un codigo unico para el boleto
void genCod(char *cod) {
    for (int i = 0; i < 5; i++) {
        cod[i] = 'A' + rand() % 26;
    }
    cod[5] = '\0';
}

// Inicializa los premios ocultos en el tablero
void iniPglob() {
    for (int i = 0; i < TAMTAB; i++) premiosGlobales[i] = 0.0;

    int usados[PRENUM] = {0}, i = 0;
    while (i < PRENUM) {
        int pos = rand() % TAMTAB;
        int repetido = 0;
        for (int j = 0; j < i; j++) {
            if (usados[j] == pos) {
                repetido = 1;
                break;
            }
        }
        if (!repetido) {
            usados[i++] = pos;
            premiosGlobales[pos] = 5.0 + (rand() % 50) * 5.0; // Premios aleatorios
        }
    }
}

// Muestra el tablero del jugador
void mosTabJug(int tablero[]) {
    printf("\n--- Tu tablero ---\n");
    for (int i = 0; i < TAMTAB; i++) {
        if (i % 5 == 0) printf("\n");
        if (tablero[i] == 1)
            printf("[XX] "); // Casilla seleccionada
        else
            printf("[%2d] ", i + 1); // Casilla disponible
    }
    printf("\n");
}

// Realiza la venta de boletos
void ventaBlts() {
    if (totBlts >= MAXBOL) {
        printf("Ya no hay mas boletos disponibles.\n");
        return;
    }

    Blt nuevo;
    int intentos = 0;

    getchar();
    printf("Ingrese su nombre: ");
    fgets(nuevo.nom, sizeof(nuevo.nom), stdin);
    nuevo.nom[strcspn(nuevo.nom, "\n")] = 0;

    printf("Ingrese su domicilio: ");
    fgets(nuevo.dom, sizeof(nuevo.dom), stdin);
    nuevo.dom[strcspn(nuevo.dom, "\n")] = 0;

    int cat;
    do {
        printf("Seleccione categoria:\n");
        printf("1. Basico (%.2f)\n2. Premium (%.2f)\n3. Oro (%.2f)\n", preBas, prePrem, preOro);
        printf("Opcion: ");
        if (scanf("%d", &cat) != 1) {
            limpbuf();
            printf("Entrada invalida.\n");
            continue;
        }

        switch (cat) {
            case 1:
                strcpy(nuevo.tipo, "Basico");
                nuevo.precio = preBas;
                intentos = 1;
                break;
            case 2:
                strcpy(nuevo.tipo, "Premium");
                nuevo.precio = prePrem;
                intentos = 3;
                break;
            case 3:
                strcpy(nuevo.tipo, "Oro");
                nuevo.precio = preOro;
                intentos = 5;
                break;
            default:
                printf("Opcion no valida.\n");
                cat = 0;
        }
    } while (cat == 0);

    nuevo.catnum = intentos;
    nuevo.premioGanado = 0.0;
    for (int i = 0; i < TAMTAB; i++) nuevo.tablero[i] = 0;

    for (int i = 0; i < intentos; i++) {
        mosTabJug(nuevo.tablero);
        printf("Intento %d/%d\n", i + 1, intentos);
        int sel;
        do {
            printf("Seleccione numero (1-%d): ", TAMTAB);
            if (scanf("%d", &sel) != 1 || sel < 1 || sel > TAMTAB) {
                limpbuf();
                printf("Numero invalido.\n");
                continue;
            }
            if (nuevo.tablero[sel - 1] == 1) {
                printf("Ya seleccionaste ese numero.\n");
                continue;
            }
            break;
        } while (1);

        nuevo.tablero[sel - 1] = 1;
        nuevo.numbol[i] = sel;

        float premio = premiosGlobales[sel - 1];
        if (premio > 0) {
            printf("¡Ganaste $%.2f!\n", premio);
            nuevo.premioGanado += premio;
        } else {
            printf("Sin premio en esta casilla.\n");
        }
    }

    genCod(nuevo.cod);
    bltsVend[totBlts++] = nuevo;
    fondRec += nuevo.precio;

    printf("\nRegistro completo.\nCodigo: %s\n", nuevo.cod);
    printf("Premio total ganado: $%.2f\n", nuevo.premioGanado);
}

// Consulta boletos vendidos
void consulBltsVend() {
    if (totBlts == 0) {
        printf("No hay boletos vendidos.\n");
        return;
    }

    printf("\n| %-15s | %-15s | %-5s | %-7s |\n", "Nombre", "Domicilio", "Codigo", "Tipo");
    printf("-----------------------------------------------------------\n");
    for (int i = 0; i < totBlts; i++) {
        printf("| %-15s | %-15s | %-5s | %-7s |\n",
               bltsVend[i].nom, bltsVend[i].dom, bltsVend[i].cod, bltsVend[i].tipo);
    }
}

// Consulta premios ganados
void conPre() {
    printf("\n| %-15s | %-5s | %-7s | Premio |\n", "Nombre", "Codigo", "Tipo");
    printf("---------------------------------------------\n");
    for (int i = 0; i < totBlts; i++) {
        printf("| %-15s | %-5s | %-7s | $%.2f |\n",
               bltsVend[i].nom, bltsVend[i].cod,
               bltsVend[i].tipo, bltsVend[i].premioGanado);
    }
}

// Muestra fondos recaudados
void FonRec() {
    float totalGanancia = 0.0;
    printf("\n| Codigo | Tipo   | Inversion | Premio | Ganancia |\n");
    printf("-----------------------------------------------------\n");
    for (int i = 0; i < totBlts; i++) {
        float gan = bltsVend[i].precio - bltsVend[i].premioGanado;
        totalGanancia += gan;
        printf("| %-6s | %-6s | %9.2f | %6.2f | %8.2f |\n",
               bltsVend[i].cod, bltsVend[i].tipo,
               bltsVend[i].precio, bltsVend[i].premioGanado, gan);
    }
    printf("-----------------------------------------------------\n");
    printf("Total: %.2f (%s)\n", totalGanancia,
           (totalGanancia < 0 ? "PERDIDA" : "GANANCIA"));
}

// Config del sistema
void Config() {
    int opcion;
    do {
        printf("\n--- Config ---\n");
        printf("1. Cambiar precios\n");
        printf("2. Reiniciar premios ocultos\n");
        printf("3. Reiniciar todo (boletos y fondo)\n");
        printf("4. Volver al menu\n");
        printf("Opcion: ");
        scanf("%d", &opcion);
        switch (opcion) {
            case 1:
                printf("Nuevo precio Basico: "); scanf("%f", &preBas);
                printf("Nuevo precio Premium: "); scanf("%f", &prePrem);
                printf("Nuevo precio Oro: "); scanf("%f", &preOro);
                printf("Precios actualizados.\n");
                break;
            case 2:
                iniPglob();
                printf("Premios ocultos reiniciados.\n");
                break;
            case 3:
                totBlts = 0;
                fondRec = 0;
                for (int i = 0; i < TAMTAB; i++) premiosGlobales[i] = 0;
                printf("Sistema reiniciado completamente.\n");
                break;
            case 4:
                return;
            default:
                printf("Opcion no valida.\n");
        }
    } while (opcion != 4);
}

// Menu principal
void casos() {
    int opc;
    do {
        printf("\n--- MENU SORTEO ---\n");
        printf("1. Venta de boletos\n");
        printf("2. Consulta de boletos vendidos\n");
        printf("3. Consulta de premios ganados\n");
        printf("4. Fondos recaudados\n");
        printf("5. Config\n");
        printf("6. Salir\n");
        printf("Opcion: ");
        scanf("%d", &opc);
        switch (opc) {
            case 1: ventaBlts(); break;
            case 2: consulBltsVend(); break;
            case 3: conPre(); break;
            case 4: FonRec(); break;
            case 5: Config(); break;
            case 6: printf("Saliendo...\n"); break;
            default: printf("Opcion no valida.\n");
        }
    } while (opc != 6);
}

// Funcion principal
int main() {
    srand(time(NULL)); // Inicializa semilla para numeros aleatorios
    iniPglob(); // Inicializa premios
    impMat(); // Muestra informacion de matriculas
    casos(); // Llama al menu principal
    return 0;
}