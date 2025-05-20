//187855 noe castillo gaytan
#include <iostream>
using namespace std;

int main() {
    enum datos {
        num1 = 5, 
        num2,    // 6
        num3,    // 7
        num4 = 30, 
        num5     // 31
    };
    
    cout << "Numeros pares desde num1 hasta num4:" << endl;
    
    for (int i = num1; i <= num4; i++) {
        if (i % 2 == 0) {
            cout << i << " ";
        }
    }
    
    cout << endl;
    
    return 0;
}