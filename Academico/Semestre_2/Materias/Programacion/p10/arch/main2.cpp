#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h> // Para strcat

void llenar(int a[], int b[], int c[], int d[], int e[]);
void sumar(int a[], int b[], int c[], int d[], int e[], int f[]);
void presentar(int a[], int b[], int c[], int d[], int e[], int f[]);

int main() {
    srand(time(NULL));
    int peso[7] = {0}, bola[7] = {0}, tapa[7] = {0}, rotulados[7] = {0}, vaciados[7] = {0}, suma[9] = {0};
    
    llenar(peso, bola, tapa, rotulados, vaciados);
    sumar(peso, bola, tapa, rotulados, vaciados, suma);
    presentar(peso, bola, tapa, rotulados, vaciados, suma);
    
    return 0;
}

void llenar(int a[], int b[], int c[], int d[], int e[]) {
    for(int i = 0; i < 7; i++) {
        a[i] = 15 + rand() % 16;  // Peso entre 15-30 kg
        b[i] = rand() % 2;        // Bolsa (0 o 1)
        c[i] = rand() % 2;        // Tapa (0 o 1)
        d[i] = rand() % 2;        // Rotulado (0 o 1)
        e[i] = rand() % 2;        // Vaciado (0 o 1)
    }
}

void sumar(int a[], int b[], int c[], int d[], int e[], int f[]) {
    for(int i = 0; i < 7; i++) {
        // Sumar pesos según condición de bolsa
        if(b[i] == 0) {
            f[0] += a[i]; // Suma para bolsa=0
        } else {
            f[1] += a[i]; // Suma para bolsa=1
        }
        
        // Sumar pesos según condición de tapa
        if(c[i] == 0) {
            f[2] += a[i]; // Suma para tapa=0
        } else {
            f[3] += a[i]; // Suma para tapa=1
        }
        
        // Sumar pesos según condición de rotulado
        if(d[i] == 0) {
            f[4] += a[i]; // Suma para rotulado=0
        } else {
            f[5] += a[i]; // Suma para rotulado=1
        }
        
        // Sumar pesos según condición de vaciado
        if(e[i] == 0) {
            f[6] += a[i]; // Suma para vaciado=0
        } else {
            f[7] += a[i]; // Suma para vaciado=1
        }
        
        f[8] += a[i]; // Suma total
    }
}

void presentar(int a[], int b[], int c[], int d[], int e[], int f[]) {
    char *colores[7] = {"amarillo", "blanco", "azul", "verde", "marron", "amarillo", "blanco"};
    char *areas[7] = {
        "1.taller electrico y mecanico",
        "1.taller electrico y mecanico",
        "1.taller electrico y mecanico",
        "2.zonas de ducha y vestuarios de zona seca",
        "2.zonas de ducha y vestuarios de zona seca",
        "2.zonas de ducha y vestuarios de zona seca",
        "2.zonas de ducha y vestuarios de zona seca"
    };
    printf("\n+===========================================================================================================================+\n");
    printf("|\t\t\t\t\tReporte de cilindros de planta de harinas y aceites\t\t\t            |");
    printf("\n+===========================================================================================================================+\n");
    printf("|%-20s|%-45s|%-15s|%-6s|%-6s|%-9s|%-6s|%-9s|\n", 
           "Planta", "Area", "Color", "Bolsa", "Tapa", "Rotulado", "Evacuo", "Cantidad");
    printf("+===========================================================================================================================+\n");
    
    // Datos de la tabla
    for(int i = 0; i < 7; i++) {
        printf("|%-20s|%-45s|%-15s|%-6d|%-6d|%-9d|%-6d|%-9d|\n", 
               "Harina y aceite", 
               areas[i], 
               colores[i], 
               b[i], c[i], d[i], e[i], a[i]);
        printf("+===========================================================================================================================+\n");
    }
    
    printf("\nSumatorias:\n");
    printf("Bolsa:    si=%dKg || no=%dKg\n", f[1], f[0]);
    printf("Tapa:     si=%dKg || no=%dKg\n", f[3], f[2]);
    printf("Rotulado: si=%dKg || no=%dKg\n", f[5], f[4]);
    printf("Evacuada: si=%dKg || no=%dKg\n", f[7], f[6]);
    printf("Total: %dKg\n", f[8]);
}