#ifndef GRAPH
#define GRAPH


#include <iostream>
#include <vector>
#include <sstream>
#include <fstream>
#include <utility>
#include <random>
#include <limits>


template<typename T>

class Graph{
private:
    int q_nodes = 0;
    int q_edges = 0;
    std::vector<std::vector<T>> adj;

public:

    Graph() = default;

    // Carga un archivo mtx
    void load_file(const std::string filename, bool zero_indexed = true) {
        std::ifstream input(filename);

        std::string line;
        std::getline(input, line);
        
        std::stringstream ss(line);
        ss >> q_nodes >> q_nodes >> q_edges; 

        adj.assign(q_nodes, std::vector<T>(q_nodes, std::numeric_limits<T>::max()));

        for (int i = 0; i < q_nodes; i++)
            adj[i][i] = T(); 

        int u, v;
        T w;
        
        while (std::getline(input, line)) {
            std::stringstream ss2(line);
            ss2 >> u >> v >> w;

            if (zero_indexed) {
                u--; v--;
            }

            adj[u][v] = std::min(adj[u][v], w);
        }
    }

    void generate_graph(int n){
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> distribucion(-10, 10);
        int numero_aleatorio = distribucion(gen);
        adj.resize(
            n,
            std::vector<T>(
                n,
                std::numeric_limits<T>::max()
            )
        );
        for(int i = 0; i < n; i++){
            for(int j = 0; j < n; j++){
                int numero_aleatorio = distribucion(gen);
                adj[i][j] = numero_aleatorio;
        
            }
        }
    }

    std::size_t size(){
        return adj.size();
    }

    void print(){
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