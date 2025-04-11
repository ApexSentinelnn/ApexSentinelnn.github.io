#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define NUM_VENDEDORES 5
#define NUM_MESES 3

// Estructura para almacenar la información de cada vendedor
typedef struct {
    char nombre[50];
    int ventas[NUM_MESES];
    int ventasTotales;
    float comision;
} Vendedor;

// Función para registrar las ventas de forma aleatoria
void registrarVentas(Vendedor vendedores[]) {
    int i, j;
    
    // Recorrer cada vendedor
    for (i = 0; i < NUM_VENDEDORES; i++) {
        vendedores[i].ventasTotales = 0;
        
        // Registrar ventas para cada mes
        for (j = 0; j < NUM_MESES; j++) {
            // Generar ventas aleatorias entre 50 y 100
            vendedores[i].ventas[j] = rand() % 51 + 50;
            vendedores[i].ventasTotales += vendedores[i].ventas[j];
        }
        
        // Calcular comisión
        if (vendedores[i].ventasTotales > 200) {
            vendedores[i].comision = vendedores[i].ventasTotales * 0.15;
        } else {
            vendedores[i].comision = 0.0;
        }
    }
}

// Función para mostrar la información en forma de tabla
void mostrarInformacion(Vendedor vendedores[]) {
    int i, j;
    
    // Imprimir encabezados
    printf("Vendedor\tVentas\t\tVentas\t\tVentas\t\tVentas\t\tComision\n");
    printf("\t\tMes 1\t\tMes 2\t\tMes 3\t\tTotales\n");
    printf("--------------------------------------------------------------------------------\n");
    
    // Imprimir datos de cada vendedor
    for (i = 0; i < NUM_VENDEDORES; i++) {
        printf("%s\t", vendedores[i].nombre);
        
        for (j = 0; j < NUM_MESES; j++) {
            printf("%d\t\t", vendedores[i].ventas[j]);
        }
        
        printf("%d\t\t%.2f\n", vendedores[i].ventasTotales, vendedores[i].comision);
    }
}

int main() {
    // Declarar e inicializar la semilla para números aleatorios
    srand(time(NULL));
    
    // Declarar arreglo de vendedores
    Vendedor vendedores[NUM_VENDEDORES];
    int i;
    
    // Mostrar información del estudiante
    printf("Nombre: [TU NOMBRE AQUI]\n");
    printf("Matricula: [TU MATRICULA AQUI]\n\n");
    
    // Solicitar nombres de vendedores
    for (i = 0; i < NUM_VENDEDORES; i++) {
        printf("Ingrese el nombre del vendedor %d: ", i + 1);
        // Usar fgets para evitar desbordamiento de buffer
        fgets(vendedores[i].nombre, 50, stdin);
        
        // Eliminar el salto de línea al final del nombre
        vendedores[i].nombre[strcspn(vendedores[i].nombre, "\n")] = 0;
        
        // Si el usuario no ingresó un nombre, asignar uno por defecto
        if (strlen(vendedores[i].nombre) == 0) {
            sprintf(vendedores[i].nombre, "Vendedor %d", i + 1);
        }
    }
    
    // Registrar ventas aleatorias y calcular comisiones
    registrarVentas(vendedores);
    
    // Mostrar la información en forma de tabla
    printf("\nResumen de Ventas y Comisiones:\n\n");
    mostrarInformacion(vendedores);
    
    return 0;
}