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

template<typename T>
struct Graph{
    std::vector<std::vector<T>> adj;
    
    Graph(void){
    }

    // Crear matriz
    Graph(const std::size_t n){
        adj.resize(
            n,
            std::vector<T>(
                n,
                std::numeric_limits<T>::max()
            )
        );

        // Recorre la diag principal y asigna valor por defecto (0)
        for(std::size_t i=0; i<n; i++)
            adj[i][i] = T();
    }

    // Lectura desde archivo
    Graph(const std::string filename, bool zero_indexed = true){
        std::ifstream input(filename); // Abre el archivo txt
        std::string line;

        std::getline(input, line);     // Lee solo la primera linea
        std::stringstream ss(line);    // Convierte esa linea en un stream para extraer strings

        std::size_t n, m, u, v;
        T w;

        // extraemos la primera linea que contiene 
        // [nodos de salida] [nodos de llegada] [cantidad de aristas]
        ss >> n >> n >> m; 
        
        // Crear matriz con elementos inf
        adj.resize(
            n,
            std::vector<T>(
                n,
                std::numeric_limits<T>::max()
            )
        );

        // Recorre la diag principal y asigna valor por defecto (0)
        for (std::size_t i = 0; i<n; i++)
            adj[i][i] = T();
        
        // Ciclo que se repite una vez por arista
        while(m--){
            std::getline(input, line);
            ss.clear();
            ss.str(std::string());
            ss.str(line);
            
            // [nodo de origen] [nodo de desitno] [peso]
            ss >> u >> v >> w;

            if(zero_indexed){
                u--;
                v--;
            }

            // Avoid loops
            if (u==v)
                continue;

            adj[u][v] = std::min(adj[u][v], w);
            // adj[v][u] = std::min(adj[v][u], w); grafo dirigido
        }
    }

    std::vector<T>& operator[](std::size_t i){
        return adj[i];
    }

    std::size_t size(void){
        return adj.size();
    }

    // Imprimir matriz de adyacencia
    void print(void){
        std::size_t n = size();
        const T T_max = std::numeric_limits<T>::max();

        for(std::size_t i=0;i<n;i++){
            std::cout<<(adj[i][0] == T_max ? -1 : adj[i][0]);
            
            for(std::size_t j=1;j<n;j++){
                std::cout<<" "<<(adj[i][j] == T_max ? -1 : adj[i][j]);
            }

            std::cout<<std::endl;
        }
    }
};

#endif