#include <stdio.h>


// Desarrollado por: Luz Elena Mendoza - Matrícula: 187739 y Andrea Giselle Jiménez Alvarado - Matrícula: 187274


void mostrarMenu() {
    int opcion;
    do {
        printf("\n====================================\n");
        printf("           Nombre del sorteo          \n");
        printf("======================================\n");
        printf("1) Venta de boletos\n");
        printf("2) Consulta de boletos vendidos\n");
        printf("3) Consulta de premios ganados\n");
        printf("4) Fondos recaudados\n");
        printf("5) Configuracion\n");
        printf("6) Salir\n");
        printf("Seleccione una opcion: ");
        scanf("%d", &opcion);
        
        switch(opcion) {
            case 1:
                printf("\nOpcion 1: Venta de boletos seleccionada.\n");
                // Aquí se implementará la funcionalidad de venta de boletos
                break;
            case 2:
                printf("\nOpcion 2: Consulta de boletos vendidos seleccionada.\n");
                // Aquí se implementará la consulta de boletos vendidos
                break;
            case 3:
                printf("\nOpcion 3: Consulta de premios ganados seleccionada.\n");
                // Aquí se implementará la consulta de premios ganados
                break;
            case 4:
                printf("\nOpcion 4: Fondos recaudados seleccionada.\n");
                // Aquí se implementará la consulta de fondos recaudados
                break;
            case 5:
                printf("\nOpcion 5: Configuracion seleccionada.\n");
                // Aquí se implementará la configuración
                break;
            case 6:
                printf("\nSaliendo del sistema...\n");
                break;
            default:
                printf("\nOpcion no valida. Intente de nuevo.\n");
        }
    } while(opcion != 6);
}

int main() {
    mostrarMenu();
    return 0;
}