#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "graph.cpp"
#include "floyd_warshall.cpp"
#include "bellman_ford.cpp"
#include "utils.h"
#ifdef _WIN32
#include <windows.h>
#endif

int main() {
    #ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
    #endif
    Graph<float> grafo;
    int u = 0;
    int v = 2;
    grafo.load_file("pro.csv");
    std::vector<Edge<float>> edge_list = grafo.get_edge_list_copy();
    int q_nodes = grafo.get_q_nodes();

    std::cout << "--- Matriz adyacencia Grafo ---\n\n";
    grafo.print_adj();
    std::cout <<"\nFloyd_Warshall\n\n--- Matriz de Distancias ---" << std::endl;
    auto mask = floydWarshall(grafo.get_adj_ref());
    std::cout << std::endl;
    grafo.print_adj();
    std::cout << "Distancia: " << grafo.get_adj_ref()[u][v] << std::endl;   
    printPath(u, v, mask);

    std::cout<<"\nBellman_Ford"<<std::endl;
    auto res = asps_bellman_ford(grafo.get_edge_list(), grafo.get_q_nodes());
    print_distance_matrix(res, grafo.get_q_nodes());
    std::cout << "Distancia: " << res.distances[u][v] << std::endl;    
    printPath_Bellman_Ford(u, v, res.preds[u]);
    return 0;
}