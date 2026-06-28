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
#include "utils.h"

template<typename T>
void bellmanFord(std::vector<Edge<T>>& graph, int n, int source_node, ASPSResult<T>& result){
    std::size_t V = n;
    const T INF = std::numeric_limits<T>::max();

    // Inicializar distancia desde source a los demas vertices como infinito
    std::vector<T> distance(V, INF);
    // Vector contiene el predecesor para llegar al nodo con indice v
    // pred[1] es el paso anterior para llegar al nodo 1
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

    for(const auto& e: graph){
        if(distance[e.source]!=INF && distance[e.source] + e.w < distance[e.destination]){
            std::cout<<"Ciclo de peso negativo encontrado.\n";
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

    for(int i=0; i<n; i++){
        bellmanFord(graph, n, i, result);
    }
    return result;
}


void printPath_Bellman_Ford(int u, int v, const std::vector<int>& pred) {
    // 1. Verificamos si hay camino
    if (pred[v] == -1 && u != v) {
        std::cout << "No existe camino de " << u << " a " << v << std::endl;
        return;
    }

    // 2. Reconstruimos el camino desde v hacia atrás
    std::vector<int> path;
    int curr = v;
    
    while (curr != -1) {
        path.push_back(curr);
        if (curr == u) break; // Llegamos al origen, paramos
        curr = pred[curr];
    }

    // 3. Imprimimos el camino (como lo guardamos al revés, lo invertimos)
    std::reverse(path.begin(), path.end());

    for (size_t i = 0; i < path.size(); ++i) {
        std::cout << path[i] +1<< (i < path.size() - 1 ? " -> " : "");
    }
    std::cout << std::endl;
}

template<typename T>
void print_distance_matrix(const ASPSResult<T>& result, int n) {
    const T INF = std::numeric_limits<T>::max();
    std::cout << "\n--- Matriz de Distancias ---" << std::endl;

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (result.distances[i][j] == INF) {
                std::cout << " INF ";
            } else {
                std::cout << " " << result.distances[i][j] << " ";
            }
        }
        std::cout << std::endl;
    }
}
#endif