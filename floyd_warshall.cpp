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
void floydWarshall(std::vector<std::vector<T>>& adj) {
    std::size_t n = adj.size();
    bool size_limit = n < 8;
    if (n < 8){
        std::vector<std::vector<int>> mask;
        for (int i = 0; i < n; i++){
            for (int j = 0; j < 0 ; j++){
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
                        }
                    }
                }
            }
        }
    }
}

#endif