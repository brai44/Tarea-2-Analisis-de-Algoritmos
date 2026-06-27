#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "graph.cpp"
#include "floyd_warshall.cpp"


int main() {
    Graph<float> grafo;
    grafo.generate_graph(3);
    grafo.print();
    auto ajd_copy = grafo.get_adj_copy();
    floydWarshall(ajd_copy);
    std::cout << std::endl;
    grafo.print();
    return 0;
}