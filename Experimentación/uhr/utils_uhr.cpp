/** Author: LELE */

#ifndef UTILS_UHR
#define UTILS_UHR

#include <algorithm>
#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

inline void validate_input(int argc, char *argv[], std::int64_t& runs)
{
    // Ahora esperamos solo 3 argumentos: ./programa <filename> <RUNS>
    if (argc != 3) {
        std::cerr << "Uso: " << argv[0] << " <filename> <RUNS>" << std::endl;
        std::cerr << "<filename>: nombre del archivo CSV de salida." << std::endl;
        std::cerr << "<RUNS>: número de ejecuciones por caso de prueba (mínimo 4)." << std::endl;
        std::exit(EXIT_FAILURE);
    }

    // Leer el número de ejecuciones
    try {
        runs = std::stoll(argv[2]);
    } catch (std::invalid_argument const& ex) {
        std::cerr << "Error: <RUNS> debe ser un número entero válido." << std::endl;
        std::exit(EXIT_FAILURE);
    } catch (std::out_of_range const& ex) {
        std::cerr << "Error: <RUNS> fuera de rango." << std::endl;
        std::exit(EXIT_FAILURE);
    }

    // Validar el mínimo de ejecuciones
    if (runs < 4) {
        std::cerr << "Error: <RUNS> debe ser al menos 4." << std::endl;
        std::exit(EXIT_FAILURE);
    }
}

inline void display_progress(std::int64_t u, std::int64_t v)
{
    const double progress = u / double(v);
    const std::int64_t width = 70;
    const std::int64_t p = width * progress;
    std::int64_t i;

    std::cerr << "\033[1m[";
    for (i = 0; i < width; i++) {
        if (i < p)
            std::cerr << "=";
        else if (i == p)
            std::cerr << ">";
        else
            std::cerr << " ";
    }
    std::cerr << "] " << std::int64_t(progress * 100.0) << "%\r\033[0m";
    std::cerr.flush();
}

inline void quartiles(std::vector<double>& data, std::vector<double>& q)
{
    q.resize(5);
    std::size_t n = data.size();
    std::size_t p;

    std::sort(data.begin(), data.end());

    if (n < 4) {
        std::cerr << "quartiles needs at least 4 data points." << std::endl;
        std::exit(EXIT_FAILURE);
    }

    // Get min and max
    q[0] = data.front();
    q[4] = data.back();

    // Find median
    if (n % 2 == 1) {
        q[2] = data[n / 2];
    } else {
        p = n / 2;
        q[2] = (data[p - 1] + data[p]) / 2.0;
    }

    // Find lower and upper quartiles
    if (n % 4 >= 2) {
        q[1] = data[n / 4];
        q[3] = data[(3 * n) / 4];
    } else {
        p = n / 4;
        q[1] = 0.25 * data[p - 1] + 0.75 * data[p];
        p = (3 * n) / 4;
        q[3] = 0.75 * data[p - 1] + 0.25 * data[p];
    }
}

#endif
