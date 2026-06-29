#ifndef GRAPH_PRINTER_H
#define GRAPH_PRINTER_H

#include "Graph.h"
#include <iostream>
#include <iomanip>
#include <limits>

class GraphPrinter {
public:
    template<typename T>
    static void print_adj(Graph<T>& g) {
        std::size_t n = g.get_q_nodes();
        const auto& adj = g.get_adj_ref();
        const T T_max = std::numeric_limits<T>::max();
        const int width = 4;

        std::cout << "   ";
        for (int i = 0; i < n; i++){
            std::cout << std::setw(width) << i + 1;
        }
        
        std::cout << "\n  ┌";
        for (int k = 0; k < n * (width) + 1; k++) std::cout << "─";
        std::cout << "┐" << std::endl;

        for (std::size_t i = 0; i < n; i++) {
            std::cout << i + 1<< " │"; 

            for (std::size_t j = 0; j < n; j++) {
                if (adj[i][j] == T_max){
                    std::cout << std::setw(width) << "INF";
                } else{
                    std::cout << std::setw(width) << adj[i][j];
                }
            }
            
            std::cout << " │" << std::endl; 
        }

        // 3. Línea inferior
        std::cout << "  └";
        for (int k = 0; k < n * (width) + 1; k++) std::cout << "─";
        std::cout << "┘" << std::endl;
    }

    template<typename T>
    static void print_edg(const Graph<T>& g) {
        std::cout << "\n[Nodo entrada], [Nodo salida], [Peso]" << std::endl;
        for(const auto& e : g.get_edge_list()) {
            std::cout << e.source << ", " << e.destination << ", " << e.w << std::endl;
        }
    }
};

#endif