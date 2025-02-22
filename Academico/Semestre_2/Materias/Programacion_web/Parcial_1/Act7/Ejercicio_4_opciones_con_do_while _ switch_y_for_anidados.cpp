#include <stdio.h>    
#include <windows.h>  
#include <stdlib.h>   
#include <time.h>    
#define pri printf
#define sca scanf

int main() {
    int c, num, x, opc;  // Declaración de variables: c, num, x y opc
    HANDLE hConsole;     // Variable para manejar la consola de Windows
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE); // Obtiene el identificador de la consola
    int colores[10] = {4, 1, 2, 6, 5, 13, 12, 11, 15, 8}; 
    srand(time(NULL));

     
    pri("******************************************************\n");
    pri("*                          HECHO POR:                *\n");
    pri("*                  Noe Castillo Gaytan. 187855       *\n");
    pri("******************************************************\n\n");

    do {
        pri("\nMenu de opciones:\n");
        pri("1. Carrera de carros\n");
        pri("2. Cuadro de n niveles\n");
        pri("3. Piramide de n niveles\n");
        pri("4. Preferencia de sabores de nieve a 30 personas\n");
        pri("5. Salir\n");
        pri("Ingrese una opcion: ");
        sca("%d", &opc);

        switch (opc) {
            case 1: {
                const int num_carros = 10;
                const int max_km = 20;
                pri("Pictograma de carros:\n");
                
                for (int i = 0; i < num_carros; ++i) {
                    int distancia = rand() % max_km + 1;
                    SetConsoleTextAttribute(hConsole, colores[i % 10]);
                    pri("Carro %d: ", i + 1);
                    for (int j = 0; j < distancia; ++j) {
                        pri("%c", 219);
                    }
                    pri(" (%d km)\n", distancia);
                }
                SetConsoleTextAttribute(hConsole, 7);
                break;
            }
            case 2: {
                pri("\nIngresa un numero: ");
                sca("%d", &num);
                for (x = 1; x <= num; x++) { 
                    for (c = 1; c <= num; c++) {
                        pri(" %d ", c);
                    }
                    pri("\n");
                }
                break;
            }
            case 3: {
                pri("\nIngresa un numero: ");
                sca("%d", &num);
                for (x = 1; x <= num; x++) {
                    for (c = 1; c <= x; c++) {
                        pri("%d", c);
                    }
                    pri("\n");
                }    
                break;
            }
            case 4: {
                int vainilla = 0, chocolate = 0, fresa = 0;
                for (int i = 0; i < 30; i++) { 
                    int preferencia = (rand() % 3) + 1;
                    if (preferencia == 1) vainilla++;
                    else if (preferencia == 2) chocolate++;
                    else fresa++; 
                }

                pri("Resultados de la encuesta:\n");
                pri("Vainilla: %d personas\n", vainilla);
                pri("Chocolate: %d personas\n", chocolate);
                pri("Fresa: %d personas\n", fresa);
                break;
            }
            case 5:
                pri("Saliendo del programa...\n");
                break;
            default:
                pri("Opcion no valida.\n");
                break;
        }
    } while (opc != 5);

    return 0;
}
