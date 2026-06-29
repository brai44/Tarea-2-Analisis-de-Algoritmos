#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <limits>
#include "utils.h"

template<typename T>
class Graph {
private:
    int q_nodes = 0;
    std::vector<std::vector<T>> adj;
    std::vector<Edge<T>> edge_list;

public:
    Graph() = default;

    void init(int n) {
        q_nodes = n;
        adj.assign(n, std::vector<T>(n, std::numeric_limits<T>::max()));
        for(int i = 0; i < n; i++) adj[i][i] = T(); // Distancia al mismo nodo es 0
        edge_list.clear();
    }

    void add_edge(int u, int v, T w) {
        adj[u][v] = std::min(adj[u][v], w);
        edge_list.push_back({u, v, w});
    }

    // Getters
    int get_q_nodes() const { 
        return q_nodes; 
    }
    std::vector<std::vector<T>>& get_adj_ref() {
        return adj; 
    }
    std::vector<std::vector<T>> get_adj_copy(){
        return adj;
    } 
    std::vector<Edge<T>>& get_edge_list() { 
        return edge_list; 
    }
    std::vector<Edge<T>> get_edge_list_copy(){
        return edge_list;
    }
};

#endif