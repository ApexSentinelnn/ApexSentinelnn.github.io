    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include <time.h>
    
    #define MAX 100
    
    // Función para contar vocales y consonantes
    void contarLetras(char *palabra, int *vocales, int *consonantes) {
        *vocales = *consonantes = 0;
        for (int i = 0; palabra[i] != '\0'; i++) {
            char c = palabra[i];
            if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z')) {
                if (strchr("AEIOUaeiou", c))
                    (*vocales)++;
                else
                    (*consonantes)++;
            }
        }
    }
    
    // Función para reemplazar vocales por un carácter especial
    void reemplazarVocales(char *palabra, char caracter) {
        for (int i = 0; palabra[i] != '\0'; i++) {
            if (strchr("AEIOUaeiou", palabra[i])) {
                palabra[i] = caracter;
            }
        }
    }
    
    // Función para generar un arreglo con letras aleatorias
    void generarArregloAleatorio(char *arreglo, int tam) {
        for (int i = 0; i < tam; i++) {
            arreglo[i] = 'A' + rand() % 26; // Letras mayúsculas aleatorias
        }
        arreglo[tam] = '\0';
    }
    
    // Función para invertir un arreglo
    void invertirArreglo(char *origen, char *destino, int tam) {
        for (int i = 0; i < tam; i++) {
            destino[i] = origen[tam - 1 - i];
        }
        destino[tam] = '\0';
    }
    
    // Función para reemplazar vocales con números consecutivos
    void reemplazarVocalesNumeros(char *arreglo) {
        int num = 1;
        for (int i = 0; arreglo[i] != '\0'; i++) {
            if (strchr("AEIOUaeiou", arreglo[i])) {
                arreglo[i] = '0' + num++;
            }
        }
    }
    
    // Función para reemplazar una letra específica en un arreglo
    void reemplazarLetra(char *arreglo, char buscar, char reemplazo) {
        for (int i = 0; arreglo[i] != '\0'; i++) {
            if (arreglo[i] == buscar) {
                arreglo[i] = reemplazo;
            }
        }
    }
    
    int main() {
        srand(time(NULL));
        int opcion;
        char continuar;
    
        do {
              
            printf("******************************************************\n");
            printf("*                      HECHO POR:                    *\n");
            printf("*              Noe Castillo Gaytan. 187855           *\n");
            printf("******************************************************\n");
            printf("\n--- MENU ---\n");
            printf("1. Primer caso\n");
            printf("2. Segundo caso\n");
            printf("3. Salir\n");
            printf("Seleccione una opcion: ");
            scanf("%d", &opcion);
    
            switch (opcion) {
                case 1: {
                    char palabra[MAX];
                    int vocales, consonantes;
    
                    printf("Introduce una palabra: ");
                    scanf("%s", palabra);
    
                    printf("Palabra ingresada: %s\n", palabra);
    
                    contarLetras(palabra, &vocales, &consonantes);
                    printf("Vocales: %d, Consonantes: %d\n", vocales, consonantes);
    
                    reemplazarVocales(palabra, '*');
                    printf("Palabra con vocales reemplazadas: %s\n", palabra);
                    break;
                }
    
                case 2: {
                    char arreglo1[11], arreglo2[11];
    
                    generarArregloAleatorio(arreglo1, 10);
                    invertirArreglo(arreglo1, arreglo2, 10);
    
                    printf("Arreglo original: %s\n", arreglo1);
                    printf("Arreglo invertido: %s\n", arreglo2);
    
                    reemplazarVocalesNumeros(arreglo1);
                    printf("Arreglo con vocales reemplazadas por numeros: %s\n", arreglo1);
    
                    char letraBuscar, letraReemplazo;
                    printf("Ingresa la letra a reemplazar en el segundo arreglo: ");
                    scanf(" %c", &letraBuscar);
                    printf("Ingresa la nueva letra: ");
                    scanf(" %c", &letraReemplazo);
    
                    reemplazarLetra(arreglo2, letraBuscar, letraReemplazo);
                    printf("Arreglo modificado: %s\n", arreglo2);
                    break;
                }
    
                case 3:
                    printf("Saliendo del programa...\n");
                    return 0;
    
                default:
                    printf("Opción no válida, intenta de nuevo.\n");
            }
    
            printf("\nDesea realizar otra operación (s/n): ");
            scanf(" %c", &continuar);
    
        } while (continuar == 's' || continuar == 'S');
    
        return 0;
    }