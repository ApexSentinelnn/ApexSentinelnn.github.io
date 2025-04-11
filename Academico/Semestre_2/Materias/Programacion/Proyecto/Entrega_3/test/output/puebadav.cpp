#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

#define MAX_BOLETOS 100
#define CODIGO_LENGTH 6
#define MAX_CASILLAS 25
#define CONTRASENA "hola"

typedef struct {
    char nombre[50];
    char domicilio[100];
    char codigo[CODIGO_LENGTH];
    char tipoBoleto[10];
    int intentos;
    float inversion;
    float premioGanado;
} Boleto;

Boleto boletos[MAX_BOLETOS];
int totalBoletos = 0;

int maxBoletosBasico = 100, maxBoletosPremium = 100, maxBoletosOro = 100;
int vendidosBasico = 0, vendidosPremium = 0, vendidosOro = 0;

float costoBasico = 10.0, costoPremium = 25.0, costoOro = 50.0;

void generarCodigo(char *codigo) {
    const char caracteres[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    for (int i = 0; i < CODIGO_LENGTH - 1; i++) {
        codigo[i] = caracteres[rand() % (sizeof(caracteres) - 1)];
    }
    codigo[CODIGO_LENGTH - 1] = '\0';
}

void limpiarBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int validarNumero(int min, int max) {
    int numero;
    while (scanf("%d", &numero) != 1 || numero < min || numero > max) {
        printf("Entrada no valida. Ingrese un numero entre %d y %d: ", min, max);
        limpiarBuffer();
    }
    return numero;
}

void venderBoleto() {
    if (totalBoletos >= MAX_BOLETOS) {
        printf("\nSe ha alcanzado el limite de boletos vendidos.\n");
        return;
    }

    Boleto nuevoBoleto;
    printf("\nIngrese nombre del participante: ");
    limpiarBuffer();
    fgets(nuevoBoleto.nombre, sizeof(nuevoBoleto.nombre), stdin);
    nuevoBoleto.nombre[strcspn(nuevoBoleto.nombre, "\n")] = '\0';

    printf("Ingrese domicilio del participante: ");
    fgets(nuevoBoleto.domicilio, sizeof(nuevoBoleto.domicilio), stdin);
    nuevoBoleto.domicilio[strcspn(nuevoBoleto.domicilio, "\n")] = '\0';

    generarCodigo(nuevoBoleto.codigo);

    printf("\nSeleccione la categoria del boleto:\n");
    printf("1) Basico (1 intento)\n");
    printf("2) Premium (3 intentos)\n");
    printf("3) Oro (5 intentos)\n");
    printf("Ingrese opcion: ");
    int categoria = validarNumero(1, 3);

    switch (categoria) {
        case 1:
            if (vendidosBasico >= maxBoletosBasico) {
                printf("No hay boletos Basico disponibles.\n");
                return;
            }
            strcpy(nuevoBoleto.tipoBoleto, "Basico");
            nuevoBoleto.intentos = 1;
            nuevoBoleto.inversion = costoBasico;
            vendidosBasico++;
            break;
        case 2:
            if (vendidosPremium >= maxBoletosPremium) {
                printf("No hay boletos Premium disponibles.\n");
                return;
            }
            strcpy(nuevoBoleto.tipoBoleto, "Premium");
            nuevoBoleto.intentos = 3;
            nuevoBoleto.inversion = costoPremium;
            vendidosPremium++;
            break;
        case 3:
            if (vendidosOro >= maxBoletosOro) {
                printf("No hay boletos Oro disponibles.\n");
                return;
            }
            strcpy(nuevoBoleto.tipoBoleto, "Oro");
            nuevoBoleto.intentos = 5;
            nuevoBoleto.inversion = costoOro;
            vendidosOro++;
            break;
    }

    int tablero[MAX_CASILLAS] = {0};
    for (int i = 0; i < 10; i++) {
        int pos;
        do {
            pos = rand() % MAX_CASILLAS;
        } while (tablero[pos] != 0);
        tablero[pos] = 5 + rand() % 246;
    }

    int casilla, intentosRealizados = 0;
    float acumulado = 0;
    while (intentosRealizados < nuevoBoleto.intentos) {
        printf("\nIntento %d de %d - Ingrese una casilla (1-25): ", intentosRealizados + 1, nuevoBoleto.intentos);
        casilla = validarNumero(1, 25);
        casilla--;

        if (tablero[casilla] == -1) {
            printf("Casilla ya descubierta. Elija otra.\n");
            continue;
        }

        acumulado += tablero[casilla];
        printf("Obtuvo: $%.2f\n", (float)tablero[casilla]);
        tablero[casilla] = -1;
        intentosRealizados++;
    }

    nuevoBoleto.premioGanado = acumulado;
    boletos[totalBoletos++] = nuevoBoleto;

    printf("\nBoleto registrado con exito!\nCodigo: %s | Categoria: %s | Intentos: %d\n",
           nuevoBoleto.codigo, nuevoBoleto.tipoBoleto, nuevoBoleto.intentos);
}

void consultarBoletos() {
    printf("\n%-20s %-30s %-10s %-10s\n", "Nombre", "Domicilio", "Codigo", "Tipo");
    for (int i = 0; i < totalBoletos; i++) {
        printf("%-20s %-30s %-10s %-10s\n",
               boletos[i].nombre, boletos[i].domicilio, boletos[i].codigo, boletos[i].tipoBoleto);
    }
}

void consultarPremios() {
    printf("\n%-20s %-10s %-10s %-10s\n", "Nombre", "Codigo", "Tipo", "Premio");
    for (int i = 0; i < totalBoletos; i++) {
        printf("%-20s %-10s %-10s $%-9.2f\n",
               boletos[i].nombre, boletos[i].codigo, boletos[i].tipoBoleto, boletos[i].premioGanado);
    }
}

void fondosRecaudados() {
    printf("\n4) Fondos recaudados:\n");
    printf("En esta opcion, se presenta un desglose de la inversion realizada por el participante y el premio entregado. La informacion se muestra en la siguiente tabla:\n\n");

    printf("%-10s %-15s %-12s %-10s %-10s\n", "Codigo", "Tipo de boleto", "Inversion", "Premio", "Ganancia");
    printf("---------------------------------------------------------------\n");

    float totalGanancia = 0.0;

    for (int i = 0; i < totalBoletos; i++) {
        float ganancia = boletos[i].premioGanado - boletos[i].inversion;
        totalGanancia += ganancia;

        printf("%-10s %-15s $%-10.2f $%-8.2f %-10.2f\n",
               boletos[i].codigo,
               boletos[i].tipoBoleto,
               boletos[i].inversion,
               boletos[i].premioGanado,
               ganancia);
    }

    printf("---------------------------------------------------------------\n");
    printf("%-38s Total: %-10.2f\n", "", totalGanancia);

    if (totalGanancia < 0)
        printf("\n*Se reporta PERDIDA\n");
    else if (totalGanancia > 0)
        printf("\n*Se reporta GANANCIA\n");
    else
        printf("\n*Sin ganancia ni perdida\n");
}

void configuracion() {
    int opcion;
    do {
        printf("\n--- Configuracion ---\n");
        printf("1) Limite de boletos por categoria\n");
        printf("2) Costo por categoria\n");
        printf("3) Volver al menu\n");
        printf("Selecciona una opcion: ");
        opcion = validarNumero(1, 3);
        switch (opcion) {
            case 1:
                printf("Maximo boletos Basico: "); maxBoletosBasico = validarNumero(1, 1000);
                printf("Maximo boletos Premium: "); maxBoletosPremium = validarNumero(1, 1000);
                printf("Maximo boletos Oro: "); maxBoletosOro = validarNumero(1, 1000);
                break;
            case 2:
                printf("Costo Basico: "); scanf("%f", &costoBasico);
                printf("Costo Premium: "); scanf("%f", &costoPremium);
                printf("Costo Oro: "); scanf("%f", &costoOro);
                break;
        }
    } while (opcion != 3);
}

void mostrarMenu() {
    int opcion;
    char clave[20];

    do {
        printf("\n====================================\n");
        printf("           LUNDY SORTEO            \n");
        printf("====================================\n");
        printf("1) Venta de boletos\n");
        printf("2) Consulta de boletos vendidos\n");
        printf("3) Consulta de premios ganados\n");
        printf("4) Fondos recaudados\n");
        printf("5) Configuracion\n");
        printf("6) Salir del sorteo\n");
        printf("Selecciona una opcion: ");
        opcion = validarNumero(1, 6);

        switch(opcion) {
            case 1: {
                int continuar;
                do {
                    venderBoleto();
                    printf("\n¿Desea comprar otro boleto? (1 = Si / 0 = No): ");
                    continuar = validarNumero(0, 1);
                } while (continuar == 1);
                break;
            }
            case 2: consultarBoletos(); break;
            case 3: consultarPremios(); break;
            case 4: fondosRecaudados(); break;
            case 5:
                printf("Ingresa la contraseña de administrador: ");
                limpiarBuffer();
                fgets(clave, sizeof(clave), stdin);
                clave[strcspn(clave, "\n")] = '\0';

                if (strcmp(clave, CONTRASENA) == 0) {
                    configuracion();
                } else {
                    printf("Contrasena incorrecta. Acceso denegado.\n");
                }
                break;
            case 6: printf("Saliendo...\n"); break;
        }
    } while (opcion != 6);
}

int main() {
    srand(time(NULL));
    mostrarMenu();
    return 0;
}
