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
#include "edge.h"

template<typename T>
std::vector<int>bellmanFord(std::vector<Edge<T>>& graph, int source_node){
    std::size_t V = graph.size()
    const T INF = std::numeric_limits<T>::max();

    // Inicializar distancia desde source a los demas vertices como infinito
    std::vector<int> distance(V, INF);
    // Vector contiene el predecesor para llegar al nodo con indice v
    // pred[1] es el paso anterior para llegar al nodo 1
    std::vector<int> pred(V, -1)

    // Distancia al origen es 0
    distance[source_node] = T()

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
    return;
}

#endif