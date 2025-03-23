#include <stdio.h>
#include <string.h>
#include <windows.h>
#include <cctype> 
#include <stdlib.h> 

#define p printf
#define s scanf

int esVocal(char c) {
    c = tolower(c); 
    return (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u');
}

int main() {
    int i, j;
    char nombre[5][15];
    char nombrein[5][15];
    char palabraBuscar[15];
    char nombrecam[5][15];
    char nombreOriginal[5][15];
    int encontrar = 0;

    p("******************************************\n");
    p("*          PROGRAMA DE CADENAS          *\n");
    p("******************************************\n");
    p("* NOMBRE   : Noe Castillo Gaytan        *\n");
    p("* MATRICULA: 187855                     *\n");
    p("******************************************\n\n");

    p("Programa de Ejemplo: Arreglos de nombres\n\n");
    p("Ingrese una lista de 5 nombres:\n\n");

    for (i = 0; i < 5; i++) {
        p("Nombre %d: ", i + 1);
        s("%s", nombre[i]);
        strcpy(nombreOriginal[i], nombre[i]); 
    }
    p("\n");

    for (i = 0; i < 5; i++) {
        p("Nombre %d: %s\n", i + 1, nombre[i]);
    }

    // Invertir los nombres
    for (i = 0; i < 5; i++) {
        size_t longitud = strlen(nombre[i]);
        for (j = 0; j < longitud; j++) {
            nombrein[i][j] = nombre[i][longitud - j - 1];
        }
        nombrein[i][longitud] = '\0';
        p("Nombre %d invertido: %s\n", i + 1, nombrein[i]);
    }

    p("\nIngrese una palabra a buscar en el arreglo 1: ");
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
        p("La palabra '%s' no se encontro en el arreglo 1.\n", palabraBuscar);
    }

    // Arreglo actualizado
    p("\nArreglo 1 actualizado:\n");
    for (i = 0; i < 5; i++) {
        p("%s\n", nombre[i]);
    }

    // Arreglo 2 con colores
    p("\n\nArreglo 2 (Colores simulados):\n");
    for (i = 0; i < 5; i++) {
        size_t longitud = strlen(nombrein[i]);
        for (j = 0; j < longitud; j++) {
            HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
            if (esVocal(nombrein[i][j])) {
                SetConsoleTextAttribute(hConsole, 10); // Verde para vocales
            } else {
                SetConsoleTextAttribute(hConsole, 9);  // Azul para consonantes
            }
            p("%c", nombrein[i][j]);
        }
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
        p("\n");
    }

    // Arreglo 3 transformación de nombres
    p("\n\nArreglo 3 (Transformacion del arreglo original):\n");
    for (i = 0; i < 5; i++) {
        size_t longitud = strlen(nombreOriginal[i]);
        int indiceCam = 0;

        if (longitud > 0) {
            for (j = longitud - 1; j >= 0; j -= 2) {
                if (j > 0) {
                    nombrecam[i][indiceCam++] = nombreOriginal[i][j - 1];
                    nombrecam[i][indiceCam++] = nombreOriginal[i][j];
                } else {
                    nombrecam[i][indiceCam++] = nombreOriginal[i][j];
                }
            }
            nombrecam[i][indiceCam] = '\0';
            p("%s\n", nombrecam[i]);
        } else {
            p("\n");
        }
    }

    // Arreglo 2 modificado (Con '#' y colores)
    p("\n\nArreglo 2 modificado (Con '#' y colores):\n");
    for (i = 0; i < 5; i++) {
        size_t longitud = strlen(nombrein[i]);
        for (j = 0; j < longitud; j++) {
            HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
            if (esVocal(nombrein[i][j])) {
                SetConsoleTextAttribute(hConsole, 10); // Verde para vocales
                p("%c", nombrein[i][j]);
            } else {
                SetConsoleTextAttribute(hConsole, 12); // Rojo para '#'
                p("#");
            }
        }
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
        p("\n");
    }

    system("pause");
    return 0;
}
