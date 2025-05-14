#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Función para limpiar el buffer de entrada
void limpiarBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// Función para escribir texto usando fputc
void escribir_fputc(const char* filename) {
    FILE* f = fopen(filename, "a");
    if (!f) {
        printf("Error al abrir el archivo.\n");
        return;
    }
    printf("Introduce un texto (finaliza con Enter): ");
    char c;
    while ((c = getchar()) != '\n' && c != EOF) {
        fputc(c, f);
    }
    fputc('\n', f);
    fclose(f);
}

// Función para leer texto usando fgetc
void leer_fgetc(const char* filename) {
    FILE* f = fopen(filename, "r");
    if (!f) {
        printf("Error al abrir el archivo.\n");
        return;
    }
    printf("Contenido del archivo:\n");
    int c;
    while ((c = fgetc(f)) != EOF) {
        putchar(c);
    }
    fclose(f);
}

// Función para escribir texto usando fprintf
void escribir_fprintf(const char* filename) {
    FILE* f = fopen(filename, "a");
    if (!f) {
        printf("Error al abrir el archivo.\n");
        return;
    }
    char texto[100];
    printf("Introduce un texto: ");
    fgets(texto, sizeof(texto), stdin);
    texto[strcspn(texto, "\n")] = 0; // Eliminar salto de línea
    fprintf(f, "%s\n", texto);
    fclose(f);
}

// Función para leer texto usando fscanf
void leer_fscanf(const char* filename) {
    FILE* f = fopen(filename, "r");
    if (!f) {
        printf("Error al abrir el archivo.\n");
        return;
    }
    char linea[100];
    printf("Contenido del archivo:\n");
    while (fgets(linea, sizeof(linea), f)) {
        printf("%s", linea);
    }
    fclose(f);
}

// Función para escribir texto usando fputs
void escribir_fputs(const char* filename) {
    FILE* f = fopen(filename, "a");
    if (!f) {
        printf("Error al abrir el archivo.\n");
        return;
    }
    char texto[100];
    printf("Introduce un texto: ");
    fgets(texto, sizeof(texto), stdin);
    texto[strcspn(texto, "\n")] = 0;
    fputs(texto, f);
    fputs("\n", f);
    fclose(f);
}

// Función para leer texto usando fgets
void leer_fgets(const char* filename) {
    FILE* f = fopen(filename, "r");
    if (!f) {
        printf("Error al abrir el archivo.\n");
        return;
    }
    char linea[100];
    printf("Contenido del archivo:\n");
    while (fgets(linea, sizeof(linea), f)) {
        printf("%s", linea);
    }
    fclose(f);
}

//Agregamoss funcion para escribir con fwrite y leer con fread
void escribir_fwrite(const char* filename) {
    FILE* f = fopen(filename, "wb");
    if (!f) {
        printf("Error al abrir el archivo.\n");
        return;
    }
    char texto[100];
    printf("Introduce un texto: ");
    fgets(texto, sizeof(texto), stdin);
    fwrite(texto, sizeof(char), strlen(texto), f);
    fclose(f);
}
// Función para leer texto usando fread
void leer_fread(const char* filename) {
    FILE* f = fopen(filename, "rb");
    if (!f) {
        printf("Error al abrir el archivo.\n");
        return;
    }
    char buffer[100];
    size_t bytesLeidos = fread(buffer, sizeof(char), sizeof(buffer), f);
    buffer[bytesLeidos] = '\0'; // Asegurarse de que el buffer esté terminado en null
    printf("Contenido del archivo:\n%s", buffer);
    fclose(f);
}


void menu() {
    int opcion;
    do {
        printf("\n--- MENU ---\n");
        printf("1. Escribir y leer con fputc/fgetc\n");
        printf("2. Escribir y leer con fprintf/fscanf\n");
        printf("3. Escribir y leer con fputs/fgets\n");
        printf("4. Escribir y leer con fwrite/fread\n");
        printf("0. Salir\n");
        printf("Selecciona una opcion: ");
        scanf("%d", &opcion);
        limpiarBuffer();

        switch (opcion) {
            case 1:
                escribir_fputc("archivo1.txt");
                leer_fgetc("archivo1.txt");
                break;
            case 2:
                escribir_fprintf("archivo2.txt");
                leer_fscanf("archivo2.txt");
                break;
            case 3:
                escribir_fputs("archivo3.txt");
                leer_fgets("archivo3.txt");
                break;
            case 4:
                escribir_fwrite("archivo4.txt");
                leer_fread("archivo4.txt");
                break;
            case 0:
                printf("Saliendo...\n");
                break;
            default:
                printf("Opcion invalida.\n");
        }
    } while (opcion != 0);
}

int main() {
    menu();
    return 0;
}
