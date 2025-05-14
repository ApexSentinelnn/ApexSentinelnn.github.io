#include <stdio.h>
#include <stdlib.h> // Para la función exit()
#include <string.h>

void menu();
void CrearFichero(char *nombreFichero);
void InsertarDatos(char *nombreFichero);
void VerDatos(char *nombreFichero);
void BuscarDato(char *nombreFichero);
void ModificarDato(char *nombreFichero);

struct sRegistro
{
    char Nombre[25];
    int Edad;
    float Sueldo;
} registro; // Variable global (considerar pasar como argumento)

int main()
{
    char nombreArchivo[] = "datos.txt"; // Nombre del archivo a usar
    int opcion;
    int exit = 0;

    while (!exit)
    {
        menu();
        printf("\nOpcion: ");
        scanf("%d", &opcion);
        getchar(); // Limpiar el buffer del newline después de scanf

        switch (opcion)
        {
        case 1:
            CrearFichero(nombreArchivo);
            break;
        case 2:
            InsertarDatos(nombreArchivo);
            break;
        case 3:
            VerDatos(nombreArchivo);
            break;
        case 4:
            BuscarDato(nombreArchivo);
            break;
        case 5:
            ModificarDato(nombreArchivo);
            break;
        case 6:
            exit = 1;
            break;
        default:
            printf("\nOpcion no valida\n");
        }
    }

    return 0;
}

void menu()
{
    printf("\nMenu:");
    printf("\n\t1. Crear fichero");
    printf("\n\t2. Insertar datos");
    printf("\n\t3. Ver datos");
    printf("\n\t4. Buscar dato");
    printf("\n\t5. Modificar dato");
    printf("\n\t6. Salir");
}

void CrearFichero(char *nombreFichero)
{
    FILE *Fichero = fopen(nombreFichero, "r");

    if (!Fichero)
    {
        Fichero = fopen(nombreFichero, "w");
        if (Fichero)
        {
            printf("\nArchivo '%s' creado!\n", nombreFichero);
            fclose(Fichero);
        }
        else
        {
            printf("\nError al crear el archivo '%s'!\n", nombreFichero);
        }
    }
    else
    {
        printf("\nEl fichero '%s' ya existe!\n", nombreFichero);
        fclose(Fichero);
    }
}

void InsertarDatos(char *nombreFichero)
{
    FILE *Fichero = fopen(nombreFichero, "a"); // Usamos "a" para añadir al final

    if (Fichero == NULL)
    {
        printf("\nError al abrir el fichero '%s'!\n", nombreFichero);
        printf("Por favor, asegúrese de que el archivo exista o intente crearlo primero.\n");
        return;
    }

    printf("\nDigita el nombre: ");
    scanf("%s", registro.Nombre);
    getchar(); // Limpiar el buffer del newline
    printf("\nDigita la edad: ");
    scanf("%d", &registro.Edad);
    getchar(); // Limpiar el buffer del newline
    printf("\nDigita el sueldo: ");
    scanf("%f", &registro.Sueldo);
    getchar(); // Limpiar el buffer del newline

    fwrite(&registro, sizeof(struct sRegistro), 1, Fichero);

    fclose(Fichero);
    printf("\nDatos insertados correctamente.\n");
}

void VerDatos(char *nombreFichero)
{
    FILE *Fichero = fopen(nombreFichero, "r");
    int numero = 1;

    if (Fichero == NULL)
    {
        printf("\nEl fichero '%s' no existe!\n", nombreFichero);
        return;
    }

    printf("\nNumero\tNombre\t\tEdad\tSueldo\n");

    while (fread(&registro, sizeof(struct sRegistro), 1, Fichero) == 1)
    {
        printf("%d\t%s\t\t%d\t%.2f\n", numero, registro.Nombre, registro.Edad, registro.Sueldo);
        numero++;
    }

    fclose(Fichero);
}

void BuscarDato(char *nombreFichero)
{
    FILE *Fichero = fopen(nombreFichero, "r");
    char nombreBuscar[25];
    int encontrado = 0;

    if (Fichero == NULL)
    {
        printf("\nEl fichero '%s' no existe!\n", nombreFichero);
        return;
    }

    printf("\nIngrese el nombre a buscar: ");
    scanf("%s", nombreBuscar);
    getchar(); // Limpiar el buffer

    while (fread(&registro, sizeof(struct sRegistro), 1, Fichero) == 1)
    {
        if (strcmp(registro.Nombre, nombreBuscar) == 0)
        {
            printf("\nRegistro encontrado:\n");
            printf("Nombre: %s\n", registro.Nombre);
            printf("Edad: %d\n", registro.Edad);
            printf("Sueldo: %.2f\n", registro.Sueldo);
            encontrado = 1;
            break; // Se encontró el registro, podemos salir del bucle
        }
    }

    fclose(Fichero);

    if (!encontrado)
    {
        printf("\nNo se encontró ningún registro con el nombre '%s'.\n", nombreBuscar);
    }
}

void ModificarDato(char *nombreFichero)
{
    FILE *Fichero = fopen(nombreFichero, "r+b"); // "r+b" para lectura y escritura en modo binario
    char nombreModificar[25];
    int encontrado = 0;
    long posicion;

    if (Fichero == NULL)
    {
        printf("\nEl fichero '%s' no existe!\n", nombreFichero);
        return;
    }

    printf("\nIngrese el nombre del trabajador cuyo sueldo desea modificar: ");
    scanf("%s", nombreModificar);
    getchar(); // Limpiar el buffer

    while (fread(&registro, sizeof(struct sRegistro), 1, Fichero) == 1)
    {
        if (strcmp(registro.Nombre, nombreModificar) == 0)
        {
            printf("\nRegistro encontrado:\n");
            printf("Nombre: %s\n", registro.Nombre);
            printf("Edad: %d\n", registro.Edad);
            printf("Sueldo actual: %.2f\n", registro.Sueldo);

            printf("\nIngrese el nuevo sueldo: ");
            scanf("%f", &registro.Sueldo);
            getchar(); // Limpiar el buffer

            // Volver al inicio del registro encontrado para escribir la modificación
            posicion = ftell(Fichero) - sizeof(struct sRegistro);
            fseek(Fichero, posicion, SEEK_SET);

            fwrite(&registro, sizeof(struct sRegistro), 1, Fichero);
            printf("\nSueldo modificado correctamente.\n");
            encontrado = 1;
            break;
        }
    }

    fclose(Fichero);

    if (!encontrado)
    {
        printf("\nNo se encontró ningún trabajador con el nombre '%s'.\n", nombreModificar);
    }
}
