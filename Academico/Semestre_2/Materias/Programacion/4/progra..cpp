#include <stdio.h>

int main() {
    int n;

    printf("Ingrese el numero inicial de asteriscos: ");
    scanf("%d", &n);

    while (n > 0) {
        for (int i = 0; i < n; i++) {
            printf("*");
        }
        printf("\n");
        n--; // Disminuir la cantidad de asteriscos en cada iteración
    }
    //es como un triangulo, empezarfa en uno y terminara en 1, al momento de iniciar incrementara al n numero y cuando llegue a n numero decrementara 
    return 0;
}
