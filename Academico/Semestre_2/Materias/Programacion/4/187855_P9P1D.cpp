//Noe Castillo Gaytan
#include <stdio.h>

void imprimirPatron(int n) {
    for (int k = n; k >= 1; k--) {  // Recorre desde n hasta 1
        // Parte creciente (1 hasta k)
        for (int i = 1; i <= k; i++) {
            for (int j = 0; j < i; j++) {
                printf("*");
            }
            printf("\n");
        }
        
        // Parte decreciente (k-1 hasta 1), excepto cuando k=1
        if (k > 1) {
            for (int i = k - 1; i >= 2; i--) {
                for (int j = 0; j < i; j++) {
                    printf("*");
                }
                printf("\n");
            }
        }
    }
}

int main() {
    int n;
    printf("Ingrese un numero: ");
    scanf("%d", &n);
    imprimirPatron(n);
    return 0;
}