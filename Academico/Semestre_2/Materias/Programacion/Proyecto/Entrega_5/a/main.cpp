#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>

#define MAXBOL 100 // Maximo de boletos
#define TAMTAB 25  // Tamano del tablero
#define PRENUM 10  // Numero de premios ocultos
#define FILENAME "Datos.txt" // Nombre del archivo de datos
#define color(c) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), c)


// Precios configurables
float preBas = 25.0;
float prePrem = 50.0;
float preOro = 100.0;
char PASSWORD[] = "123";
int colores[3] = {9,10,12};

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
    HANDLE hConsole;
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    printf("\n|==============================================|\n");
    printf("|         Matriculas de estudiantes            |\n");
    printf("|==============================================|\n");
    printf("|");color(10);printf(" 187855 ");color(7);printf("|");color(10);printf(" Castillo Gaytan Noe                 ");color(7);printf("|\n");
    printf("|");color(10);printf(" 187339 ");color(7);printf("|");color(10);printf(" Tristan Contreras David Alejandro   ");color(7);printf("|\n");
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

    HANDLE hConsole;
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    printf("\n---    Tu tablero ---\n");
    for (int i = 0; i < TAMTAB; i++) {
        if (i % 5 == 0) printf("\n");
        if (tablero[i] == 1){
            color(12);
            printf("[XX] "); // Casilla seleccionada
        }
        else{
            color(9);
            printf("[%2d] ", i + 1); // Casilla disponible
        }
        color(7);
    }
    printf("\n");
}

// Guardar datos al archivo en formato de tabla
void guardarDatos() {
    HANDLE hConsole;
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    FILE *archivo = fopen(FILENAME, "w");
    if (archivo == NULL) {
            color(14);
        printf("Error al abrir el archivo para guardar datos.\n");
    color(7);
        return;
    }

    // Cabecera para lectura humana
    fprintf(archivo, "====================== SISTEMA DE SORTEO ======================\n\n");





    // Guardar configuración de precios
    fprintf(archivo, "=== CONFIGURACION DE PRECIOS ===\n");
    fprintf(archivo, "Basico: %.2f | Premium: %.2f | Oro: %.2f\n\n", preBas, prePrem, preOro);

    // Guardar premios globales
    fprintf(archivo, "=== PREMIOS OCULTOS ===\n");
    fprintf(archivo, "Posicion | Premio\n");
    fprintf(archivo, "-----------------\n");
    for (int i = 0; i < TAMTAB; i++) {
        if (premiosGlobales[i] > 0) {
            fprintf(archivo, "%8d | %.2f\n", i+1, premiosGlobales[i]);
        }
    }
    fprintf(archivo, "\n");

    // Guardar fondos recaudados
    fprintf(archivo, "=== FONDOS RECAUDADOS ===\n");
    fprintf(archivo, "Total: %.2f (%s)\n\n", fondRec, (fondRec < 0 ? "PERDIDA" : "GANANCIA"));

    // Guardar boletos en formato tabla
    fprintf(archivo, "=== BOLETOS VENDIDOS: %d ===\n", totBlts);
    if (totBlts > 0) {
        fprintf(archivo, "ID | Codigo | Nombre                | Tipo    | Precio | Premio  | Ganancia\n");
        fprintf(archivo, "--------------------------------------------------------------------------\n");
        for (int i = 0; i < totBlts; i++) {
            Blt b = bltsVend[i];
            float ganancia = b.precio - b.premioGanado;
            fprintf(archivo, "%-2d | %-6s | %-20s | %-7s | %6.2f | %7.2f | %8.2f\n",
                    i+1, b.cod, b.nom, b.tipo, b.precio, b.premioGanado, ganancia);
        }
        fprintf(archivo, "\n");
    }

    // Guardar información detallada de cada boleto
    fprintf(archivo, "=== DETALLES DE BOLETOS ===\n");
    for (int i = 0; i < totBlts; i++) {
        Blt b = bltsVend[i];
        fprintf(archivo, "Boleto #%d - Codigo: %s\n", i+1, b.cod);
        fprintf(archivo, "  Nombre: %s\n", b.nom);
        fprintf(archivo, "  Domicilio: %s\n", b.dom);
        fprintf(archivo, "  Tipo: %s (%.2f)\n", b.tipo, b.precio);
        fprintf(archivo, "  Numeros seleccionados: ");
        for (int j = 0; j < b.catnum; j++) {
            fprintf(archivo, "%d ", b.numbol[j]);
        }
        fprintf(archivo, "\n");
        fprintf(archivo, "  Premio ganado: %.2f\n\n", b.premioGanado);
    }

    //sección técnica para la carga de datos
    fprintf(archivo, "###DATOS_TECNICOS###\n");
    fprintf(archivo, "CONFIG\n");
    fprintf(archivo, "%.2f %.2f %.2f %s\n", preBas, prePrem, preOro,PASSWORD);


    fprintf(archivo, "PREMIOS\n");
    for (int i = 0; i < TAMTAB; i++) {
        fprintf(archivo, "%.2f ", premiosGlobales[i]);
    }
    fprintf(archivo, "\n");

    fprintf(archivo, "BOLETOS\n");
    fprintf(archivo, "%d\n", totBlts);

    for (int i = 0; i < totBlts; i++) {
        fprintf(archivo, "%s\n", bltsVend[i].nom);
        fprintf(archivo, "%s\n", bltsVend[i].dom);
        fprintf(archivo, "%s\n", bltsVend[i].cod);
        fprintf(archivo, "%s\n", bltsVend[i].tipo);
        fprintf(archivo, "%.2f\n", bltsVend[i].precio);
        fprintf(archivo, "%d\n", bltsVend[i].catnum);

        // Escribir números seleccionados
        for (int j = 0; j < bltsVend[i].catnum; j++) {
            fprintf(archivo, "%d ", bltsVend[i].numbol[j]);
        }
        fprintf(archivo, "\n");

        // Escribir tablero
        for (int j = 0; j < TAMTAB; j++) {
            fprintf(archivo, "%d ", bltsVend[i].tablero[j]);
        }
        fprintf(archivo, "\n");

        fprintf(archivo, "%.2f\n", bltsVend[i].premioGanado);
    }

    fprintf(archivo, "FONDOS\n");
    fprintf(archivo, "%.2f\n", fondRec);

    fclose(archivo);
    color(14);
    printf("Datos guardados correctamente.\n");
    color(7);
}

// Cargar datos desde el archivo
void cargarDatos() {
    FILE *archivo = fopen(FILENAME, "r");
    if (archivo == NULL) {
            color(14);
        printf("No se encontró archivo de datos. Se creará uno nuevo al guardar.\n");
        color(7);
        return;
    }

    char buffer[200];
    int datosTecnicos = 0;

    // Buscar la sección de datos técnicos
    while (fgets(buffer, sizeof(buffer), archivo) != NULL) {
        if (strstr(buffer, "###DATOS_TECNICOS###") != NULL) {
            datosTecnicos = 1;
            break;
        }
    }

    if (!datosTecnicos) {
            color(14);
        printf("Error: No se encontró la sección de datos técnicos en el archivo.\n");
        color(7);
        fclose(archivo);
        return;
    }

    // Leer configuración
    fgets(buffer, sizeof(buffer), archivo);  // Leer "CONFIG"
    fscanf(archivo, "%f %f %f  %[^\n]\n", &preBas, &prePrem, &preOro,PASSWORD);


    // Leer premios globales
    fgets(buffer, sizeof(buffer), archivo);  // Leer "PREMIOS"
    for (int i = 0; i < TAMTAB; i++) {
        fscanf(archivo, "%f", &premiosGlobales[i]);
    }
    fscanf(archivo, "\n");

    // Leer boletos
    fgets(buffer, sizeof(buffer), archivo);  // Leer "BOLETOS"
    fscanf(archivo, "%d\n", &totBlts);

    for (int i = 0; i < totBlts; i++) {
        fgets(bltsVend[i].nom, sizeof(bltsVend[i].nom), archivo);
        bltsVend[i].nom[strcspn(bltsVend[i].nom, "\n")] = 0;

        fgets(bltsVend[i].dom, sizeof(bltsVend[i].dom), archivo);
        bltsVend[i].dom[strcspn(bltsVend[i].dom, "\n")] = 0;

        fgets(bltsVend[i].cod, sizeof(bltsVend[i].cod), archivo);
        bltsVend[i].cod[strcspn(bltsVend[i].cod, "\n")] = 0;

        fgets(bltsVend[i].tipo, sizeof(bltsVend[i].tipo), archivo);
        bltsVend[i].tipo[strcspn(bltsVend[i].tipo, "\n")] = 0;

        fscanf(archivo, "%f\n", &bltsVend[i].precio);
        fscanf(archivo, "%d\n", &bltsVend[i].catnum);

        // Leer números seleccionados
        for (int j = 0; j < bltsVend[i].catnum; j++) {
            fscanf(archivo, "%d", &bltsVend[i].numbol[j]);
        }
        fscanf(archivo, "\n");

        // Leer tablero
        for (int j = 0; j < TAMTAB; j++) {
            fscanf(archivo, "%d", &bltsVend[i].tablero[j]);
        }
        fscanf(archivo, "\n");

        fscanf(archivo, "%f\n", &bltsVend[i].premioGanado);
    }

    // Leer fondos recaudados
    fgets(buffer, sizeof(buffer), archivo);  // Leer "FONDOS"
    fscanf(archivo, "%f\n", &fondRec);

    fclose(archivo);
    printf("Datos cargados correctamente.\n");
}

// Verificar contraseña
int verificarPassword() {
    HANDLE hConsole;
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    char pass[20];

    printf("Ingrese la contrasena para acceder a configuraciones: ");
    scanf("%s", pass);
    if (strcmp(pass, PASSWORD) == 0) {
            color(14);
        printf("Acceso concedido.\n");
            color(7);
        return 1;
    } else {
        color(14);
        printf("Contrasena incorrecta. Acceso denegado.\n");
        color(7);
        return 0;
    }
}

// Realiza la venta de boletos
void ventaBlts() {
    HANDLE hConsole;
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
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
            color(14);
            printf("Entrada invalida.\n");
            color(7);
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
                color(14);
                printf("Numero invalido.\n");
                color(7);
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
                color(10);
            printf("¡Ganaste $%.2f!\n", premio);
        color(7);
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
    HANDLE hConsole;
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    if (totBlts == 0) {
        printf("No hay boletos vendidos.\n");
        return;
    }
    color(11);
    printf("\n| %-5s | %-15s | %-15s | %-5s | %-7s |\n", "ID", "Nombre", "Domicilio", "Codigo", "Tipo");
    printf("----------------------------------------------------------------\n");
    for (int i = 0; i < totBlts; i++) {
        printf("| %-5d | %-15s | %-15s | %-5s | %-7s |\n", i+1,
               bltsVend[i].nom, bltsVend[i].dom, bltsVend[i].cod, bltsVend[i].tipo);
    }
    color(7);
}

// Consulta premios ganados
void conPre() {
    HANDLE hConsole;
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    if (totBlts == 0) {
        printf("No hay boletos vendidos.\n");
        return;
    }
    color(11);
    printf("\n| %-5s | %-15s | %-5s | %-7s | Premio |\n", "ID", "Nombre", "Codigo", "Tipo");
    printf("--------------------------------------------------\n");
    for (int i = 0; i < totBlts; i++) {
        printf("| %-5d | %-15s | %-5s | %-7s | $%.2f |\n", i+1,
               bltsVend[i].nom, bltsVend[i].cod,
               bltsVend[i].tipo, bltsVend[i].premioGanado);
    }
    color(7);
}

// Muestra fondos recaudados
void FonRec() {
    HANDLE hConsole;
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    if (totBlts == 0) {
            color(14);
        printf("No hay boletos vendidos.\n");
            color(7);
        return;
    }

    float totalIngresos = 0.0;
    float totalPremios = 0.0;

    color(11);
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
    color(7);
    float totalGanancia = totalIngresos - totalPremios;
    printf("Total de ventas: %.2f\n", totalIngresos);
    printf("Total de premios: %.2f\n", totalPremios);
    printf("Balance total: %.2f (%s)\n", totalGanancia,
           (totalGanancia < 0 ? "PERDIDA" : "GANANCIA"));
}

// Eliminar un boleto
void eliminarBoleto() {
    HANDLE hConsole;
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    if (totBlts == 0) {
            color(14);
        printf("No hay boletos que eliminar.\n");
        color(7);
        return;
    }

    // Mostrar lista de boletos
    consulBltsVend();

    int id;


    do{
    printf("\nIngrese el ID del boleto a eliminar (1-%d): ", totBlts);
    if (scanf("%d", &id) !=1 || id < 1 || id > totBlts){
            limpbuf();
            color(14);
        printf("ID invalido.\n");
            color(7);

    }
        break;
    }while(1);

    int idx = id - 1;

    // Pedir confirmación
    char conf;
    printf("\n¿Esta seguro que desea eliminar el boleto con codigo %s a nombre de %s? (S/N): ",
           bltsVend[idx].cod, bltsVend[idx].nom);
    getchar(); // Limpiar buffer
    scanf("%c", &conf);

    if (conf != 'S' && conf != 's') {
            color(14);
        printf("Operacion cancelada.\n");
            color(7);
        return;
    }

    // Actualizar fondos recaudados
    fondRec -= bltsVend[idx].precio;
    color(14);
    printf("Boleto con codigo %s a nombre de %s eliminado.\n",
           bltsVend[idx].cod, bltsVend[idx].nom);
        color(7);

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
    HANDLE hConsole;
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
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
        scanf("%d", &opcion);
        switch (opcion) {
            case 1:
                printf("\n--- Precio actual|| Basico: %.2f || Premium: %.2f || Oro: %.2f  ---\n",preBas,prePrem,preOro);
                printf("Nuevo precio Basico: ");
                Or_bas=preBas;
                Or_Prem=prePrem;
                Or_Oro=preOro;

                if (scanf("%f", &preBas) !=1){
                    limpbuf();
                color(14);
                    printf("Precio invalido.\n");
                color(7);
                    break;

                }

                printf("Nuevo precio Premium: ");
                if (scanf("%f", &prePrem) !=1){
                    preBas=Or_bas;

                    limpbuf();
                color(14);
                    printf("Precio invalido.\n");
                color(7);
                    break;
                }


                printf("Nuevo precio Oro: ");
                if (scanf("%f", &preOro) !=1){
                        preBas=Or_bas;
                        prePrem=Or_Prem;

                    limpbuf();

                color(14);
                    printf("Precio invalido.\n");
                color(7);
                    break;
                }

                color(14);
                printf("...Precios actualizados...\n");
                color(7);
                guardarDatos();
                break;
            case 2:
                printf("\nIngresa la nueva contrasena: ");
                scanf("%s",PASSWORD);
                color(14);
                printf("...Contrasena actualizada: --- %s ---...\n",PASSWORD);
                color(7);
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
                    color(14);
                    printf("...Sistema reiniciado completamente...\n");
                    color(7);
                    guardarDatos();
                } else {
                    color(14);
                    printf("...Operacion cancelada...\n");
                    color(7);
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
                    color(14);
                    printf("...Operacion cancelada...\n");
                    color(7);
                }
                break;
            case 7:
                return;
            default:
                color(14);
                printf("...Opcion no valida...\n");
                color(7);
        }
    } while (opcion != 7);
}

// Menu principal
void casos() {
    HANDLE hConsole;
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
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
            case 6: color(14);printf("Guardando datos y saliendo...\n");color(7); guardarDatos(); break;
            default: color(14);printf("Opcion no valida.\n");color(7);
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
