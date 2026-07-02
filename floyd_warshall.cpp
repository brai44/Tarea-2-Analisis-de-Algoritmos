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
    const T INF = 1e8; // Valor "infinito" que representa ausencia de arista.
    bool size_limit = n < 8; // Solo se reconstruyen caminos para grafos pequeños.
 

    // Inicialización de la matriz mask (reconstrucción de caminos).
    // mask[i][j] = j si hay arista directa i->j, -1 si no hay conexión inicial.
    std::vector<std::vector<int>> mask;
    if (size_limit) {
        mask.assign(n, std::vector<int>(n, -1));
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (adj[i][j] < INF) mask[i][j] = j;
            }
        }
    }
 
    // Núcleo del algoritmo de Floyd-Warshall: programación dinámica
    // sobre el vértice intermedio k.
    for (std::size_t k = 0; k < n; k++) {
        for (std::size_t i = 0; i < n; i++) {
            // Poda: si no hay camino de i a k
            if (adj[i][k] > INF) continue;
            for (std::size_t j = 0; j < n; j++) {
                if (adj[k][j] < INF) {
                    // Relajación aristas
                    if (adj[i][j] > adj[i][k] + adj[k][j]) {
                        adj[i][j] = adj[i][k] + adj[k][j];
                        if (size_limit) {
                            // El siguiente salto desde i hacia j pasa a ser el mismo que el siguiente salto desde i hacia k.
                            mask[i][j] = mask[i][k];
                        }
                    }
                }
            }
        }
    }
 
    // Detección de ciclos negativos
    bool has_negative_cycle = false;
    for (int i = 0; i < n; i++) {
        if (adj[i][i] < 0) {
            has_negative_cycle = true;
            std::cout << "ADVERTENCIA: Grafo contiene ciclos negativos. Caminos indefinidos." << std::endl;
            break;
        }
    }
 
    // Si hay ciclo negativo, se invalida toda la matriz mask marcando -2
    // en cada celda, ya que ningún camino reconstruido sería confiable.
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

void printPath_Floyd_Warshall(int u, int v, std::vector<std::vector<int>>& mask)
{
    // Si la matriz era muy grande no hacemos nada
    if (mask.size() != 0) {
        // Si no hay camino
        if (mask[u][v] == -1) {
            std::cout << "No path\n";
        // Si hay ciclo negativos
        } else if (mask[u][v] == -2) {
            std::cout << "No path (debido a ciclo negativo)\n" << std::endl;
        } else {
            // Reconstrucción del camino salto a salto hasta alcanzar v.
            std::vector<int> path = { u };
            while (u != v) {
                u = mask[u][v];
                path.push_back(u);
            }
            int n = path.size();
            for (int i = 0; i < n - 1; i++)
                std::cout << path[i] + 1 << " -> ";
            std::cout << path[n - 1] + 1 << std::endl;
        }
    }
}
#endif