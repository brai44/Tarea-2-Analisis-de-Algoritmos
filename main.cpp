#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "graph.cpp"

int main() {
    Graph<float> grafo;
    grafo.generate_graph(5);
    grafo.print();
    return 0;
}