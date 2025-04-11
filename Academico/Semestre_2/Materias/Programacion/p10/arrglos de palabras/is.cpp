#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

// Estructura para representar cada fila de datos
struct ZonaCilindros {
    char planta[50];
    char ubicacion[100];
    char color[20];
    int conBolsa; // 1=SI, 0=NO
    int conTapa; // 1=SI, 0=NO
    int rotulados; // 1=SI, 0=NO
    int basuraEvacuada; // 1=SI, 0=NO
    int cantidadBasura; // en kg (aleatorio entre 15-30)
};

// Función para generar un número aleatorio en un rango
int numeroAleatorio(int min, int max) {
    return min + rand() % (max - min + 1);
}

// Función para generar datos aleatorios de SI/NO
int generarSiNo() {
    return rand() % 2; // 0=NO, 1=SI
}

// Función para llenar los datos de las zonas
void llenarDatos(struct ZonaCilindros zonas[], int n) {
    // Zona 1: Taller Eléctrico y Mecánico
    strcpy(zonas[0].planta, "PLANTA DE HARINA Y ACEITE");
    strcpy(zonas[0].ubicacion, "1. Zona de Taller Electrico y Mecanico");
    strcpy(zonas[0].color, "AMARILLO");
    zonas[0].conBolsa = 0;  // NO
    zonas[0].conTapa = 1;   // SI
    zonas[0].rotulados = 1; // SI
    zonas[0].basuraEvacuada = 1; // SI
    zonas[0].cantidadBasura = 25;
    
    strcpy(zonas[1].planta, "PLANTA DE HARINA Y ACEITE");
    strcpy(zonas[1].ubicacion, "1. Zona de Taller Electrico y Mecanico");
    strcpy(zonas[1].color, "BLANCO");
    zonas[1].conBolsa = 0;  // NO
    zonas[1].conTapa = 1;   // SI
    zonas[1].rotulados = 1; // SI
    zonas[1].basuraEvacuada = 0; // NO
    zonas[1].cantidadBasura = 15;
    
    strcpy(zonas[2].planta, "PLANTA DE HARINA Y ACEITE");
    strcpy(zonas[2].ubicacion, "1. Zona de Taller Electrico y Mecanico");
    strcpy(zonas[2].color, "AZUL");
    zonas[2].conBolsa = 0;  // NO
    zonas[2].conTapa = 1;   // SI
    zonas[2].rotulados = 0; // NO
    zonas[2].basuraEvacuada = 1; // SI
    zonas[2].cantidadBasura = 21;
    
    // Zona 2: Duchas y Vestuarios de Zona Seca
    strcpy(zonas[3].planta, "PLANTA DE HARINA Y ACEITE");
    strcpy(zonas[3].ubicacion, "2. Zona de Duchas y Vestuarios de Zona Seca");
    strcpy(zonas[3].color, "VERDE");
    zonas[3].conBolsa = 0;  // NO
    zonas[3].conTapa = 0;   // NO
    zonas[3].rotulados = 1; // SI
    zonas[3].basuraEvacuada = 1; // SI
    zonas[3].cantidadBasura = 28;
    
    strcpy(zonas[4].planta, "PLANTA DE HARINA Y ACEITE");
    strcpy(zonas[4].ubicacion, "2. Zona de Duchas y Vestuarios de Zona Seca");
    strcpy(zonas[4].color, "MARRON");
    zonas[4].conBolsa = 0;  // NO
    zonas[4].conTapa = 0;   // NO
    zonas[4].rotulados = 1; // SI
    zonas[4].basuraEvacuada = 1; // SI
    zonas[4].cantidadBasura = 21;
    
    strcpy(zonas[5].planta, "PLANTA DE HARINA Y ACEITE");
    strcpy(zonas[5].ubicacion, "2. Zona de Duchas y Vestuarios de Zona Seca");
    strcpy(zonas[5].color, "AMARILLO");
    zonas[5].conBolsa = 0;  // NO
    zonas[5].conTapa = 1;   // SI
    zonas[5].rotulados = 0; // NO
    zonas[5].basuraEvacuada = 0; // NO
    zonas[5].cantidadBasura = 26;
    
    strcpy(zonas[6].planta, "PLANTA DE HARINA Y ACEITE");
    strcpy(zonas[6].ubicacion, "2. Zona de Duchas y Vestuarios de Zona Seca");
    strcpy(zonas[6].color, "BLANCO");
    zonas[6].conBolsa = 0;  // NO
    zonas[6].conTapa = 1;   // SI
    zonas[6].rotulados = 1; // SI
    zonas[6].basuraEvacuada = 0; // NO
    zonas[6].cantidadBasura = 23;
}

// Función para calcular sumatorias por característica
void calcularSumatorias(struct ZonaCilindros zonas[], int n, int sumatoriasCaracteristicas[4][2]) {
    // Inicializar arreglo de sumatorias
    for (int i = 0; i < 4; i++) {
        sumatoriasCaracteristicas[i][0] = 0; // Sumatoria NO
        sumatoriasCaracteristicas[i][1] = 0; // Sumatoria SI
    }
    
    // Calcular sumatorias
    for (int i = 0; i < n; i++) {
        // [0] = Con Bolsa
        if (zonas[i].conBolsa == 1)
            sumatoriasCaracteristicas[0][1] += zonas[i].cantidadBasura;
        else
            sumatoriasCaracteristicas[0][0] += zonas[i].cantidadBasura;
        
        // [1] = Con Tapa
        if (zonas[i].conTapa == 1)
            sumatoriasCaracteristicas[1][1] += zonas[i].cantidadBasura;
        else
            sumatoriasCaracteristicas[1][0] += zonas[i].cantidadBasura;
        
        // [2] = Rotulados
        if (zonas[i].rotulados == 1)
            sumatoriasCaracteristicas[2][1] += zonas[i].cantidadBasura;
        else
            sumatoriasCaracteristicas[2][0] += zonas[i].cantidadBasura;
        
        // [3] = Basura Evacuada
        if (zonas[i].basuraEvacuada == 1)
            sumatoriasCaracteristicas[3][1] += zonas[i].cantidadBasura;
        else
            sumatoriasCaracteristicas[3][0] += zonas[i].cantidadBasura;
    }
}

// Función para mostrar el reporte alineado como en la imagen
void mostrarReporte(struct ZonaCilindros zonas[], int n, int sumatorias[4][2]) {
    printf("==============================================================================================\n");
    printf("                     REPORTE DE CILINDROS EN PLANTA DE HARINA Y ACEITE\n");
    printf("==============================================================================================\n");
    printf("%-25s | %-33s | %-8s | %-10s | %-9s | %-10s | %-16s | %-8s |\n", 
           "PLANTA", "UBICACION DE CILINDROS", "Color", "Con Bolsa", "Con Tapa", "Rotulados", "Basura Evacuada", "Cantidad");
    printf("%-25s | %-33s | %-8s | %-2s %-2s | %-2s %-2s | %-2s %-4s | %-12s | %8s |\n", 
           "", "", "", "SI", "NO", "SI", "NO", "SI", "NO", "(kg)", "");
    printf("----------------------------------------------------------------------------------------------\n");
    
    for (int i = 0; i < n; i++) {
        printf("%-25s | %-33s | %-8s | %2s %2s | %2s %2s | %2s %4s | %12s | %8d |\n", 
               zonas[i].planta,
               zonas[i].ubicacion,
               zonas[i].color,
               zonas[i].conBolsa ? "X" : "", zonas[i].conBolsa ? "" : "X",
               zonas[i].conTapa ? "X" : "", zonas[i].conTapa ? "" : "X",
               zonas[i].rotulados ? "X" : "", zonas[i].rotulados ? "" : "X",
               zonas[i].basuraEvacuada ? "X" : "", 
               zonas[i].cantidadBasura);
    }
    
    printf("==============================================================================================\n");
    printf("SUMATORIAS:\n");
    printf("Con Bolsa: SI=%d kg, NO=%d kg\n", sumatorias[0][1], sumatorias[0][0]);
    printf("Con Tapa: SI=%d kg, NO=%d kg\n", sumatorias[1][1], sumatorias[1][0]);
    printf("Rotulados: SI=%d kg, NO=%d kg\n", sumatorias[2][1], sumatorias[2][0]);
    printf("Basura Evacuada: SI=%d kg, NO=%d kg\n", sumatorias[3][1], sumatorias[3][0]);
    printf("==============================================================================================\n");
}

int main() {
    // Inicializar generador de números aleatorios
    srand(time(NULL));
    
    // Definir el número de zonas
    const int NUM_ZONAS = 7;
    
    // Crear arreglo de zonas
    struct ZonaCilindros zonas[NUM_ZONAS];
    
    // Arreglo para almacenar sumatorias [característica][SI/NO]
    int sumatoriasCaracteristicas[4][2]; // [0]=ConBolsa, [1]=ConTapa, [2]=Rotulados, [3]=BasuraEvacuada
    
    // Llenar los datos exactamente como aparecen en la imagen proporcionada
    llenarDatos(zonas, NUM_ZONAS);
    
    // Calcular sumatorias
    calcularSumatorias(zonas, NUM_ZONAS, sumatoriasCaracteristicas);
    
    // Mostrar el reporte
    mostrarReporte(zonas, NUM_ZONAS, sumatoriasCaracteristicas);
    
    return 0;
}