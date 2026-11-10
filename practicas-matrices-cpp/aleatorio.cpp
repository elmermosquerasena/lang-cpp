#include "aleatorio.h"
#include <random>

namespace aleatorio {

    int entero(int min, int max)
    {
        static std::random_device rd;
        static std::mt19937 gen(rd());

        return std::uniform_int_distribution<int>(
            min, max
        )(gen);
    }

    double decimal(double min, double max)
    {
        static std::random_device rd;
        static std::mt19937 gen(rd());

        return std::uniform_real_distribution<double>(
            min, max
        )(gen);
    }

}
