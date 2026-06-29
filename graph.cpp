#ifndef GRAPH
#define GRAPH


#include <iostream>
#include <vector>
#include <sstream>
#include <fstream>
#include <utility>
#include <random>
#include <limits>
#include <set>
#include "utils.h"
#include <iomanip>

template<typename T>

class Graph{
private:
    int q_nodes = 0;
    int q_edges = 0;
    std::vector<std::vector<T>> adj;
    std::vector<Edge<T>> edge_list;

public:

    Graph() = default;

    void load_file(const std::string filename, bool zero_indexed = true) {
        std::ifstream input(filename);

        std::string line;
        std::getline(input, line);
        
        std::stringstream ss(line);
        ss >> q_nodes >> q_nodes >> q_edges; 

        adj.assign(q_nodes, std::vector<T>(q_nodes, std::numeric_limits<T>::max()));
        edge_list.clear();

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
            edge_list.push_back({u,v,w});
        }
    }

    void generate_graph(int n, bool loops = false, bool negatives = false){
        const int INF = 1000000000;
        std::random_device rd;
        std::mt19937 gen(rd());
        int min = negatives ? -10 : 0;
        int max = 10; 
        std::uniform_int_distribution<> distribucion(min, max);
        q_nodes = n;
        edge_list.clear();
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
                if (numero_aleatorio == 0){
                    numero_aleatorio = INF;
                }
                if (!loops && i == j){
                    adj[i][j] = 0;
                } else {
                   adj[i][j] = numero_aleatorio; 
                   edge_list.push_back({i,j,numero_aleatorio});
                }     
            }
        }
        q_edges = edge_list.size();
    }

void create_graph_densidad(int n, int e) {
    q_nodes = n;
    edge_list.clear();
    
    // Inicializar matriz con Infinito
    adj.assign(n, std::vector<T>(n, std::numeric_limits<T>::max()));
    for(int i = 0; i < n; i++) adj[i][i] = 0; // Distancia al mismo nodo es 0

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist_nodos(0, n - 1);
    std::uniform_real_distribution<double> dist_pesos(1.0, 100.0);

    // Usamos un set para evitar repetir la misma arista (u, v)
    std::set<std::pair<int, int>> aristas_creadas;

    while(aristas_creadas.size() < (size_t)e) {
        int u = dist_nodos(gen);
        int v = dist_nodos(gen);

        // Validaciones: no bucles, no aristas repetidas
        if (u == v || aristas_creadas.count({u, v})) continue;

        double peso = dist_pesos(gen);
        
        // Guardar
        aristas_creadas.insert({u, v});
        edge_list.push_back({u, v, peso});
        adj[u][v] = peso;
    }
    q_edges = edge_list.size();
}

    std::size_t size(){
        return adj.size();
    }

    std::vector<std::vector<T>>& get_adj_ref() {
        return adj;
    }

    // Solo usar cuando los grafos son chicos
    std::vector<std::vector<T>> get_adj_copy(){
        return adj;
    } 

    std::vector<Edge<T>>& get_edge_list(){
        return edge_list;
    }

    std::vector<Edge<T>> get_edge_list_copy(){
        return edge_list;
    }
    
    int get_q_nodes(){
        return q_nodes;
    }
    
    void print_adj() {
        std::size_t n = size();
        const T T_max = std::numeric_limits<T>::max();
        const int width = 4; 

        std::cout << "   ";
        for (int i = 0; i < n; i++){
            std::cout << std::setw(width) << i;
        }
        
        std::cout << "\n  ┌";
        for (int k = 0; k < n * (width) + 1; k++) std::cout << "─";
        std::cout << "┐" << std::endl;

        for (std::size_t i = 0; i < n; i++) {
            std::cout << i << " │"; 

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

    void print_edg(){
        std::cout<<"[Nodo entrada], [Nodo salida], [Peso]"<<std::endl;
        for(const auto& e:edge_list){
            std::cout<<e.source<<", "<<e.destination<<", "<<e.w<<std::endl;
        }
    }
};

#endif