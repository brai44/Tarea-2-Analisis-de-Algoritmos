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
    auto mask = floydWarshall(grafo.get_adj_ref());
    std::cout << std::endl;
    grafo.print();
    printPath(1, 2, mask);
    return 0;
}