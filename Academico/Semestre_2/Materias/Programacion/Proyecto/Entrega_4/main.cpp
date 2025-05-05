#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

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
    printf("\n" BOLD "|============================================================|\n" RESET);
    printf(BOLD "|                     Matriculas de Estudiantes              |\n" RESET);
    printf(BOLD "|============================================================|\n" RESET);
    printf(AZUL "| %-10s | %-40s |\n" RESET, "Matricula", "Nombre");
    printf(AZUL "|------------|------------------------------------------|\n" RESET);
    printf(AZUL "| %-10s | %-40s |\n" RESET, "187855", "Castillo Gaytan Noe");
    printf(AZUL "| %-10s | %-40s |\n" RESET, "187339", "Tristan Contreras David Alejandro");
    printf(BOLD "|============================================================|\n" RESET);
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
    printf("\n" CYAN "--- Tu tablero ---\n" RESET);
    for (int i = 0; i < TAMTAB; i++) {
        if (i % 5 == 0) printf("\n");
        if (tablero[i] == 1)
            printf(ROC "[XX] " RESET); // Casilla seleccionada
        else
            printf(VERD "[%2d] " RESET, i + 1); // Casilla disponible
    }
    printf("\n");
}

// Guardar datos al archivo en formato de tabla
void guardarDatos() {
    // Guardar datos para el público
    FILE *archivoPublico = fopen(FILENAME, "w");
    if (archivoPublico == NULL) {
        printf("Error al abrir el archivo para guardar datos públicos.\n");
        return;
    }

    // Cabecera para lectura humana
    fprintf(archivoPublico, "====================== SISTEMA DE SORTEO ======================\n\n");
    
    // Guardar configuración de precios
    fprintf(archivoPublico, "=== CONFIGURACION DE PRECIOS ===\n");
    fprintf(archivoPublico, "Basico: %.2f | Premium: %.2f | Oro: %.2f\n\n", preBas, prePrem, preOro);
    
    // Guardar premios globales
    fprintf(archivoPublico, "=== PREMIOS OCULTOS ===\n");
    fprintf(archivoPublico, "Posicion | Premio\n");
    fprintf(archivoPublico, "-----------------\n");
    for (int i = 0; i < TAMTAB; i++) {
        if (premiosGlobales[i] > 0) {
            fprintf(archivoPublico, "%8d | %.2f\n", i+1, premiosGlobales[i]);
        }
    }
    fprintf(archivoPublico, "\n");
    
    // Guardar fondos recaudados
    fprintf(archivoPublico, "=== FONDOS RECAUDADOS ===\n");
    fprintf(archivoPublico, "Total: %.2f (%s)\n\n", fondRec, (fondRec < 0 ? "PERDIDA" : "GANANCIA"));
    
    // Guardar boletos en formato tabla
    fprintf(archivoPublico, "=== BOLETOS VENDIDOS: %d ===\n", totBlts);
    if (totBlts > 0) {
        fprintf(archivoPublico, "ID | Codigo | Nombre                | Tipo    | Precio | Premio  | Ganancia\n");
        fprintf(archivoPublico, "--------------------------------------------------------------------------\n");
        for (int i = 0; i < totBlts; i++) {
            Blt b = bltsVend[i];
            float ganancia = b.precio - b.premioGanado;
            fprintf(archivoPublico, "%-2d | %-6s | %-20s | %-7s | %6.2f | %7.2f | %8.2f\n", 
                    i+1, b.cod, b.nom, b.tipo, b.precio, b.premioGanado, ganancia);
        }
        fprintf(archivoPublico, "\n");
    }
    fclose(archivoPublico);

    // Guardar datos técnicos
    FILE *archivoTecnico = fopen(FILENAME_ADMIN, "w");
    if (archivoTecnico == NULL) {
        printf("Error al abrir el archivo para guardar datos técnicos.\n");
        return;
    }

    fprintf(archivoTecnico, "###DATOS_TECNICOS###\n");
    fprintf(archivoTecnico, "CONFIG\n");
    fprintf(archivoTecnico, "%.2f %.2f %.2f\n", preBas, prePrem, preOro);
    
    fprintf(archivoTecnico, "PREMIOS\n");
    for (int i = 0; i < TAMTAB; i++) {
        fprintf(archivoTecnico, "%.2f ", premiosGlobales[i]);
    }
    fprintf(archivoTecnico, "\n");
    
    fprintf(archivoTecnico, "BOLETOS\n");
    fprintf(archivoTecnico, "%d\n", totBlts);
    
    for (int i = 0; i < totBlts; i++) {
        fprintf(archivoTecnico, "%s\n", bltsVend[i].nom);
        fprintf(archivoTecnico, "%s\n", bltsVend[i].dom);
        fprintf(archivoTecnico, "%s\n", bltsVend[i].cod);
        fprintf(archivoTecnico, "%s\n", bltsVend[i].tipo);
        fprintf(archivoTecnico, "%.2f\n", bltsVend[i].precio);
        fprintf(archivoTecnico, "%d\n", bltsVend[i].catnum);
        
        // Escribir números seleccionados
        for (int j = 0; j < bltsVend[i].catnum; j++) {
            fprintf(archivoTecnico, "%d ", bltsVend[i].numbol[j]);
        }
        fprintf(archivoTecnico, "\n");
        
        // Escribir tablero
        for (int j = 0; j < TAMTAB; j++) {
            fprintf(archivoTecnico, "%d ", bltsVend[i].tablero[j]);
        }
        fprintf(archivoTecnico, "\n");
        
        fprintf(archivoTecnico, "%.2f\n", bltsVend[i].premioGanado);
    }
    
    fprintf(archivoTecnico, "FONDOS\n");
    fprintf(archivoTecnico, "%.2f\n", fondRec);
    fclose(archivoTecnico);

    // Guardar contraseña
    FILE *passFile = fopen(PASSWORD_FILE, "w");
    if (passFile != NULL) {
        fprintf(passFile, "%s\n", PASSWORD);
        fclose(passFile);
    } else {
        printf("Error al guardar la contraseña.\n");
    }
}
// Cargar datos desde el archivo
void cargarDatos() {
    FILE *archivoTecnico = fopen(FILENAME_ADMIN, "r");
    if (archivoTecnico == NULL) {
        printf("No se encontró archivo de datos técnicos. Se creará uno nuevo al guardar.\n");
        return;
    }

    char buffer[200];

    // Leer configuración
    fgets(buffer, sizeof(buffer), archivoTecnico);  // Leer "###DATOS_TECNICOS###"
    fgets(buffer, sizeof(buffer), archivoTecnico);  // Leer "CONFIG"
    fscanf(archivoTecnico, "%f %f %f\n", &preBas, &prePrem, &preOro);

    // Leer premios globales
    fgets(buffer, sizeof(buffer), archivoTecnico);  // Leer "PREMIOS"
    for (int i = 0; i < TAMTAB; i++) {
        fscanf(archivoTecnico, "%f", &premiosGlobales[i]);
    }
    fscanf(archivoTecnico, "\n");

    // Leer boletos
    fgets(buffer, sizeof(buffer), archivoTecnico);  // Leer "BOLETOS"
    fscanf(archivoTecnico, "%d\n", &totBlts);

    for (int i = 0; i < totBlts; i++) {
        fgets(bltsVend[i].nom, sizeof(bltsVend[i].nom), archivoTecnico);
        bltsVend[i].nom[strcspn(bltsVend[i].nom, "\n")] = 0;

        fgets(bltsVend[i].dom, sizeof(bltsVend[i].dom), archivoTecnico);
        bltsVend[i].dom[strcspn(bltsVend[i].dom, "\n")] = 0;

        fgets(bltsVend[i].cod, sizeof(bltsVend[i].cod), archivoTecnico);
        bltsVend[i].cod[strcspn(bltsVend[i].cod, "\n")] = 0;

        fgets(bltsVend[i].tipo, sizeof(bltsVend[i].tipo), archivoTecnico);
        bltsVend[i].tipo[strcspn(bltsVend[i].tipo, "\n")] = 0;

        fscanf(archivoTecnico, "%f\n", &bltsVend[i].precio);
        fscanf(archivoTecnico, "%d\n", &bltsVend[i].catnum);

        // Leer números seleccionados
        for (int j = 0; j < bltsVend[i].catnum; j++) {
            fscanf(archivoTecnico, "%d", &bltsVend[i].numbol[j]);
        }
        fscanf(archivoTecnico, "\n");

        // Leer tablero
        for (int j = 0; j < TAMTAB; j++) {
            fscanf(archivoTecnico, "%d", &bltsVend[i].tablero[j]);
        }
        fscanf(archivoTecnico, "\n");

        fscanf(archivoTecnico, "%f\n", &bltsVend[i].premioGanado);
    }

    // Leer fondos recaudados
    fgets(buffer, sizeof(buffer), archivoTecnico);  // Leer "FONDOS"
    fscanf(archivoTecnico, "%f\n", &fondRec);

    fclose(archivoTecnico);
    printf("Datos técnicos cargados correctamente.\n");

    // Cargar la contraseña desde el archivo
    FILE *passFile = fopen(PASSWORD_FILE, "r");
    if (passFile != NULL) {
        fgets(PASSWORD, sizeof(PASSWORD), passFile);
        PASSWORD[strcspn(PASSWORD, "\n")] = 0; // Eliminar el salto de línea
        fclose(passFile);
        printf("Contraseña cargada correctamente.\n");
    } else {
        printf("Error al cargar la contraseña.\n");
    }
}

// Verificar contraseña
int verificarPassword() {
    char pass[20];
    printf(AMAR "Ingrese la contrasena para acceder a configuraciones: " RESET);
    scanf("%s", pass);
    if (strcmp(pass, PASSWORD) == 0) {
        printf(VERD "Acceso concedido.\n" RESET);
        return 1;
    } else {
        printf(ROC "Contrasena incorrecta. Acceso denegado.\n" RESET);
        return 0;
    }
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
    
    // Guardar datos actualizados
    guardarDatos();
}

// Consulta boletos vendidos
void consulBltsVend() {
    if (totBlts == 0) {
        printf("No hay boletos vendidos.\n");
        return;
    }

    printf("\n| %-5s | %-15s | %-15s | %-5s | %-7s |\n", "ID", "Nombre", "Domicilio", "Codigo", "Tipo");
    printf("----------------------------------------------------------------\n");
    for (int i = 0; i < totBlts; i++) {
        printf("| %-5d | %-15s | %-15s | %-5s | %-7s |\n", i+1,
               bltsVend[i].nom, bltsVend[i].dom, bltsVend[i].cod, bltsVend[i].tipo);
    }
}

// Consulta premios ganados
void conPre() {
    if (totBlts == 0) {
        printf("No hay boletos vendidos.\n");
        return;
    }

    printf("\n| %-5s | %-15s | %-5s | %-7s | Premio |\n", "ID", "Nombre", "Codigo", "Tipo");
    printf("--------------------------------------------------\n");
    for (int i = 0; i < totBlts; i++) {
        printf("| %-5d | %-15s | %-5s | %-7s | $%.2f |\n", i+1,
               bltsVend[i].nom, bltsVend[i].cod,
               bltsVend[i].tipo, bltsVend[i].premioGanado);
    }
}

// Muestra fondos recaudados
void FonRec() {
    if (totBlts == 0) {
        printf("No hay boletos vendidos.\n");
        return;
    }

    float totalIngresos = 0.0;
    float totalPremios = 0.0;
    
    printf("\n| %-5s | %-6s | %-6s | %-9s | %-6s | %-8s |\n", "ID", "Codigo", "Tipo", "Inversion", "Premio", "Ganancia");
    printf("----------------------------------------------------------\n");
    for (int i = 0; i < totBlts; i++) {
        float gan = bltsVend[i].precio - bltsVend[i].premioGanado;
        totalIngresos += bltsVend[i].precio;
        totalPremios += bltsVend[i].premioGanado;
        
        printf("| %-5d | %-6s | %-6s | %9.2f | %6.2f | %8.2f |\n", i+1,
               bltsVend[i].cod, bltsVend[i].tipo,
               bltsVend[i].precio, bltsVend[i].premioGanado, gan);
    }
    printf("----------------------------------------------------------\n");
    
    float totalGanancia = totalIngresos - totalPremios;
    printf("Total de ventas: %.2f\n", totalIngresos);
    printf("Total de premios: %.2f\n", totalPremios);
    printf("Balance total: %.2f (%s)\n", totalGanancia,
           (totalGanancia < 0 ? "PERDIDA" : "GANANCIA"));
}

// Eliminar un boleto
void eliminarBoleto() {
    if (totBlts == 0) {
        printf("No hay boletos que eliminar.\n");
        return;
    }
    
    // Mostrar lista de boletos
    consulBltsVend();
    
    int id;
    printf("\nIngrese el ID del boleto a eliminar (1-%d): ", totBlts);
    scanf("%d", &id);
    
    if (id < 1 || id > totBlts) {
        printf("ID invalido.\n");
        return;
    }
    
    int idx = id - 1;
    
    // Pedir confirmación
    char conf;
    printf("\n¿Esta seguro que desea eliminar el boleto con codigo %s a nombre de %s? (S/N): ", 
           bltsVend[idx].cod, bltsVend[idx].nom);
    getchar(); // Limpiar buffer
    scanf("%c", &conf);
    
    if (conf != 'S' && conf != 's') {
        printf("Operacion cancelada.\n");
        return;
    }
    
    // Actualizar fondos recaudados
    fondRec -= bltsVend[idx].precio;
    
    printf("Boleto con codigo %s a nombre de %s eliminado.\n", 
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
        scanf("%d", &opcion);
        switch (opcion) {
            case 1:
                printf("Nuevo precio Basico: "); scanf("%f", &preBas);
                printf("Nuevo precio Premium: "); scanf("%f", &prePrem);
                printf("Nuevo precio Oro: "); scanf("%f", &preOro);
                printf("Precios actualizados.\n");
                guardarDatos();
                break;
            case 2:
                printf("Nueva contrasena: ");
                limpbuf();
                fgets(PASSWORD, sizeof(PASSWORD), stdin);
                PASSWORD[strcspn(PASSWORD, "\n")] = 0;
                printf("Contrasena actualizada.\n");
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
                    printf("Sistema reiniciado completamente.\n");
                    guardarDatos();
                } else {
                    printf("Operacion cancelada.\n");
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
                    printf("Operacion cancelada.\n");
                }
                break;
            case 7:
                return;
            default:
                printf("Opcion no valida.\n");
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
        scanf("%d", &opc);
        switch (opc) {
            case 1: ventaBlts(); break;
            case 2: consulBltsVend(); break;
            case 3: conPre(); break;
            case 4: FonRec(); break;
            case 5: Config(); break;
            case 6: printf("Guardando datos y saliendo...\n"); guardarDatos(); break;
            default: printf("Opcion no valida.\n");
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