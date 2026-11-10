#include "color.h"
#include "aleatorio.h"
#include "menu.h"
#include <iostream>

#ifdef _WIN32
#include <windows.h>
#endif


using std::cout;
using std::endl;
using std::cin;
using consola::colorear;
using consola::Color;

struct Opcion {
    bool mostrar_primos{false};
    bool mostrar_vals_12_16{false};
};

int main() {

    #ifdef _WIN32
        SetConsoleOutputCP(CP_UTF8);
    #endif


    int matriz_letra[5][5]{};
    int matriz_figura[5][5]{};

    // Funcion lamba para mostrar la matriz con las figuras
    auto mostrar_matrices = [&](Opcion opcion) {
        for (int i=0; i<5; i++) {
            for (int j=0; j<5; j++) {
                if  (
                        ((i==0 || i==4) && (j!=0)) ||
                        ((j==0) && (i!=0) && (i!=4)) ||
                        ((j==4) && (i>1)) ||
                        ((i==2) && (j>1))
                    ) {

                    bool esPrimo{true};

                    if (opcion.mostrar_primos) {

                        for (int k{matriz_letra[i][j]-1}; k>1; k--) {
                            if (((matriz_letra[i][j] % k) == 0) && k != 1) {
                                esPrimo = false;
                                break;
                            }
                        }

                    }

                    if (esPrimo && opcion.mostrar_primos) {
                        cout << colorear(matriz_letra[i][j], {.bg = Color::Verde}) << "\t";
                    } else {
                        cout << colorear(matriz_letra[i][j], {.bg = Color::Cyan}) << "\t";
                    }
                } else {
                    cout << matriz_letra[i][j] << "\t";
                }
            }
            cout << "\t\t";
            for (int j=0; j<5; j++) {
                if  (
                        ((j==1 || j==3) && (i<3)) ||
                        ((i==0 || i==2) && (j!=0 && j!=4)) ||
                        ((j==2) && (i>1 && i<4))
                    ) {
                    bool rango_valido{ false };

                    if (opcion.mostrar_vals_12_16) {
                        rango_valido = (matriz_figura[i][j] >= 12 && matriz_figura[i][j] <= 16);
                    }

                    if (rango_valido && opcion.mostrar_vals_12_16) {
                        cout << colorear(matriz_figura[i][j], {.bg = Color::Verde}) << "\t";
                    } else {
                        cout << colorear(matriz_figura[i][j], {.bg = Color::Cyan}) << "\t";
                    }
                } else {
                    cout << matriz_figura[i][j] << "\t";
                }
            }
            cout << endl;
        }
    };

    auto llenar_matrices = [&]() {
        for (int i=0; i<5; i++) {
            for (int j=0; j<5; j++) {
                matriz_letra[i][j] = aleatorio::entero(1,100);
                matriz_figura[i][j] = aleatorio::entero(1,100);
            }
        }
    };

    Opcion opcion{};
    int control{0};

    do {
        mostrar_matrices(opcion);
        menu::principal();
        cin >> control;
        while ( control < 0 || control > 3) {
            cout << "opcion invalida\n>> ";
            cin >> control;
        }

        switch (control) {
            case 0:
                break;
            case 1:
                llenar_matrices();
                break;
            case 2:
                opcion.mostrar_primos = true;
                break;
            case 3:
                opcion.mostrar_vals_12_16 = true;
                break;
            default:
                break;
        }

    } while (control != 0);


    #ifdef _WIN32
        system("pause");
    #endif

    return 0;
}