#include <iostream>
#include <vector>
#include <cstdlib>  // Para rand() y srand()
#include <ctime>    // Para time()

using namespace std;

// Función para llenar un arreglo con entrada del usuario
void llenarArreglo(vector<int>& arr) {
    for (int i = 0; i < arr.size(); i++) {
        cout << "Ingrese el elemento " << i + 1 << ": ";
        cin >> arr[i];
    }
}

// Función para mostrar un arreglo
void mostrarArreglo(const vector<int>& arr) {
    for (int num : arr) {
        cout << num << " ";
    }
    cout << endl;
}

// Opción 1: Mostrar arreglo en orden inverso
void opcion1() {
    vector<int> arr(7);
    llenarArreglo(arr);
    
    cout << "Elementos en orden inverso: ";
    for (int i = arr.size() - 1; i >= 0; i--) {
        cout << arr[i] << " ";
    }
    cout << endl;
}

// Opción 2: Invertir el arreglo y mostrarlo
void opcion2() {
    vector<int> arr(7);
    llenarArreglo(arr);
    
    // Invertir el arreglo
    int n = arr.size();
    for (int i = 0; i < n / 2; i++) {
        swap(arr[i], arr[n - 1 - i]);
    }

    cout << "Arreglo invertido: ";
    mostrarArreglo(arr);
}

// Opción 3: Arreglo con números aleatorios y suma de posiciones pares
void opcion3() {
    vector<int> arr(10);
    srand(time(0));  // Semilla para números aleatorios

    // Llenar el arreglo con números aleatorios del 1 al 20
    for (int i = 0; i < arr.size(); i++) {
        arr[i] = rand() % 20 + 1;
    }

    cout << "Arreglo generado aleatoriamente: ";
    mostrarArreglo(arr);

    // Sumar los números en posiciones pares
    int suma = 0;
    for (int i = 0; i < arr.size(); i += 2) {
        suma += arr[i];
    }

    cout << "Suma de elementos en posiciones pares: " << suma << endl;
}

int main() {
    int opcion;
    do {
        cout << "\nMenu de opciones:\n";
        cout << "1. Mostrar arreglo en orden inverso\n";
        cout << "2. Invertir y mostrar el arreglo\n";
        cout << "3. Generar y sumar posiciones pares en un arreglo\n";
        cout << "4. Salir\n";
        cout << "Seleccione una opción: ";
        cin >> opcion;

        switch (opcion) {
            case 1:
                opcion1();
                break;
            case 2:
                opcion2();
                break;
            case 3:
                opcion3();
                break;
            case 4:
                cout << "Saliendo del programa...\n";
                break;
            default:
                cout << "Opción no válida. Intente de nuevo.\n";
        }
    } while (opcion != 4);

    return 0;
}
