/**
* @file aleatorio.h
 * @brief Utilidades para la generación de números aleatorios.
 */
namespace aleatorio {

    /**
     * @brief Genera un número entero aleatorio.
     *
     * @param min Valor mínimo incluido.
     * @param max Valor máximo incluido.
     * @return Entero aleatorio en el rango [min, max].
     *
     * @example
     * @code
     * auto dado = aleatorio::entero(1, 6);
     * @endcode
     */
    int entero(int min, int max);

    /**
     * @brief Genera un número decimal aleatorio.
     *
     * @param min Valor mínimo del rango.
     * @param max Valor máximo del rango.
     * @return Número decimal aleatorio en el rango [min, max].
     *
     * @example
     * @code
     * auto temperatura =
     *     aleatorio::decimal(-10.0, 40.0);
     * @endcode
     */
    double decimal(double min, double max);

}