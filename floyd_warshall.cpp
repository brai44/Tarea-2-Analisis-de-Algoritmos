#ifndef FLOYD_WARSHALL
#define FLOYD_WARSHALL

#include <algorithm>
#include <cstdint>
#include <fstream>
#include <iostream>
#include <limits>
#include <sstream>
#include <string>
#include <vector>
#include <climits>
#include <limits> 

template<typename T>
std::vector<std::vector<int>> floydWarshall(std::vector<std::vector<T>>& adj) {
    std::size_t n = adj.size();
    const T INF = 1e8; 
    bool size_limit = n < 8;

    std::vector<std::vector<int>> mask;
    if (size_limit) {
        mask.assign(n, std::vector<int>(n, -1));
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (adj[i][j] < INF) mask[i][j] = j;
            }
        }
    }

    for (std::size_t k = 0; k < n; k++) {
        for (std::size_t i = 0; i < n; i++) {
            if (adj[i][k] > INF) continue;
            for (std::size_t j = 0; j < n; j++) {
                if (adj[k][j] < INF) {
                    if (adj[i][j] > adj[i][k] + adj[k][j]) {
                        adj[i][j] = adj[i][k] + adj[k][j];
                        if (size_limit) {
                            mask[i][j] = mask[i][k];
                        }
                    }
                }
            }
        }
    }

    bool has_negative_cycle = false;
    for (int i = 0; i < n; i++) {
        if (adj[i][i] < 0) {
            has_negative_cycle = true;
            std::cout << "ADVERTENCIA: Grafo contiene ciclos negativos. Caminos indefinidos." << std::endl;
            break; 
        }
    }

    if (has_negative_cycle) {
        if (size_limit) {
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {
                    mask[i][j] = -2; 
                }
            }
        }
    }

    return mask;
}

void printPath_Floyd_Warshall(int u, int v , std::vector<std::vector<int>>& mask) 
{ 
    if (mask.size() != 0){
        if (mask[u][v] == -1) {
            std::cout << "No path";
        } else if (mask[u][v] == -2) {
            std::cout << "No path (debido a ciclo negativo)" << std::endl;
        } else {
            std::vector<int> path = { u }; 
            while (u != v) { 
                u = mask[u][v]; 
                path.push_back(u); 
            } 
            int n = path.size(); 
            for (int i = 0; i < n - 1; i++) 
                std::cout << path[i] << " -> "; 
            std::cout << path[n - 1] << std::endl; 
        }
    }
} 

#endif