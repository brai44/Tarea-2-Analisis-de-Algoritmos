#ifndef CREATE_GRAPH_H
#define CREATE_GRAPH_H

#include "Graph.h"
#include <random>
#include <set>
#include <sstream>
#include <fstream>

class CreateGraph {
public:
    template<typename T>
    static void create_random_density(Graph<T>& g, int n, int e) {
        g.init(n);
        std::mt19937 gen(std::random_device{}());
        std::uniform_int_distribution<int> dist_nodos(0, n - 1);
        std::uniform_real_distribution<double> dist_pesos(1.0, 100.0);

        std::set<std::pair<int, int>> aristas;
        while(aristas.size() < (size_t)e) {
            int u = dist_nodos(gen);
            int v = dist_nodos(gen);
            if (u == v || aristas.count({u, v})) continue;

            aristas.insert({u, v});
            g.add_edge(u, v, (T)dist_pesos(gen));
        }
    }

    // Carga desde archivo MTX
    template<typename T>
    static void load_file(Graph<T>& g, const std::string& filename, bool zero_indexed = true) {
        std::ifstream input(filename);
        int q_nodes=0, q_edges=0;
        std::string line;
        std::getline(input, line);

        std::stringstream ss(line);
        ss >> q_nodes >> q_nodes >> q_edges; // q_nodes, q_nodes, q_edges

        g.init(q_nodes);

        int u, v;
        T w;
        while (std::getline(input, line)) {
            std::stringstream ss2(line);
            ss2 >> u >> v >> w;

            if (zero_indexed) {
                u--; v--;
            }
            g.add_edge(u, v, w);
        }
    }
};

#endif