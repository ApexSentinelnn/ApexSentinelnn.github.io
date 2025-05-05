#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Definicion de la estructura estudiante
struct estudiante {
    char nombre[50];
    int matricula;
    float calif;
};

int main() {
    // Declaracion del puntero a la estructura
    struct estudiante *ptr_est;
    
    // Creacion de una variable de tipo estudiante
    struct estudiante mejor;
    
    // Asignacion de la direccion de 'mejor' al puntero
    ptr_est = &mejor;
    
    // Uso del operador -> para acceder a los miembros de la estructura
    strcpy(ptr_est->nombre, "Cleopatra");
    ptr_est->matricula = 15001;
    ptr_est->calif = 7.5;
    
    // Mostrar en pantalla los datos almacenados
    printf("Datos del estudiante:\n");
    printf("Nombre: %s\n", ptr_est->nombre);
    printf("Matricula: %d\n", ptr_est->matricula);
    printf("Calificacion: %.1f\n", ptr_est->calif);
    
    // Ejemplo utilizando memoria dinamica con malloc()
    printf("\n--- Ejemplo con malloc() ---\n");
    
    // Solicitar memoria para un nuevo estudiante
    struct estudiante *nuevo_est = (struct estudiante *) malloc(sizeof(struct estudiante));
    
    // Verificar si se asigno correctamente la memoria
    if (nuevo_est == NULL) {
        printf("Error: No se pudo asignar memoria.\n");
        return 1;
    }
    
    // Solicitar datos al usuario
    printf("Ingrese el nombre del estudiante: ");
    // En un programa real, deberias usar fgets para mayor seguridad
    scanf("%s", nuevo_est->nombre);
    
    printf("Ingrese la matricula: ");
    scanf("%d", &nuevo_est->matricula);
    
    printf("Ingrese la calificacion: ");
    scanf("%f", &nuevo_est->calif);
    
    // Mostrar los datos ingresados
    printf("\nDatos del nuevo estudiante:\n");
    printf("Nombre: %s\n", nuevo_est->nombre);
    printf("Matricula: %d\n", nuevo_est->matricula);
    printf("Calificacion: %.1f\n", nuevo_est->calif);
    
    // Liberar la memoria asignada
    free(nuevo_est);
    
    return 0;
}