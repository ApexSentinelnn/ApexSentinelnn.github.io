#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_BOLETOS 100
#define MAX_CASILLAS 25

typedef struct {
    char nombre[50];
    char domicilio[100];
    char codigo[6];
    char tipoBoleto[10];
    float premio;
} Boleto;

Boleto boletosVendidos[MAX_BOLETOS];
int totalBoletos = 0;
float premios[MAX_CASILLAS];
int tablero[MAX_CASILLAS];

void generarCodigo(char *codigo) {
    for (int i = 0; i < 5; i++) {
        codigo[i] = 'A' + rand() % 26;
    }
    codigo[5] = '\0';
}

void inicializarTablero() {
    for (int i = 0; i < MAX_CASILLAS; i++) {
        tablero[i] = 0;
        premios[i] = (rand() % 50) * 5.0;
    }
    for (int i = 0; i < 10; i++) {
        tablero[rand() % MAX_CASILLAS] = 1;
    }
}

void ventaBoletos() {
    if (totalBoletos >= MAX_BOLETOS) {
        printf("No hay más boletos disponibles.\n");
        return;
    }

    Boleto nuevo;
    printf("Ingrese nombre: ");
    scanf(" %[^]", nuevo.nombre);
    printf("Ingrese domicilio: ");
    scanf(" %[^]", nuevo.domicilio);
    generarCodigo(nuevo.codigo);
    printf("Código generado: %s\n", nuevo.codigo);
    
    printf("Seleccione tipo de boleto (Basico, Premium, Oro): ");
    scanf(" %s", nuevo.tipoBoleto);
    nuevo.premio = 0.0;
    
    inicializarTablero();
    int intentos = (strcmp(nuevo.tipoBoleto, "Oro") == 0) ? 5 : (strcmp(nuevo.tipoBoleto, "Premium") == 0) ? 3 : 1;
    
    for (int i = 0; i < intentos; i++) {
        int casilla;
        printf("Seleccione una casilla (0-24): ");
        scanf("%d", &casilla);
        if (casilla >= 0 && casilla < MAX_CASILLAS) {
            if (tablero[casilla]) {
                printf("¡Ganaste $%.2f!\n", premios[casilla]);
                nuevo.premio += premios[casilla];
                tablero[casilla] = 0;
            } else {
                printf("Casilla vacía.\n");
            }
        } else {
            printf("Casilla inválida. Intente de nuevo.\n");
        }
    }
    
    boletosVendidos[totalBoletos++] = nuevo;
}

void consultaBoletosVendidos() {
    printf("\n=== Boletos Vendidos ===\n");
    printf("Nombre\tDomicilio\tCódigo\tTipo\n");
    for (int i = 0; i < totalBoletos; i++) {
        printf("%s\t%s\t%s\t%s\n", boletosVendidos[i].nombre, boletosVendidos[i].domicilio, boletosVendidos[i].codigo, boletosVendidos[i].tipoBoleto);
    }
}

void consultaPremiosGanados() {
    printf("\n=== Premios Entregados ===\n");
    printf("Nombre\tCódigo\tTipo\tPremio\n");
    for (int i = 0; i < totalBoletos; i++) {
        if (boletosVendidos[i].premio > 0)
            printf("%s\t%s\t%s\t%.2f\n", boletosVendidos[i].nombre, boletosVendidos[i].codigo, boletosVendidos[i].tipoBoleto, boletosVendidos[i].premio);
    }
}

void fondosRecaudados() {
    printf("\n=== Fondos Recaudados ===\n");
    printf("Código\tTipo\tInversión\tPremio\tGanancia\n");
    float total = 0;
    for (int i = 0; i < totalBoletos; i++) {
        float costo = (strcmp(boletosVendidos[i].tipoBoleto, "Oro") == 0) ? 100 : (strcmp(boletosVendidos[i].tipoBoleto, "Premium") == 0) ? 50 : 25;
        float ganancia = costo - boletosVendidos[i].premio;
        total += ganancia;
        printf("%s\t%s\t%.2f\t%.2f\t%.2f\n", boletosVendidos[i].codigo, boletosVendidos[i].tipoBoleto, costo, boletosVendidos[i].premio, ganancia);
    }
    printf("Total: %.2f\n", total);
}

int main() {
    srand(time(NULL));
    int opcion;
    do {
        printf("\n===== SISTEMA DE SORTEO =====\n");
        printf("1. Venta de boletos\n");
        printf("2. Consulta de boletos vendidos\n");
        printf("3. Consulta de premios ganados\n");
        printf("4. Fondos recaudados\n");
        printf("5. Salir\n");
        printf("Seleccione una opción: ");
        scanf("%d", &opcion);
        
        switch(opcion) {
            case 1: ventaBoletos(); break;
            case 2: consultaBoletosVendidos(); break;
            case 3: consultaPremiosGanados(); break;
            case 4: fondosRecaudados(); break;
            case 5: printf("Saliendo del programa...\n"); break;
            default: printf("Opción no válida. Intente de nuevo.\n");
        }
    } while(opcion != 5);
    
    return 0;
}
