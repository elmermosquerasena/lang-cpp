#pragma once

#include <format>
#include <iterator>
#include <optional>
#include <string>

namespace consola {

    /**
     * @enum Color
     * @brief Representa los colores básicos compatibles con secuencias ANSI.
     *
     * Los valores de esta enumeración se utilizan para generar códigos ANSI
     * de color de texto (foreground) y color de fondo (background) en terminales.
     */
    enum class Color {
        Negro,
        Rojo,
        Verde,
        Amarillo,
        Azul,
        Magenta,
        Cyan,
        Blanco
    };

    /**
     * @brief Obtiene el código ANSI para el color del texto.
     *
     * Convierte un valor de la enumeración Color en el código ANSI
     * correspondiente para el color de primer plano.
     *
     * @param c Color deseado.
     * @return Código ANSI del color de texto.
     *
     * @example
     * @code
     * int codigo = consola::fg(consola::Color::Verde);
     * // Resultado: 32
     * @endcode
     */
    constexpr int fg(Color c) {
        return 30 + static_cast<int>(c);
    }

    /**
     * @brief Obtiene el código ANSI para el color de fondo.
     *
     * Convierte un valor de la enumeración Color en el código ANSI
     * correspondiente para el color de fondo.
     *
     * @param c Color deseado.
     * @return Código ANSI del color de fondo.
     *
     * @example
     * @code
     * int codigo = consola::bg(consola::Color::Azul);
     * // Resultado: 44
     * @endcode
     */
    constexpr int bg(Color c) {
        return 40 + static_cast<int>(c);
    }

    /**
     * @struct Estilo
     * @brief Define los atributos visuales aplicables a un texto.
     *
     * Permite especificar opcionalmente un color de texto
     * y un color de fondo.
     */
    struct Estilo {

        /**
         * @brief Color del texto (foreground).
         */
        std::optional<Color> color;

        /**
         * @brief Color de fondo (background).
         */
        std::optional<Color> bg;
    };

    /**
     * @brief Aplica formato ANSI a un texto.
     *
     * Genera una cadena que incluye las secuencias ANSI necesarias
     * para mostrar el texto con los colores especificados.
     * Al final del texto se agrega automáticamente la secuencia
     * de reinicio ANSI ("\\033[0m").
     *
     * @param texto Texto a colorear.
     * @param e Estilo a aplicar. Si no se especifica, se utiliza el estilo por defecto.
     * @return Cadena formateada con secuencias ANSI.
     *
     * @note Requiere una terminal compatible con ANSI.
     *
     * @example Texto en rojo
     * @code
     * std::cout << consola::colorear(
     *     "Error",
     *     {.color = consola::Color::Rojo}
     * );
     * @endcode
     *
     * @example Texto amarillo sobre fondo azul
     * @code
     * consola::Estilo estilo;
     * estilo.color = consola::Color::Amarillo;
     * estilo.bg = consola::Color::Azul;
     *
     * std::cout << consola::colorear(
     *     "Advertencia",
     *     estilo
     * );
     * @endcode
     *
     * @example Uso con inicialización directa
     * @code
     * std::cout << consola::colorear(
     *     "Proceso completado",
     *     {
     *         .color = consola::Color::Verde,
     *         .bg    = consola::Color::Negro
     *     }
     * );
     * @endcode
     */
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

    /**
     * @brief Aplica formato ANSI a un texto.
     *
     * Genera una cadena que incluye las secuencias ANSI necesarias
     * para mostrar el nummero con los colores especificados.
     * Al final del numero se agrega automáticamente la secuencia
     * de reinicio ANSI ("\\033[0m").
     *
     * @param numero Numero a colorear.
     * @param e Estilo a aplicar. Si no se especifica, se utiliza el estilo por defecto.
     * @return Cadena formateada con secuencias ANSI.
     *
     * @note Requiere una terminal compatible con ANSI.
     *
     * @example Numero en rojo
     * @code
     * std::cout << consola::colorear(
     *     12,
     *     {.color = consola::Color::Rojo}
     * );
     * @endcode
     *
     * @example Numero amarillo sobre fondo azul
     * @code
     * consola::Estilo estilo;
     * estilo.color = consola::Color::Amarillo;
     * estilo.bg = consola::Color::Azul;
     *
     * std::cout << consola::colorear(
     *     5,
     *     estilo
     * );
     * @endcode
     *
     * @example Uso con inicialización directa
     * @code
     * std::cout << consola::colorear(
     *     7,
     *     {
     *         .color = consola::Color::Verde,
     *         .bg    = consola::Color::Negro
     *     }
     * );
     * @endcode
     */
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


    /**
     * @brief Aplica formato ANSI a un texto.
     *
     * Genera una cadena que incluye las secuencias ANSI necesarias
     * para mostrar el nummero con los colores especificados.
     * Al final del numero se agrega automáticamente la secuencia
     * de reinicio ANSI ("\\033[0m").
     *
     * @param numero Numero a colorear.
     * @param e Estilo a aplicar. Si no se especifica, se utiliza el estilo por defecto.
     * @return Cadena formateada con secuencias ANSI.
     *
     * @note Requiere una terminal compatible con ANSI.
     *
     * @example Numero en rojo
     * @code
     * std::cout << consola::colorear(
     *     12,
     *     {.color = consola::Color::Rojo}
     * );
     * @endcode
     *
     * @example Numero amarillo sobre fondo azul
     * @code
     * consola::Estilo estilo;
     * estilo.color = consola::Color::Amarillo;
     * estilo.bg = consola::Color::Azul;
     *
     * std::cout << consola::colorear(
     *     5,
     *     estilo
     * );
     * @endcode
     *
     * @example Uso con inicialización directa
     * @code
     * std::cout << consola::colorear(
     *     7,
     *     {
     *         .color = consola::Color::Verde,
     *         .bg    = consola::Color::Negro
     *     }
     * );
     * @endcode
     */
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

#include <string_view>