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
    bool size_limit = n < 8;
    std::vector<std::vector<int>> mask;
    if (size_limit){
        mask.assign(n, std::vector<int>(n));
        for (int i = 0; i < n; i++){
            for (int j = 0; j < n ; j++){
                if (adj[i][j] == std::numeric_limits<T>::max()) 
                    mask[i][j] = -1; 
                else
                    mask[i][j] = j; 
            }
        }
    }

    const T T_max = std::numeric_limits<T>::max();

    for (std::size_t k = 0; k < n; k++) {
        for (std::size_t i = 0; i < n; i++) {
            for (std::size_t j = 0; j < n; j++) {
                if  (adj[i][k] != T_max && adj[k][j] != T_max) {
                    if (T_max - adj[i][k] < adj[k][j]) {
                    } else {
                        if (adj[i][j] > adj[i][k] + adj[k][j]) {
                            adj[i][j] = adj[i][k] + adj[k][j];
                            if (size_limit){
                                mask[i][j] = mask[i][k]; 
                            }
                        }
                    }
                }
            }
        }
    }

    return mask;
}

void printPath(int u, int v , std::vector<std::vector<int>>& mask) 
{ 
    bool bool_path = true;
    if (mask[u][v] == -1) {
        std::cout << "No path";
        bool_path = false;
    }

    std::vector<int> path = { u }; 
    while (u != v) { 
        u = mask[u][v]; 
        path.push_back(u); 
    } 

    if (bool_path){
        int n = path.size(); 
        for (int i = 0; i < n - 1; i++) 
            std::cout << path[i] << " -> "; 
        std::cout << path[n - 1] << std::endl; 
    }
} 

#endif