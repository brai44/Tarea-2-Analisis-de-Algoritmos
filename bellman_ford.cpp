#ifndef BELLMAN_FORD
#define BELLMAN_FORD

#include <algorithm>
#include <cstdint>
#include <fstream>
#include <iostream>
#include <limits>
#include <sstream>
#include <string>
#include <vector>
#include <iomanip>
#include "utils.h"

template<typename T>
void bellmanFord(std::vector<Edge<T>>& graph, int n, int source_node, ASPSResult<T>& result){
    std::size_t V = n;
    const T INF = std::numeric_limits<T>::max();

    // distance[v] distancia minima conocida desde el origen hacia el vértice v
    std::vector<T> distance(V, INF);
    // pred[v] vertice anterior en el camino mas corto hacia v
    std::vector<int> pred(V, -1);

    // Distancia al origen es 0
    distance[source_node] = 0;

    // Iterar V-1 veces
    for(std::size_t i=1; i<V; i++){
        bool changes = false;

        //En cada iteracion pasamos por todas las aristas
        for(const auto& e : graph){
            // Condicion 1: El nodo origen de e debe haber sido descubierto (no INF)
            // Condicion 2: Formula de relajacion
            if(distance[e.source]!=INF && distance[e.source] + e.w < distance[e.destination]){
                distance[e.destination] = distance[e.source] + e.w;
                pred[e.destination] = e.source;
                changes = true;
            }
        }

        // Si no hubo cambios al pasar por todas las aristas se llego al óptimo
        if(!changes)
            break;
    }

    // Detectar ciclos de peso negativo con una pasada adicional
    for(const auto& e: graph){
        if(distance[e.source]!=INF && distance[e.source] + e.w < distance[e.destination]){
            std::cout<<"Ciclo de peso negativo encontrado.\n";
            result.negative_cycle = true;
            return;
        }
    }
    result.distances.push_back(distance);
    result.preds.push_back(pred);
}

template<typename T>
ASPSResult<T> asps_bellman_ford(std::vector<Edge<T>>& graph, int n){
    ASPSResult<T> result;

    //Reservar espacio para evitar reallocationes
    result.distances.reserve(n);
    result.preds.reserve(n);

    // Ejecutar Bellman-Ford para cada vertice como origen
    for(int i=0; i<n; i++){
        bellmanFord(graph, n, i, result);
    }
    return result;
}


void printPath_Bellman_Ford(int u, int v, const std::vector<int>& pred) {
    // Verificamos si hay camino
    if (pred[v] == -1 && u != v) {
        std::cout << "No existe camino de " << u + 1 << " a " << v + 1 << std::endl;
        return;
    }

    // Reconstruimos el camino desde v hacia atrás
    std::vector<int> path;
    int curr = v;
    
    while (curr != -1) {
        path.push_back(curr);
        if (curr == u) break; // Llegamos al origen, paramos
        curr = pred[curr];
    }

    // Imprimimos el camino
    std::reverse(path.begin(), path.end());

    for (size_t i = 0; i < path.size(); ++i) {
        std::cout << path[i] + 1 << (i < path.size() - 1 ? " -> " : "");
    }
    std::cout << std::endl;
}

template<typename T>
void print_distance_matrix(const ASPSResult<T>& result, int n) {
    if (!result.negative_cycle){
        const T INF = std::numeric_limits<T>::max();
        std::cout << "\n--- Matriz de Distancias ---\n" << std::endl;
        const int width = 4; 

        std::cout << "   ";
        for (int i = 0; i < n; i++){
            std::cout << std::setw(width) << i + 1;
        }

        std::cout << "\n  ┌";
        for (int k = 0; k < n * (width) + 1; k++) std::cout << "─";
        std::cout << "┐" << std::endl;

        for (std::size_t i = 0; i < n; i++) {
            std::cout << i + 1 << " │"; 

            for (std::size_t j = 0; j < n; j++) {
                if (result.distances[i][j] == INF){
                    std::cout << std::setw(width) << "INF";
                } else{
                    std::cout << std::setw(width) << result.distances[i][j];
                }
            }
            
            std::cout << " │" << std::endl; 
        }

        std::cout << "  └";
        for (int k = 0; k < n * (width) + 1; k++) std::cout << "─";
        std::cout << "┘" << std::endl;
    }
    
}
#endif