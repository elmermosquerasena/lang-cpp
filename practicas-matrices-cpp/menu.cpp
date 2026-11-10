#include "menu.h"
#include <iostream>

using std::cout;
using std::endl;
// using std::cin;

namespace menu {
    void principal() {
        cout << "\n               Menu "
                "\n 1) Rellenar la matrices de aleatorios entre 1 y 100"
                "\n 2) Letra: Mostrar la cantidad de números"
                "\n         primos del área sombreada."
                "\n 3) Figura: Mostrar si al  menos existen dos"
                "\n          numero en el rango de  12 a 16 "
                "\n 0) Salir "
                "\n Seleccione una opcion"
                "\n >> ";
    }

}
