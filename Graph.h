#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <limits>
#include "utils.h"

template<typename T>
class Graph {
private:
    int q_nodes = 0;                     // Cantidad total de nodos
    std::vector<std::vector<T>> adj;     // Matriz de pesos entre nodos
    std::vector<Edge<T>> edge_list;      // Lista con todas las aristas

public:
    Graph() = default;

    // Prepara el grafo para N nodos
    void init(int n) {
        q_nodes = n;
        // Llena la matriz con "infinito"
        adj.assign(n, std::vector<T>(n, std::numeric_limits<T>::max()));
        // La distancia de un nodo a sí mismo es 0
        for(int i = 0; i < n; i++) adj[i][i] = T(); 
        edge_list.clear();
    }

    // Agrega una conexión entre dos nodos con un peso
    void add_edge(int u, int v, T w) {
        // Guarda el menor peso si ya existía una conexión
        adj[u][v] = std::min(adj[u][v], w);
        edge_list.push_back({u, v, w});
    }

    // --- Getters ---

    int get_q_nodes() const { 
        return q_nodes; 
    }

    // Retorna la matriz de adyacencia
    std::vector<std::vector<T>>& get_adj_ref() {
        return adj; 
    }

    std::vector<std::vector<T>> get_adj_copy(){
        return adj;
    } 

    // Retorna la lista de aristas
    std::vector<Edge<T>>& get_edge_list() { 
        return edge_list; 
    }

    std::vector<Edge<T>> get_edge_list_copy(){
        return edge_list;
    }
};

#endif