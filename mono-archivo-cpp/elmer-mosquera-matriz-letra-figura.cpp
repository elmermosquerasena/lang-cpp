// Salida y entrada por consola
#include <iostream>
#include <print>

// Libreria de aleatorio
#include <random>

// Texto
#include <string>
#include <string_view>

// Libreria de color
#include <format>
#include <iterator>
#include <optional>
#include <windows.h>

using std::print;
using std::println;
using std::cin;
using std::string;
using std::cout;
using std::endl;


struct Contexto {
	bool mostrar_matriz_letra{false};
	bool mostrar_matriz_figura{false};
	bool mt_letra_llena{false};
	bool mt_figura_llena{false};
	bool mostrar_sw_letra{false};
	bool mostrar_sw_figura{false};
	bool mostrar_primos_mt_letra{false};
	bool mostrar_rango_mt_figura{false};
};

struct Matrices {
	int matriz_letra[5][5] {};
	int matriz_figura[5][5] {};
};

namespace consola {

	enum class Color { Negro, Rojo, Verde, Amarillo, Azul, Magenta, Cyan, Blanco };

	constexpr int fg(Color c);

	constexpr int bg(Color c);

	struct Estilo {
		std::optional<Color> color;
		std::optional<Color> bg;
	};

	inline std::string colorear(std::string_view texto, Estilo);

	inline string colorear(const int numero, Estilo);

	inline string colorear(const double numero, Estilo);

}

namespace aleatorio {

	int entero(int min, int max);

	double decimal(double min, double max);
}

int menu_de_operaciones(Contexto contexto);

void salida_ejercicio(const Contexto& contexto, const Matrices &matrices);
void llenar_matriz_letra(Matrices &matrices);
void llenar_matriz_figura(Matrices &matrices);
void modificar_contexto(Contexto& contexto, int opcion);

int main() {

	SetConsoleOutputCP(CP_UTF8);

	Contexto contexto{};
	Matrices matrices{};

	int opcion{};

	do {
		system("cls");

		if (contexto.mostrar_matriz_letra || contexto.mostrar_matriz_figura) {
			salida_ejercicio(contexto,matrices);
		}

		opcion = menu_de_operaciones(contexto);
		modificar_contexto(contexto, opcion);

		if (opcion == 3) {
			llenar_matriz_letra(matrices);
		} else if (opcion == 4) {
			llenar_matriz_figura(matrices);
		}

	} while (opcion != 0);

	return 0;
}

void modificar_contexto(Contexto& contexto, int opcion) {
	switch (opcion) {
		case 0:
			break;
		case 1:
			contexto.mostrar_matriz_letra = contexto.mostrar_matriz_letra ? false : true;
			break;
		case 2:
			contexto.mostrar_matriz_figura = contexto.mostrar_matriz_figura ? false : true;
			break;
		case 3:
			contexto.mt_letra_llena = true;
			break;
		case 4:
			contexto.mt_figura_llena = true;
			break;
		case 5:
			contexto.mostrar_sw_letra = contexto.mostrar_sw_letra ? false : true;
			break;
		case 6:
			contexto.mostrar_sw_figura = contexto.mostrar_sw_figura ? false: true;
			break;
		case 7:
			contexto.mostrar_primos_mt_letra =  contexto.mostrar_primos_mt_letra ? false : true;
			break;
		case 8:
			contexto.mostrar_rango_mt_figura = contexto.mostrar_rango_mt_figura ? false: true;
			break;
		default:
			break;
	}
}

void llenar_matriz_letra(Matrices &matrices) {
	for (int i=0; i<5; i++) {
		for (int j=0; j<5; j++) {
			matrices.matriz_letra[i][j] = aleatorio::entero(1,100);
		}
	}
};

void llenar_matriz_figura(Matrices &matrices) {
	for (int i=0; i<5; i++) {
		for (int j=0; j<5; j++) {
			matrices.matriz_figura[i][j] = aleatorio::entero(1,100);
		}
	}
};

namespace aleatorio {

	int entero(int min, int max) {
		static std::random_device rd;
		static std::mt19937 gen(rd());

		return std::uniform_int_distribution<int>(
		           min, max
		       )(gen);
	}

	double decimal(double min, double max) {
		static std::random_device rd;
		static std::mt19937 gen(rd());

		return std::uniform_real_distribution<double>(
		           min, max
		       )(gen);
	}

}

int menu_de_operaciones(Contexto contexto) {
	// Operador ternario
	string mt_letra = contexto.mostrar_matriz_letra ? "OCULTAR" : "MOSTRAR";
	string mt_figura = contexto.mostrar_matriz_figura ? "OCULTAR" : "MOSTRAR";

	string sw_letra = contexto.mostrar_sw_letra ? "OCULTAR" : "MOSTRAR";
	string sw_figura = contexto.mostrar_sw_figura ? "OCULTAR" : "MOSTRAR";

	string letra_primos = contexto.mostrar_primos_mt_letra ? "OCULTAR" : "MOSTRAR";
	string figura_rango = contexto.mostrar_rango_mt_figura ? "OCULTAR" : "MOSTRAR";

	print("\n"
	      "\n                                        EJECICIO DE MATRICES"
	      "\n"
	      "\n1.                              {} MATRIZ DE NUMEROS 5x5 LETRA G"
	      "\n2.                              {} MATRIZ DE NUMEROS 5x5 FIGURA",
	      mt_letra, mt_figura);

	if (contexto.mostrar_matriz_letra) {
		print("\n3.                                     RELLENAR MATRIZ DE LETRA");
	}
	if (contexto.mostrar_matriz_figura) {
		print("\n4.                                     RELLENAR MATRIZ DE FIGURA");
	}

	if (contexto.mostrar_matriz_letra && contexto.mt_letra_llena) {
		print("\n5.                                {} AREA SOMBREADA DE LETRA", sw_letra);
	}
	if (contexto.mostrar_matriz_figura && contexto.mt_figura_llena) {
		print("\n6.                                {} AREA SOMBREADA DE FIGURA",sw_figura);
	}

	if (contexto.mostrar_matriz_letra && contexto.mt_letra_llena && contexto.mostrar_sw_letra) {
		print("\n7.            {} NUMEROS PRIMOS EN EL AREA SOMBREADA DE LA MATRIZ DE LETRA",letra_primos);
	}

	if (contexto.mostrar_matriz_figura && contexto.mt_figura_llena && contexto.mostrar_sw_figura) {
		print("\n8.            {} NUMEROS ENTRE 12 Y 16 EN EL AREA SOMBREADA DE LA MATRIZ DE FIGURA",figura_rango);
	}

	print("\n0.                                                 SALIR");

	int opcion{};

	bool esValido{};

	auto opcionInvalida = []() {
		std::println("OPCION INVALIDA");
	};

	do {
		print("\n>> ");
		cin >> opcion;

		switch (opcion) {
			case 0:
				cout<< "saliendo"  << endl;
				esValido = true;
				break;
			case 1:
				esValido = true;
				break;
			case 2:
				esValido = true;
				break;
			case 3:
				esValido = contexto.mostrar_matriz_letra ? true : false;
				break;
			case 4:
				esValido = contexto.mostrar_matriz_figura ? true : false;
				break;
			case 5:
				esValido = (contexto.mostrar_matriz_letra && contexto.mt_letra_llena) ? true : false;
				break;
			case 6:
				esValido = (contexto.mostrar_matriz_figura && contexto.mt_figura_llena) ? true : false;
				break;
			case 7:
				esValido = (contexto.mostrar_matriz_letra && contexto.mt_letra_llena && contexto.mostrar_sw_letra) ? true : false;
				break;
			case 8:
				esValido = (contexto.mostrar_matriz_figura && contexto.mt_figura_llena && contexto.mostrar_sw_figura) ? true : false;
				break;
			default:
				break;
		}

		if (!esValido) {
			opcionInvalida();
		}

	} while (!esValido);

	return opcion;

}

void salida_ejercicio(const Contexto& contexto, const Matrices &matrices) {

	int i{};
	// Cuantos numeros primos hay en el area sombreada de la matriz letra?
	int cant_n_primos_mt_letra{}, cant_n_en_rango_mt_figura{};

	// Existen almenos 2 numeros entre 12 y 16 en el area sombreada de la matriz figura
	bool hay_dos_n_en_rango_mt_figura{};

	auto mostrar_mt_letra = [&]() {
		for (int j=0; j<5; j++) {
			if  ( contexto.mostrar_sw_letra &&
			        (((i==0 || i==4) && (j!=0)) ||
			         ((j==0) && (i!=0) && (i!=4)) ||
			         ((j==4) && (i>1)) ||
			         ((i==2) && (j>1)))
			    ) {

				bool esPrimo{false};

				if (contexto.mostrar_primos_mt_letra && matrices.matriz_letra[i][j]) {
					esPrimo = true;
					for (int k{matrices.matriz_letra[i][j]-1}; k>1; k--) {
						if (((matrices.matriz_letra[i][j] % k) == 0) && k != 1) {
							esPrimo = false;
							break;
						}
					}
				}

				if (esPrimo && contexto.mostrar_primos_mt_letra) {
					cant_n_primos_mt_letra++;
					cout << consola::colorear(matrices.matriz_letra[i][j], {.bg = consola::Color::Verde}) << "\t";
				} else {
					cout << consola::colorear(matrices.matriz_letra[i][j], {.bg = consola::Color::Cyan}) << "\t";
				}
			} else {
				cout << matrices.matriz_letra[i][j] << "\t";
			}
		}
	};

	auto mostrar_mt_figura = [&]() {
		for (int j=0; j<5; j++) {
			if  (contexto.mostrar_sw_figura &&
			        (((j==1 || j==3) && (i<3)) ||
			         ((i==0 || i==2) && (j!=0 && j!=4)) ||
			         ((j==2) && (i>1 && i<4)))
			    ) {
				bool rango_valido{ false };

				if (contexto.mostrar_rango_mt_figura) {
					rango_valido = (matrices.matriz_figura[i][j] >= 12 && matrices.matriz_figura[i][j] <= 16);
				}

				if (rango_valido && contexto.mostrar_rango_mt_figura) {
					cant_n_en_rango_mt_figura++;
					cout << consola::colorear(matrices.matriz_figura[i][j], {.bg = consola::Color::Verde}) << "\t";
				} else {
					cout << consola::colorear(matrices.matriz_figura[i][j], {.bg = consola::Color::Cyan}) << "\t";
				}
			} else {
				cout << matrices.matriz_figura[i][j] << "\t";
			}
		}
	};

	for (i=0; i<5; i++) {

		if (contexto.mostrar_matriz_letra) {
			mostrar_mt_letra();
		}

		if (contexto.mostrar_matriz_letra && contexto.mostrar_matriz_figura) {
			cout << "\t\t";
		}

		if (contexto.mostrar_matriz_figura) {
			mostrar_mt_figura();
		}

		cout << endl;
	}

	if (contexto.mostrar_matriz_letra && contexto.mt_letra_llena && contexto.mostrar_sw_letra && contexto.mostrar_primos_mt_letra) {
		print("HAY {} NUMEROS PRIMOS EN EL EL", cant_n_primos_mt_letra);
	}

	if (contexto.mostrar_matriz_figura && contexto.mt_figura_llena && contexto.mostrar_sw_figura && contexto.mostrar_rango_mt_figura) {

		if((contexto.mostrar_matriz_letra && contexto.mt_letra_llena && contexto.mostrar_sw_letra && contexto.mostrar_primos_mt_letra) &&
		        (contexto.mostrar_matriz_figura && contexto.mt_figura_llena && contexto.mostrar_sw_figura && contexto.mostrar_rango_mt_figura)) {
			print("\t\t\t\t");
		} else if (contexto.mostrar_matriz_letra) {
			print("\t\t\t\t\t\t\t");
		}


		if (cant_n_en_rango_mt_figura > 2) {
			hay_dos_n_en_rango_mt_figura = true;
		}
		if (hay_dos_n_en_rango_mt_figura) {
			print("HAY ALMENOS 2 VALORES ENTRE 12 Y 15 ");
		} else {
			print("NO HAY ALMENOS 2 VALORES ENTRE 12 ");
		}
	}

	if (contexto.mostrar_matriz_letra && contexto.mt_letra_llena && contexto.mostrar_sw_letra && contexto.mostrar_primos_mt_letra) {
		print("\nAREA SOMBREADA DE LA MATRIZ LETRA");
	}

	if (contexto.mostrar_matriz_figura && contexto.mt_figura_llena && contexto.mostrar_sw_figura && contexto.mostrar_rango_mt_figura) {

		if((contexto.mostrar_matriz_letra && contexto.mt_letra_llena && contexto.mostrar_sw_letra && contexto.mostrar_primos_mt_letra) &&
		        (contexto.mostrar_matriz_figura && contexto.mt_figura_llena && contexto.mostrar_sw_figura && contexto.mostrar_rango_mt_figura)) {
			print("\t\t\t");
		} else if (contexto.mostrar_matriz_letra) {
			print("\n\t\t\t\t\t\t\t");
		} else {
			print("\n");
		}

		if (cant_n_en_rango_mt_figura > 2) {
			hay_dos_n_en_rango_mt_figura = true;
		}
		if (hay_dos_n_en_rango_mt_figura) {
			print("EN EL EL AREA SOMBREADA DE LA MATRIZ FIGURA");
		} else {
			print("Y 15 EN EL EL AREA SOMBREADA DE LA MATRIZ FIGURA");
		}

	}
};

namespace consola {

	constexpr int fg(Color c) {
		return 30 + static_cast<int>(c);
	}

	constexpr int bg(Color c) {
		return 40 + static_cast<int>(c);
	}

	inline std::string colorear(std::string_view texto, Estilo e = {}) {
		std::string out;
		out.reserve(texto.size() + 16);

		if (e.color)
			std::format_to(std::back_inserter(out),
			               "\033[{}m",
			               fg(*e.color));

		if (e.bg)
			std::format_to(std::back_inserter(out),
			               "\033[{}m",
			               bg(*e.bg));

		out.append(texto);
		out.append("\033[0m");

		return out;
	}

	inline std::string colorear(const int numero, Estilo e = {}) {
		std::string out;
		const std::string texto = std::to_string(numero);
		out.reserve(texto.size() + 16);

		if (e.color)
			std::format_to(std::back_inserter(out),
			               "\033[{}m",
			               fg(*e.color));

		if (e.bg)
			std::format_to(std::back_inserter(out),
			               "\033[{}m",
			               bg(*e.bg));

		out.append(texto);
		out.append("\033[0m");

		return out;
	}

	inline std::string colorear(const double numero, Estilo e = {}) {
		std::string out;
		const std::string texto = std::to_string(numero);
		out.reserve(texto.size() + 16);

		if (e.color)
			std::format_to(std::back_inserter(out),
			               "\033[{}m",
			               fg(*e.color));

		if (e.bg)
			std::format_to(std::back_inserter(out),
			               "\033[{}m",
			               bg(*e.bg));

		out.append(texto);
		out.append("\033[0m");

		return out;
	}
}