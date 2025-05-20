#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char Nombre[25];
    int Edad;
    float Sueldo;
} sRegistro;

int main() {
    char nombreArchivo[] = "datos.txt";
    int opcion;
    int salir = 0;

    while (!salir) {
        // menu
        printf("\nMenu:");
        printf("\n\t1. Crear fichero");
        printf("\n\t2. Insertar datos");
        printf("\n\t3. Ver datos");
        printf("\n\t4. Buscar dato");
        printf("\n\t5. Modificar dato");
        printf("\n\t6. Salir");
        printf("\nOpcion: ");
        scanf("%d", &opcion);
        getchar();

        switch (opcion) {
            case 1: {
                // CrearFichero
                FILE *f = fopen(nombreArchivo, "r");
                if (!f) {
                    f = fopen(nombreArchivo, "w");
                    if (f) {
                        printf("\nArchivo '%s' creado!\n", nombreArchivo);
                        fclose(f);
                    } else {
                        printf("\nError al crear el archivo '%s'!\n", nombreArchivo);
                    }
                } else {
                    printf("\nEl fichero '%s' ya existe!\n", nombreArchivo);
                    fclose(f);
                }
                break;
            }
            case 2: {
                // InsertarDatos
                FILE *f = fopen(nombreArchivo, "a");
                if (!f) {
                    printf("\nError al abrir el fichero '%s'!\n", nombreArchivo);
                    printf("Por favor, asegúrese de que el archivo exista o intente crearlo primero.\n");
                    break;
                }
                sRegistro reg;
                printf("\nDigita el nombre: ");
                scanf("%24s", reg.Nombre);
                getchar();
                printf("\nDigita la edad: ");
                scanf("%d", &reg.Edad);
                getchar();
                printf("\nDigita el sueldo: ");
                scanf("%f", &reg.Sueldo);
                getchar();

                fwrite(&reg, sizeof(sRegistro), 1, f);
                fclose(f);
                printf("\nDatos insertados correctamente.\n");
                break;
            }
            case 3: {
                // VerDatos
                FILE *f = fopen(nombreArchivo, "r");
                if (!f) {
                    printf("\nEl fichero '%s' no existe!\n", nombreArchivo);
                    break;
                }
                sRegistro reg;
                int numero = 1;
                printf("\nNumero\tNombre\t\tEdad\tSueldo\n");
                while (fread(&reg, sizeof(sRegistro), 1, f) == 1) {
                    printf("%d\t%s\t\t%d\t%.2f\n", numero, reg.Nombre, reg.Edad, reg.Sueldo);
                    numero++;
                }
                fclose(f);
                break;
            }
            case 4: {
                // BuscarDato
                FILE *f = fopen(nombreArchivo, "r");
                if (!f) {
                    printf("\nEl fichero '%s' no existe!\n", nombreArchivo);
                    break;
                }
                char nombreBuscar[25];
                int encontrado = 0;
                sRegistro reg;
                printf("\nIngrese el nombre a buscar: ");
                scanf("%24s", nombreBuscar);
                getchar();

                while (fread(&reg, sizeof(sRegistro), 1, f) == 1) {
                    if (strcmp(reg.Nombre, nombreBuscar) == 0) {
                        printf("\nRegistro encontrado:\n");
                        printf("Nombre: %s\n", reg.Nombre);
                        printf("Edad: %d\n", reg.Edad);
                        printf("Sueldo: %.2f\n", reg.Sueldo);
                        encontrado = 1;
                        break;
                    }
                }
                fclose(f);
                if (!encontrado) {
                    printf("\nNo se encontró ningún registro con el nombre '%s'.\n", nombreBuscar);
                }
                break;
            }
            case 5: {
                // ModificarDato
                FILE *f = fopen(nombreArchivo, "r+b");
                if (!f) {
                    printf("\nEl fichero '%s' no existe!\n", nombreArchivo);
                    break;
                }
                char nombreModificar[25];
                int encontrado = 0;
                sRegistro reg;
                printf("\nIngrese el nombre del trabajador cuyo sueldo desea modificar: ");
                scanf("%24s", nombreModificar);
                getchar();

                while (fread(&reg, sizeof(sRegistro), 1, f) == 1) {
                    if (strcmp(reg.Nombre, nombreModificar) == 0) {
                        printf("\nRegistro encontrado:\n");
                        printf("Nombre: %s\n", reg.Nombre);
                        printf("Edad: %d\n", reg.Edad);
                        printf("Sueldo actual: %.2f\n", reg.Sueldo);

                        printf("\nIngrese el nuevo sueldo: ");
                        scanf("%f", &reg.Sueldo);
                        getchar();

                        fseek(f, -sizeof(sRegistro), SEEK_CUR);
                        fwrite(&reg, sizeof(sRegistro), 1, f);
                        printf("\nSueldo modificado correctamente.\n");
                        encontrado = 1;
                        break;
                    }
                }
                fclose(f);
                if (!encontrado) {
                    printf("\nNo se encontró ningún trabajador con el nombre '%s'.\n", nombreModificar);
                }
                break;
            }
            case 6:
                salir = 1;
                break;
            default:
                printf("\nOpcion no valida\n");
        }
    }
    return 0;
}
