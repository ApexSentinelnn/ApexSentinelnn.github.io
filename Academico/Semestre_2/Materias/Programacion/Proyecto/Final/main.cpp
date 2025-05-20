#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>  // Se agregó para usar fabs()

// Colores ANSI
#define RESET "\033[0m"
#define ROC "\033[31m"
#define VERD "\033[32m"
#define AMAR "\033[33m"
#define AZUL "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN "\033[36m"
#define BOLD "\033[1m"

// Valores
#define MAXBOL 100 // Maximo de boletos
#define TAMTAB 25  // Tamano del tablero
#define PRENUM 10  // Numero de premios ocultos
//File para guardar datos para el publico
#define FILENAME "Datos_P.txt"
//file para guardar datos para el administrador
#define FILENAME_ADMIN "Datos_A.txt"
// Contraseña para configuraciones
#define PASSWORD_FILE "password.txt"
// Contraseña por defecto
char PASSWORD[30] = "12345"; // Contrasena para configuraciones

    time_t tiempoActual;
    struct tm *infoTiempo;


// Precios configurables
float preBas = 25.0;
float prePrem = 50.0;
float preOro = 100.0;

// Estructura de boleto
typedef struct {
    char nom[50];       // Nombre del comprador
    char dom[100];      // Domicilio
    char cod[6];        // Codigo unico
    char tipo[10];
    float precio;       // Precio del boleto
    int numbol[5];      // Numeros seleccionados
    int catnum;         // Intentos permitidos
    int tablero[TAMTAB];// Tablero del jugador
    float premioGanado; // Premio ganado
    char horaVenta[40];      // Tipo de boleto

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
    printf("\n" BOLD "|============================================================|\n" RESET);
    printf(BOLD "|               Matriculas de Estudiantes                    |\n" RESET);
    printf(BOLD "|============================================================|\n" RESET);
    printf(BOLD "| %-10s | %-45s |\n" RESET, "Matricula", "Nombre");
    printf(BOLD "|------------|-----------------------------------------------|\n|" RESET);
    printf(VERD " 187855     " RESET); printf(BOLD "|" RESET); printf(VERD " Castillo Gaytan Noe                          " RESET);printf(BOLD " |\n|" RESET);
    printf(VERD " 187339     " RESET); printf(BOLD "|" RESET); printf(VERD " TRISTAN CONTRERAS DAVID ALEJANDRO            " RESET);printf(BOLD " |\n" RESET);
    printf(BOLD "|============================================================|\n" RESET);
}

//codigo unico para el boleto
void genCod(char *cod) {
    for (int i = 0; i < 5; i++) {
        cod[i] = (char)('A' + rand() % 26); // Conversión
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
            premiosGlobales[pos] = (float)(5.0 + (rand() % 50) * 5.0); // Conversión
        }
    }
}

//tablero del jugador
void mosTabJug(int tablero[]) {
    printf("\n" CYAN "\n--- Tu tablero ---\n" RESET);
    for (int i = 0; i < TAMTAB; i++) {
        if (i % 5 == 0) printf("\n");
        if (tablero[i] == 1)
            printf(ROC "[XX] " RESET); // Casilla seleccionada
        else
            printf(VERD "[%2d] " RESET, i + 1); // Casilla disponible
    }
    printf("\n");
}

// Función auxiliar para leer cadenas entre comillas
void leerCadenaConComillas(FILE* archivo, char* destino, int tamano) {
    char temp[500] = {0};
    if (fgets(temp, sizeof(temp), archivo) != NULL) {
        // Si el string empieza con comillas, quitarlas
        if (temp[0] == '"') {
            int len = strlen(temp);
            if (len > 2 && temp[len-2] == '"') {
                strncpy(destino, temp + 1, len - 3);
                destino[len - 3] = '\0';
            } else {
                strncpy(destino, temp, tamano - 1);
                destino[strcspn(destino, "\n")] = 0;
            }
        } else {
            strncpy(destino, temp, tamano - 1);
            destino[strcspn(destino, "\n")] = 0;
        }
    } else {
        destino[0] = '\0';
    }
}

// Guardar datos al archivo en formato de tabla
void guardarDatos() {
    // Guardar datos para el público con formato mejorado
    FILE *archivoPublico = fopen(FILENAME, "w");
    if (archivoPublico == NULL) {
        printf(AMAR "Error al abrir el archivo para guardar datos publicos.\n" RESET);
        return;
    }

    // Cabecera para lectura humana
    fprintf(archivoPublico, "╔═══════════════════════════════════════════════════════════════════╗\n");
    fprintf(archivoPublico, "║                     SISTEMA DE SORTEO OFICIAL                     ║\n");
    fprintf(archivoPublico, "╚═══════════════════════════════════════════════════════════════════╝\n\n");

    // Sección de configuración de precios
    fprintf(archivoPublico, "╔══════════════════════ CONFIGURACIÓN DE PRECIOS ═══════════════════╗\n");
    fprintf(archivoPublico, "║                                                                   ║\n");
    fprintf(archivoPublico, "║  ◆ Básico:  $%.2f                                                 ║\n", preBas);
    fprintf(archivoPublico, "║  ◆ Premium: $%.2f                                                 ║\n", prePrem);
    fprintf(archivoPublico, "║  ◆ Oro:     $%.2f                                                 ║\n", preOro);
    fprintf(archivoPublico, "║                                                                   ║\n");
    fprintf(archivoPublico, "╚═══════════════════════════════════════════════════════════════════╝\n\n");

    // Sección de premios ocultos
    fprintf(archivoPublico, "╔════════════════════════ PREMIOS DISPONIBLES ════════════════════════╗\n");
    fprintf(archivoPublico, "║                                                                     ║\n");
    fprintf(archivoPublico, "║  Posición  |  Premio ($)                                            ║\n");
    fprintf(archivoPublico, "║  ----------|------------                                            ║\n");

    int hayPremios = 0;
    for (int i = 0; i < TAMTAB; i++) {
        if (premiosGlobales[i] > 0) {
            fprintf(archivoPublico, "║  %-9d |  %-9.2f                                            ║\n", i+1, premiosGlobales[i]);
            hayPremios = 1;
        }
    }

    if (!hayPremios) {
        fprintf(archivoPublico, "║     No hay premios configurados actualmente                      ║\n");
    }

    fprintf(archivoPublico, "║                                                                     ║\n");
    fprintf(archivoPublico, "╚═════════════════════════════════════════════════════════════════════╝\n\n");

    // Sección de fondos
    // Calcular totales de ingresos y premios
    float totalIngresos = 0.0;
    float totalPremios = 0.0;
    for (int i = 0; i < totBlts; i++) {
        totalIngresos += bltsVend[i].precio;
        totalPremios += bltsVend[i].premioGanado;
    }
    float totalGanancia = totalIngresos - totalPremios;

    fprintf(archivoPublico, "╔═══════════════════════ FONDOS RECAUDADOS ════════════════════════╗\n");
    fprintf(archivoPublico, "║                                                                   ║\n");
    fprintf(archivoPublico, "║  Total ventas:   $%.2f                                            ║\n", totalIngresos);
    fprintf(archivoPublico, "║  Total premios:  $%.2f                                            ║\n", totalPremios);
    fprintf(archivoPublico, "║  Balance final:  $%.2f %s                                 ║\n",
            fabs(totalGanancia), (totalGanancia < 0 ? "(DÉFICIT)" : "(GANANCIA)"));
    fprintf(archivoPublico, "║                                                                   ║\n");
    fprintf(archivoPublico, "╚═══════════════════════════════════════════════════════════════════╝\n\n");

    // Sección de boletos vendidos
    fprintf(archivoPublico, "╔═══════════════════════ BOLETOS VENDIDOS: %d ═══════════════════════╗\n", totBlts);

    if (totBlts > 0) {
        fprintf(archivoPublico, "║                                                                      |                            ║\n");
        fprintf(archivoPublico, "║  ID | Código  | Nombre                | Tipo    | Precio  | Premio   | Fecha                      ║\n");
        fprintf(archivoPublico, "║ ----|---------|-----------------------|---------|---------|----------|----------------------------║\n");

        for (int i = 0; i < totBlts; i++) {
            Blt b = bltsVend[i];
            fprintf(archivoPublico, "║ %2d | %-7s | %-20s | %-7s | %7.2f | %7.2f | %-30s ║\n",
                    i+1, b.cod, b.nom, b.tipo, b.precio, b.premioGanado, b.horaVenta);
        }
        fprintf(archivoPublico, "║                                                                   ║\n");
    } else {
        fprintf(archivoPublico, "║                                                                   ║\n");
        fprintf(archivoPublico, "║            No hay boletos vendidos actualmente                    ║\n");
        fprintf(archivoPublico, "║                                                                   ║\n");
    }

    fprintf(archivoPublico, "╚═══════════════════════════════════════════════════════════════════╝\n\n");

    // Pie de página

    char fechaHora[50];

    time(&tiempoActual);
    infoTiempo = localtime(&tiempoActual);
    strftime(fechaHora, sizeof(fechaHora), "%d/%m/%Y %H:%M:%S", infoTiempo);

    fprintf(archivoPublico, "Reporte generado: %s\n", fechaHora);
    fprintf(archivoPublico, "© Sistema de Sorteo (Tu suerte apremia) - Todos los derechos reservados\n");

    fclose(archivoPublico);

    // Guardar datos técnicos para el administrador
    FILE *archivoT = fopen(FILENAME_ADMIN, "w");
    if (archivoT == NULL) {
        printf(AMAR "Error al abrir el archivo para guardar datos tecnicos.\n" RESET);
        return;
    }

    fprintf(archivoT, "###DATOS_TECNICOS###\n");

    // Guardar configuración
    fprintf(archivoT, "CONFIG\n");
    fprintf(archivoT, "%.2f %.2f %.2f\n", preBas, prePrem, preOro);

    // Guardar premios globales
    fprintf(archivoT, "PREMIOS\n");
    for (int i = 0; i < TAMTAB; i++) {
        fprintf(archivoT, "%.2f ", premiosGlobales[i]);
    }
    fprintf(archivoT, "\n");

    // Guardar información de boletos
    fprintf(archivoT, "BOLETOS\n");
    fprintf(archivoT, "%d\n", totBlts);

    for (int i = 0; i < totBlts; i++) {
        //  strings con comillas para  problemas con espacios
        fprintf(archivoT, "\"%s\"\n", bltsVend[i].nom);
        fprintf(archivoT, "\"%s\"\n", bltsVend[i].dom);
        fprintf(archivoT, "\"%s\"\n", bltsVend[i].cod);
        fprintf(archivoT, "\"%s\"\n", bltsVend[i].tipo);

        fprintf(archivoT, "%.2f\n", bltsVend[i].precio);
        fprintf(archivoT, "%d\n", bltsVend[i].catnum);


        //  números seleccionados
        for (int j = 0; j < bltsVend[i].catnum; j++) {
            fprintf(archivoT, "%d ", bltsVend[i].numbol[j]);
        }
        fprintf(archivoT, "\n");

        //  tablero
        for (int j = 0; j < TAMTAB; j++) {
            fprintf(archivoT, "%d ", bltsVend[i].tablero[j]);
        }
        fprintf(archivoT, "\n");

        fprintf(archivoT, "%.2f\n", bltsVend[i].premioGanado);

    fprintf(archivoT, "\"%s\"\n", bltsVend[i].horaVenta);
    }


    //  fondos
    fprintf(archivoT, "FONDOS\n");
    fprintf(archivoT, "%.2f\n", fondRec);

    fclose(archivoT);

    //  contraseña en archivo separado
    FILE *passFile = fopen(PASSWORD_FILE, "w");
    if (passFile != NULL) {
        fprintf(passFile, "%s", PASSWORD);
        fclose(passFile);
    } else {
        printf(AMAR "Error al guardar la contrasena.\n" RESET);
    }

    printf(CYAN "Todos los datos guardados correctamente.\n" RESET);
}

// Cargar datos
void cargarDatos() {
    FILE *passFile = fopen(PASSWORD_FILE, "r");
    if (passFile != NULL) {
        if (fgets(PASSWORD, sizeof(PASSWORD), passFile) != NULL) {
            PASSWORD[strcspn(PASSWORD, "\n")] = 0;
            printf(CYAN "Contrasena cargada correctamente.\n" RESET);
        } else {
            printf(ROC "Error al leer la contrasena.\n" RESET);
        }
        fclose(passFile);
    } else {
        printf(CYAN "No se encontro archivo de contrasena. Se usara la contrasena predeterminada.\n" RESET);
    }

    FILE *archivoT = fopen(FILENAME_ADMIN, "r");
    if (archivoT == NULL) {
        printf(CYAN "No se encontro archivo de datos tecnicos. Se creara uno nuevo al guardar.\n");
        return;
    }

    char buffer[500];

    if (fgets(buffer, sizeof(buffer), archivoT) == NULL || strcmp(buffer, "###DATOS_TECNICOS###\n") != 0) {
        printf(AMAR "Error: Formato de archivo invalido.\n" RESET);
        fclose(archivoT);
        return;
    }

    // Leer configuración
    if (fgets(buffer, sizeof(buffer), archivoT) == NULL || strcmp(buffer, "CONFIG\n") != 0) {
        printf(AMAR "Error: Formato de configuración invalido.\n" RESET);
        fclose(archivoT);
        return;
    }

    if (fscanf(archivoT, "%f %f %f\n", &preBas, &prePrem, &preOro) != 3) {
        printf(AMAR "Error al leer la configuracion de precios.\n" RESET);
        fclose(archivoT);
        return;
    }

    // Leer premios globales
    if (fgets(buffer, sizeof(buffer), archivoT) == NULL || strcmp(buffer, "PREMIOS\n") != 0) {
        printf(AMAR "Error: Formato de premios invalido.\n" RESET);
        fclose(archivoT);
        return;
    }

    for (int i = 0; i < TAMTAB; i++) {
        if (fscanf(archivoT, "%f", &premiosGlobales[i]) != 1) {
            printf(AMAR "Error al leer los premios globales.\n" RESET);
            fclose(archivoT);
            return;
        }
    }
    fscanf(archivoT, "\n");

    // Leer boletos
    if (fgets(buffer, sizeof(buffer), archivoT) == NULL || strcmp(buffer, "BOLETOS\n") != 0) {
        printf(AMAR "Error: Formato de boletos invalido.\n" RESET);
        fclose(archivoT);
        return;
    }

    if (fscanf(archivoT, "%d\n", &totBlts) != 1) {
        printf(AMAR "Error al leer el total de boletos.\n" RESET);
        fclose(archivoT);
        return;
    }

    for (int i = 0; i < totBlts; i++) {
        // Leer nombre
        leerCadenaConComillas(archivoT, bltsVend[i].nom, sizeof(bltsVend[i].nom));

        // Leer domicilio
        leerCadenaConComillas(archivoT, bltsVend[i].dom, sizeof(bltsVend[i].dom));

        // Leer código
        leerCadenaConComillas(archivoT, bltsVend[i].cod, sizeof(bltsVend[i].cod));

        // Leer tipo
        leerCadenaConComillas(archivoT, bltsVend[i].tipo, sizeof(bltsVend[i].tipo));

        // Leer precio
        if (fscanf(archivoT, "%f\n", &bltsVend[i].precio) != 1) {
            printf(AMAR "Error al leer el precio del boleto %d.\n" RESET, i+1);
            fclose(archivoT);
            return;
        }

        // Leer cantidad de números
        if (fscanf(archivoT, "%d\n", &bltsVend[i].catnum) != 1) {
            printf(AMAR "Error al leer la cantidad de numeros del boleto %d.\n" RESET, i+1);
            fclose(archivoT);
            return;
        }

        // Leer números seleccionados
        for (int j = 0; j < bltsVend[i].catnum; j++) {
            if (fscanf(archivoT, "%d", &bltsVend[i].numbol[j]) != 1) {
                printf(AMAR "Error al leer los numeros seleccionados del boleto %d.\n" RESET, i+1);
                fclose(archivoT);
                return;
            }
        }
        fscanf(archivoT, "\n");

        // Leer tablero
        for (int j = 0; j < TAMTAB; j++) {
            if (fscanf(archivoT, "%d", &bltsVend[i].tablero[j]) != 1) {
                printf(AMAR "Error al leer el tablero del boleto %d.\n" RESET, i+1);
                fclose(archivoT);
                return;
            }
        }
        fscanf(archivoT, "\n");

        // Leer premio ganado
        if (fscanf(archivoT, "%f\n", &bltsVend[i].premioGanado) != 1) {
            printf(AMAR "Error al leer el premio ganado del boleto %d.\n" RESET, i+1);
            fclose(archivoT);
            return;
        }

        // Leer Hora venta
       // fprintf(archivoT, "\"%s\"\n", bltsVend[i].horaVenta);
       leerCadenaConComillas(archivoT, bltsVend[i].horaVenta, sizeof(bltsVend[i].horaVenta));
    }

    // Leer fondos recaudados
    if (fgets(buffer, sizeof(buffer), archivoT) == NULL || strcmp(buffer, "FONDOS\n") != 0) {
        printf(AMAR "Error: Formato de fondos invalido.\n" RESET);
        fclose(archivoT);
        return;
    }

    if (fscanf(archivoT, "%f\n", &fondRec) != 1) {
        printf(AMAR "Error al leer los fondos recaudados.\n" RESET);
        fclose(archivoT);
        return;
    }

    fclose(archivoT);
    printf(CYAN "Datos tecnicos cargados correctamente.\n" RESET);
}

// Verificar contraseña
int verificarPassword() {
    char pass[20];
    printf("Ingrese la contrasena para acceder a configuraciones: ");
    scanf("%s", pass);
    if (strcmp(pass, PASSWORD) == 0) {
        printf(CYAN "Acceso concedido.\n" RESET);
        return 1;
    } else {
        printf(ROC "Contrasena incorrecta. Acceso denegado.\n" RESET);
        return 0;
    }
}

// Realiza la venta de boletos
void ventaBlts() {
    if (totBlts >= MAXBOL) {
        printf(AMAR "Ya no hay mas boletos disponibles.\n" RESET);
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

    time(&tiempoActual);
    infoTiempo = localtime(&tiempoActual);
    strftime(nuevo.horaVenta, sizeof(nuevo.horaVenta), "%d/%m/%Y %H:%M:%S", infoTiempo);

    int cat;
    do {
        printf("Seleccione categoria:\n");
        printf("1. Basico (%.2f)\n2. Premium (%.2f)\n3. Oro (%.2f)\n", preBas, prePrem, preOro);
        printf("Opcion: ");
        if (scanf("%d", &cat) != 1) {
            limpbuf();
            printf(ROC "Entrada invalida.\n" RESET);
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
                printf(ROC "Opcion no valida.\n" RESET);
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
                printf(ROC "Numero invalido.\n" RESET);
                continue;
            }
            if (nuevo.tablero[sel - 1] == 1) {
                printf(ROC "Ya seleccionaste ese numero.\n" RESET);
                continue;
            }
            break;
        } while (1);

        nuevo.tablero[sel - 1] = 1;
        nuevo.numbol[i] = sel;

        float premio = premiosGlobales[sel - 1];
        if (premio > 0) {
            printf("Ganaste: ");printf(MAGENTA " $%.2f\n" RESET, premio);
            nuevo.premioGanado += premio;
        } else {
            printf(AMAR " Sin premio en esta casilla.\n" RESET);
        }
    }

    genCod(nuevo.cod);
    bltsVend[totBlts++] = nuevo;
    fondRec += nuevo.precio;

    printf(CYAN "\nRegistro completo.\nCodigo: %s\n" RESET, nuevo.cod);
    printf("Premio total ganado:"); printf(MAGENTA " $%.2f\n" RESET, nuevo.premioGanado);

    // Guardar datos actualizados
    guardarDatos();
}

// Consulta boletos vendidos
void consulBltsVend() {



    if (totBlts == 0) {
        printf(AMAR "No hay boletos vendidos.\n" RESET);
        return;
    }


    printf("\n\n---------------------------------------------------------------------------------------\n");
    printf("|                           CONSULTA BOLETOS VENDIDOS                                 |");
    printf("\n|-------------------------------------------------------------------------------------|");
    printf("\n| %-5s | %-15s | %-15s | %-5s | %-7s | %-20s |\n", "ID", "Nombre", "Domicilio", "Codigo", "Tipo", "Fecha");
    printf("|-------|-----------------|-----------------|--------|---------|----------------------|\n");
    for (int i = 0; i < totBlts; i++) {
        printf("| %-5d | %-15s | %-14s  | %-6s | %-7s | %-20s |\n", i+1,
               bltsVend[i].nom, bltsVend[i].dom, bltsVend[i].cod, bltsVend[i].tipo, bltsVend[i].horaVenta);
    }
    printf("---------------------------------------------------------------------------------------\n");
}

// Consulta premios ganados
void conPre() {
    if (totBlts == 0) {
        printf(AMAR "No hay boletos vendidos.\n" RESET);
        return;
    }
    printf("\n\n--------------------------------------------------------\n");
    printf("|              CONSULTA PREMIOS GANADOS                |\n");
    printf("|------------------------------------------------------|");
    printf("\n| %-5s | %-15s | %-5s | %-7s | Premio  |\n", "ID", "Nombre", "Codigo", "Tipo");
    printf("|-------|-----------------|--------|---------|---------|\n");
    for (int i = 0; i < totBlts; i++) {
        printf("| %-5d | %-15s | %-6s | %-7s | $%6.2f |\n", i+1,
               bltsVend[i].nom, bltsVend[i].cod,
               bltsVend[i].tipo, bltsVend[i].premioGanado);
    }
    printf("--------------------------------------------------------\n");
}

// Muestra fondos recaudados
void FonRec() {
    if (totBlts == 0) {
        printf(AMAR "No hay boletos vendidos.\n" RESET);
        return;
    }

    float totalIngresos = 0.0;
    float totalPremios = 0.0;
    printf("-------------------------------------------------------------\n");
    printf("|                CONSULTA FONDOS RECAUDADOS                 |\n");
    printf("|-----------------------------------------------------------|");
    printf("\n| %-5s | %-6s | %-8s | %-9s | %-6s | %-8s |\n", "ID", "Codigo", "Tipo", "Inversion", "Premio", "Ganancia");
    printf("|-----------------------------------------------------------|\n");
    for (int i = 0; i < totBlts; i++) {
        float gan = bltsVend[i].precio - bltsVend[i].premioGanado;
        totalIngresos += bltsVend[i].precio;
        totalPremios += bltsVend[i].premioGanado;

        printf("| %-5d | %-6s | %-8s | %9.2f | %6.2f | %8.2f |\n", i+1,
               bltsVend[i].cod, bltsVend[i].tipo,
               bltsVend[i].precio, bltsVend[i].premioGanado, gan);
    }
    printf("-------------------------------------------------------------\n");

    float totalGanancia = totalIngresos - totalPremios;
    printf("Total de ventas: %.2f\n", totalIngresos);
    printf("Total de premios: %.2f\n", totalPremios);
    printf("Balance total:"); printf(MAGENTA " %.2f (%s)\n" RESET, totalGanancia,
           (totalGanancia < 0 ? "PERDIDA" : "GANANCIA"));
}

// Eliminar un boleto
void eliminarBoleto() {
    if (totBlts == 0) {
        printf(AMAR "No hay boletos que eliminar.\n" RESET);
        return;
    }

    // Mostrar lista de boletos
    consulBltsVend();

    int id;
    printf("\nIngrese el ID del boleto a eliminar (1-%d): ", totBlts);


    if (scanf("%d", &id) < 1 || id > totBlts){
        limpbuf();
        printf(ROC "ID invalido.\n" RESET);
        return;
                }

    /*scanf("%d", &id);

    if (id < 1 || id > totBlts) {
        printf("ID invalido.\n");
        return;
    }*/

    int idx = id - 1;

    // Pedir confirmación
    char conf;
    printf("\n¿Esta seguro que desea eliminar el boleto con codigo %s a nombre de %s? (S/N): ",
           bltsVend[idx].cod, bltsVend[idx].nom);

    getchar(); // Limpiar buffer
    scanf("%c", &conf);

    if (conf != 'S' && conf != 's') {
        printf(ROC "Operacion cancelada.\n" RESET);
        return;
    }

    // Actualizar fondos recaudados
    fondRec -= bltsVend[idx].precio;

    printf(CYAN "Boleto con codigo %s a nombre de %s eliminado.\n" RESET,
           bltsVend[idx].cod, bltsVend[idx].nom);

    // Desplazar elementos para eliminar
    for (int i = idx; i < totBlts - 1; i++) {
        bltsVend[i] = bltsVend[i + 1];
    }

    totBlts--;

    // Guardar datos actualizados
    guardarDatos();
}

// Config del sistema
void Config() {
    // Verificar contraseña
    if (!verificarPassword()) {
        return;
    }

    int opcion;
    float Or_bas,Or_Prem,Or_Oro;





    do {
        printf("\n--- Config ---\n");
        printf("1. Cambiar precios\n");
        printf("2. Cambiar contrasena\n");
        printf("3. Reiniciar todo (boletos y fondo)\n");
        printf("4. Eliminar boleto\n");
        printf("5. Guardar datos\n");
        printf("6. Cargar datos\n");
        printf("7. Volver al menu\n");
        printf("Opcion: ");
        if (scanf("%d",&opcion) != 1){
            printf(ROC "Entrada invalida. Ingrese un numero.\n" RESET);
            int cc;
            while ((cc = getchar()) != '\n' && cc != EOF);
            opcion = 0;
        }else{
            switch (opcion) {
            case 1:

               printf("\n--- Precio actual|| Basico: %.2f || Premium: %.2f || Oro: %.2f  ---\n",preBas,prePrem,preOro);
                printf("Nuevo precio Basico: ");
                Or_bas=preBas;
                Or_Prem=prePrem;
                Or_Oro=preOro;

                if (scanf("%f", &preBas) !=1){
                    limpbuf();
                    printf(ROC "Precio invalido.\n" RESET);

                    break;

                }

                printf("Nuevo precio Premium: ");
                if (scanf("%f", &prePrem) !=1){
                    preBas=Or_bas;

                    limpbuf();
                    printf(ROC "Precio invalido.\n" RESET);

                    break;
                }


                printf("Nuevo precio Oro: ");
                if (scanf("%f", &preOro) !=1){
                        preBas=Or_bas;
                        prePrem=Or_Prem;

                    limpbuf();


                    printf(ROC "Precio invalido.\n" RESET);

                    break;
                }


                printf(CYAN "...Precios actualizados...\n" RESET);

                guardarDatos();
                break;
            case 2:
                printf("Nueva contrasena: ");
                limpbuf();
                fgets(PASSWORD, sizeof(PASSWORD), stdin);
                PASSWORD[strcspn(PASSWORD, "\n")] = 0;
                printf(CYAN "Contrasena actualizada.\n" RESET);
                guardarDatos();
                break;
            case 3:
                char conf;
                printf("¿Esta seguro de reiniciar TODO el sistema? (S/N): ");
                getchar();
                scanf("%c", &conf);
                if (conf == 'S' || conf == 's') {
                    totBlts = 0;
                    fondRec = 0;
                    iniPglob();
                    printf(CYAN "Sistema reiniciado completamente.\n" RESET);
                    guardarDatos();
                } else {
                    printf(ROC "Operacion cancelada.\n" RESET);
                }
                break;
            case 4:
                eliminarBoleto();
                break;
            case 5:
                guardarDatos();
                break;
            case 6:
                printf("¿Esta seguro de cargar datos del archivo? Los datos actuales podrian perderse. (S/N): ");
                getchar();
                scanf("%c", &conf);
                if (conf == 'S' || conf == 's') {
                    cargarDatos();
                } else {
                    printf(ROC "Operacion cancelada.\n" RESET);
                }
                break;
            case 7:
                return;
            default:
                printf(ROC "Opcion no valida.\n" RESET);
            }
        }
    } while (opcion != 7);
}

// Menu principal
void casos() {
    int opc;
    do {
        iniPglob(); // Inicializa premios
        printf("\n\n====================== SISTEMA DE SORTEO ======================\n");
        printf("Bienvenido al sistema de sorteos.\n");
        printf("\n--- MENU SORTEO ---\n");
        printf("1. Venta de boletos\n");
        printf("2. Consulta de boletos vendidos\n");
        printf("3. Consulta de premios ganados\n");
        printf("4. Fondos recaudados\n");
        printf("5. Config\n");
        printf("6. Salir\n");
        printf("Opcion: ");
        if (scanf("%d",&opc) != 1){
            printf(ROC "Entrada invalida. Ingrese un numero.\n" RESET);
            int c;
            while ((c = getchar()) != '\n' && c != EOF);
            opc = 0;
        }else{
            switch (opc) {
            case 1: ventaBlts(); break;
            case 2: consulBltsVend(); break;
            case 3: conPre(); break;
            case 4: FonRec(); break;
            case 5: Config(); break;
            case 6: printf(CYAN "Guardando datos y saliendo...\n" RESET); guardarDatos(); break;
            default: printf(ROC "Opcion no valida.\n" RESET);
        }
        }
    } while (opc != 6);
}

// Funcion principal
int main() {
    srand(time(NULL)); // Inicializa semilla para numeros aleatorios
    iniPglob(); // Inicializa premios
    cargarDatos(); // Carga datos existentes
    impMat(); // Muestra informacion de matriculas
    casos(); // Llama al menu principal
    return 0;
}
