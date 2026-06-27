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

template<typename T>
struct Edge{
    size_t source, destination; //entero sin signo
    T w;
};

template<typename T>
struct Graph{
    std::vector<Edge<T>> edges;
    std::size_t num_nodes;

    Graph(void) : num_nodes(0){
    }

    Graph(const std::size_t n){
        num_nodes = n;
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
        num_nodes = n;

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
            
            Edge<T> actual_edge = {u, v, w};
            edges.push_back(actual_edge);
        }
    }

    // Imprimir lista de aristas
    void print(void) const {
        std::cout<<"Grafo con "<<num_node <<" nodos y "<<edges.size()<<" aristas:\n";
        for (const auto& edge : edges) {
            std::cout << "Origen: " << edge.source 
                      << " -> Destino: " << edge.destination 
                      << " | Peso: " << edge.w << "\n";
        }
    }
};

#endif