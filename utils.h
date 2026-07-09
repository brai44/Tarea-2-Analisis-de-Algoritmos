#ifndef UTILS_H
#define UTILS_H
#include <vector>

// Estructura que representa una arista (conexión) en el grafo
template<typename T>
struct Edge {
    int source;      // Nodo de origen
    int destination; // Nodo de destino
    T w;             // Peso de la arista
};

// Estructura para almacenar los resultados del algoritmo All-Pairs Shortest Path (APSP)
template<typename T>
struct ASPSResult {
    // Matriz de distancias mínimas entre todos los pares de nodos
    std::vector<std::vector<T>> distances;
    
    // Matriz de predecesores para reconstruir el camino más corto
    std::vector<std::vector<int>> preds;
    
    // Bandera para indicar si se encontró un ciclo negativo (el algoritmo no funcionaría)
    bool negative_cycle = false;
};

#endif