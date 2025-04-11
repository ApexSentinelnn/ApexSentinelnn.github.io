#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

void matri(void) {
    printf("****************************************\n");
    printf("* Desarrollado por: Noe Castillo Gaytan *\n");
    printf("* Matricula: 187855 *\n");
    printf("****************************************\n\n");
}

void dat(int pes[], int bol[], int tap[], int rot[], int vac[]);
void sum(int pes[], int bol[], int tap[], int rot[], int vac[], int tot[][2]);
void imp(int pes[], int bol[], int tap[], int rot[], int vac[], int tot[][2]);

void dat(int pes[], int bol[], int tap[], int rot[], int vac[]) {
    for(int i = 0; i < 7; i++) {
        pes[i] = 15 + rand() % 16;  //peso entre 15 y 30 kg
        bol[i] = rand() % 2;        
        tap[i] = rand() % 2;
        rot[i] = rand() % 2;
        vac[i] = rand() % 2;
    }
}

void sum(int pes[], int bol[], int tap[], int rot[], int vac[], int tot[][2]) {
    for(int i = 0; i < 7; i++) {
        tot[0][bol[i]] += pes[i];   
        tot[1][tap[i]] += pes[i];   
        tot[2][rot[i]] += pes[i];   
        tot[3][vac[i]] += pes[i];   
    }
}

void imp(int pes[], int bol[], int tap[], int rot[], int vac[], int tot[][2]) {
    char *col[7] = {"Amarillo", "Blanco", "Azul", "Verde", "Marron", "Amarillo", "Blanco"};
    char *area[7] = {
        "1. Taller Electrico y Mecanico",
        "1. Taller Electrico y Mecanico",
        "1. Taller Electrico y Mecanico",
        "2. Zonas de Ducha y Vestuarios",
        "2. Zonas de Ducha y Vestuarios",
        "2. Zonas de Ducha y Vestuarios",
        "2. Zonas de Ducha y Vestuarios"
    };
    printf("\n=================================================================================================================================================");
    printf("\n|                                                  Reporte de cilindros de planta de harinas y aceites                                          |");
    printf("\n=================================================================================================================================================\n");
    printf("| %-15s | %-35s | %-10s | %-5s | %-5s | %-9s | %-7s | %-8s | %-23s |\n",
           "Planta", "Area", "Color", "Bolsa", "Tapa", "Rotulado", "Evacuo", "Peso", "Sumatoria");
    printf("=================================================================================================================================================\n");

    for (int i = 0; i < 7; i++) {
        printf("| %-15s | %-35s | %-10s | %-5d | %-5d | %-9d | %-7d | %-6dKg | Si=%-5dKg | No=%-5dKg |\n",
               "Harina y aceite", area[i], col[i],
               bol[i], tap[i], rot[i], vac[i], pes[i],
               tot[0][1], tot[0][0]);
    }

    printf("=================================================================================================================================================\n");
    printf("\nColumna de Sumatoria:\n");
    printf("Bolsa:     si = %-3dKg || no = %-3dKg\n", tot[0][1], tot[0][0]);
    printf("Tapa:      si = %-3dKg || no = %-3dKg\n", tot[1][1], tot[1][0]);
    printf("Rotulado:  si = %-3dKg || no = %-3dKg\n", tot[2][1], tot[2][0]);
    printf("Evacuada:  si = %-3dKg || no = %-3dKg\n", tot[3][1], tot[3][0]);
}

int main() {
    srand(time(0));
    int pes[7] = {0}, bol[7] = {0}, tap[7] = {0}, rot[7] = {0}, vac[7] = {0};
    int tot[4][2] = {0};  //guardar sumatorias

    matri();
    dat(pes, bol, tap, rot, vac);
    sum(pes, bol, tap, rot, vac, tot);
    imp(pes, bol, tap, rot, vac, tot);

    return 0;
}
