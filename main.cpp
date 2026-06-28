#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "graph.cpp"
#include "floyd_warshall.cpp"


int main() {
    Graph<int> grafo;
    grafo.load_file("negativos.csv");
    grafo.print_adj();
    std::cout << std::endl;
    auto mask = floydWarshall(grafo.get_adj_ref());
    std::cout << std::endl;
    grafo.print_adj();
    printPath(1, 3, mask);
    return 0;
}