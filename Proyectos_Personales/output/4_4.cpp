#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <windows.h>

#define p printf
#define s scanf

// Función para establecer el color del texto en consola
void setColor(int textColor) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, textColor);
}

int main() {
    int i, j, k;
    char nombre[5][15];
    char nombrein[5][15];
    char palabraBuscar[15];
    int encontrar = 0;

    p("NOMBRE: Sanchez Mendoza Valeria Guadalupe \n");
    p("MATRICULA: 185890\n\n");

    p("Programa de Ejemplo arreglos de nombres\n\n");
    p("Dame una lista de 5 nombres\n\n");

    for (i = 0; i < 5; i++) {
        p("Dame el nombre %d: ", i + 1);
        s("%s", nombre[i]);
    }
    p("\n\n");

    for (i = 0; i < 5; i++) {
        p("El nombre %d es: %s\n", i + 1, nombre[i]);
    }

    // Invertir los nombres
    for (i = 0; i < 5; i++) {
        int longitud = strlen(nombre[i]);

        for (j = 0; j < longitud; j++) {
            nombrein[i][j] = nombre[i][longitud - j - 1];
        }
        nombrein[i][longitud] = '\0';
        p("El nombre %d invertido es: %s\n", i + 1, nombrein[i]);
    }

    p("Ingrese una palabra a buscar en el arreglo 1: ");
    s("%s", palabraBuscar);

    // Buscar la palabra
    for (i = 0; i < 5; i++) {
        if (strcmp(nombre[i], palabraBuscar) == 0) {
            p("Palabra encontrada en la fila %d: %s\n", i + 1, nombre[i]);
            strcpy(nombre[i], "BINGO");
            encontrar = 1;
            break; // Salir del bucle si se encuentra la palabra
        }
    }

    if (!encontrar) {
        p("La palabra '%s' no se encontró en el arreglo 1.\n", palabraBuscar);
    }

    // Arreglo actualizado
    p("\nArreglo 1 actualizado:\n");
    for (i = 0; i < 5; i++) {
        p("%s\n", nombre[i]);
    }

    // Arreglo 2 con colores
    p("\n\nArreglo 2 (con colores simulados):\n");
    for (i = 0; i < 5; i++) {
        int longitud = strlen(nombrein[i]);
        for (j = 0; j < longitud; j++) {
            if (nombrein[i][j] == 'a' || nombrein[i][j] == 'e' || nombrein[i][j] == 'i' || nombrein[i][j] == 'o' || nombrein[i][j] == 'u') {
                setColor(10); // Verde para vocales
                p("%c", nombrein[i][j]);
            } else {
                setColor(9);  // Azul para consonantes
                p("%c", nombrein[i][j]);
            }
        }
        // Restaurar color predeterminado
        setColor(7); // 7 es el color predeterminado en la consola
        p("\n");
    }

    getch();
    return 0;
}

