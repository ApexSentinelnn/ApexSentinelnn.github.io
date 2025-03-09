#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <windows.h>
#include <iomanip>
using namespace std;

void setColor(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void caso1() {
    const int tam = 9;
    int arr1[tam];
    double arr2[tam], arr3[tam];
    srand(time(0));
    
    cout << "\nArreglo 1: ";
    for (int i = 0; i < tam; i++) {
        arr1[i] = 20 + rand() % 31;
        cout << arr1[i] << " ";
    }
    
    cout << "\nArreglo 2 (Raiz cuadrada): ";
    for (int i = 0; i < tam; i++) {
        arr2[i] = sqrt(arr1[i]);
        cout << fixed << setprecision(2) << arr2[i] << " ";
    }
    
    cout << "\nArreglo 3 (Suma): ";
    for (int i = 0; i < tam; i++) {
        arr3[i] = arr1[i] + arr2[i];
        if ((int)arr3[i] % 2 == 0)
            setColor(9);
        else
            setColor(4);
        cout << arr3[i] << " ";
    }
    setColor(7);
    cout << "\n";
}

void caso2() {
    string nombre;
    double calificaciones[4], promedio = 0;
    
    cout << "\nIngrese el nombre del estudiante: ";
    cin.ignore();
    getline(cin, nombre);
    
    cout << "Ingrese sus 4 calificaciones:\n";
    for (int i = 0; i < 4; i++) {
        cout << "Calificacion " << i + 1 << ": ";
        cin >> calificaciones[i];
        promedio += calificaciones[i];
    }
    promedio /= 4;
    
    cout << "\nNombre                  Calificaciones       Promedio\n";
    cout << nombre << "  ";
    for (int i = 0; i < 4; i++) {
        if (calificaciones[i] < 7)
            setColor(4);
        else
            setColor(2);
        cout << calificaciones[i] << " ";
    }
    if (promedio < 7)
        setColor(4);
    else
        setColor(2);
    cout << fixed << setprecision(2) << promedio << "\n";
    setColor(7);
}

int main() {
    int opcion;
        printf("******************************************************\n");
        printf("*                      HECHO POR:                    *\n");
        printf("*              Noe Castillo Gaytan. 187855           *\n");
        printf("******************************************************\n");
    do {
        cout << "\nMenu de opciones:\n";
        cout << "1. Caso con 3 arreglos numericos\n";
        cout << "2. Caso con 2 arreglos\n";
        cout << "3. Salir\n";
        cout << "Seleccione una opcion: ";
        cin >> opcion;
        
        switch (opcion) {
            case 1:
                caso1();
                break;
            case 2:
                caso2();
                break;
            case 3:
                cout << "Saliendo...\n";
                break;
            default:
                cout << "Opcion no válida, intente nuevamente.\n";
        }
    } while (opcion != 3);
    
    return 0;
}
