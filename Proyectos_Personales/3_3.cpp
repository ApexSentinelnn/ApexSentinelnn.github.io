#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <windows.h>

#define p printf
#define s scanf

int main() {
    int i, j, k;
    char nombre[5][15];
    char nombrein[5][15];
    char palabraBuscar[15];
    char nombrecam[5][15];
    int encontrar = 0;

    p("NOMBRE: Noe castillo gaytan \n");
    p("MATRICULA: 187855\n\n");

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
            break;
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
            HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
            if (nombrein[i][j] == 'a' || nombrein[i][j] == 'e' || nombrein[i][j] == 'i' || nombrein[i][j] == 'o' || nombrein[i][j] == 'u') {
                SetConsoleTextAttribute(hConsole, 10); // verde para vocales
                p("%c", nombrein[i][j]);
            } else {
                SetConsoleTextAttribute(hConsole, 9);  // azul para consonantes
                p("%c", nombrein[i][j]);
            }
        }
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
        p("\n");
    }
    getch();
    return 0;
}

