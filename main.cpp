#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "graph.cpp"
#include "floyd_warshall.cpp"
#include "bellman_ford.cpp"
#include "utils.h"

int main() {
    Graph<int> grafo;
    grafo.load_file("test.mtx");
    std::vector<Edge<int>> edge_list = grafo.get_edge_list_copy();
    int q_nodes = grafo.get_q_nodes();
    grafo.print_adj();
    std::cout <<"Floyd_Warshall"<<std::endl;
    auto mask = floydWarshall(grafo.get_adj_ref());
    std::cout << std::endl;
    grafo.print_adj();

    std::cout<<"Bellman_Ford"<<std::endl;
    auto res = asps_bellman_ford(grafo.get_edge_list(), grafo.get_q_nodes());
    // Imprimir distancia de 0 a 3:
    print_distance_matrix(res, grafo.get_q_nodes());
    std::cout << "Distancia: " << res.distances[0][3] << std::endl;    
    printPath_Bellman_Ford(0, 3, res.preds[0]);
    return 0;
}