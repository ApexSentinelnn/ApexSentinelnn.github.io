#include <stdio.h>
#include <conio.h>
#include <stdlib.h>

typedef struct {
    char Nombre[25];
    int Edad;
    float Sueldo;
} Registro;

void matricula(){
    printf("Matricula: 187855\n");
    printf("Nombre: Noe Castillo Gaytan\n");
    printf("Curso: Programacion 1\n");
    printf("Fecha: 14 de mayo de 2025\n");
}

int main() {
    Registro empleados[5];
    FILE *archivo;
    int i;

    printf("=== INGRESO DE DATOS (5 REGISTROS) ===\n");
    
    archivo = fopen("empleados.txt", "w");
    
    if(archivo == NULL) {
        printf("Error al crear el archivo!\n");
        return 1;
    }

    for(i = 0; i < 5; i++) {
        printf("\nRegistro %d:\n", i+1);
        
        printf("Nombre: ");
        scanf("%24s", empleados[i].Nombre);
        
        printf("Edad: ");
        scanf("%d", &empleados[i].Edad);
        
        printf("Sueldo: ");
        scanf("%f", &empleados[i].Sueldo);
        
        while(getchar() != '\n');
        
        fprintf(archivo, "Registro %d\n", i+1);
        fprintf(archivo, "Nombre: %s\n", empleados[i].Nombre);
        fprintf(archivo, "Edad: %d\n", empleados[i].Edad);
        fprintf(archivo, "Sueldo: %.2f\n\n", empleados[i].Sueldo);
    }
    fclose(archivo);
    printf("\nDatos guardados correctamente en empleados.txt!\n");

    printf("\n=== DATOS ALMACENADOS EN EL ARCHIVO ===\n");
    
    archivo = fopen("empleados.txt", "r");
    
    if(archivo == NULL) {
        printf("Error al abrir el archivo para lectura!\n");
        return 1;
    }

    char linea[100];
    while(fgets(linea, sizeof(linea), archivo) != NULL) {
        printf("%s", linea);
    }

    fclose(archivo);
    printf("\nPresione una tecla para salir...");
    getch();
    return 0;
}