/** uhr: generic time performance tester
 * Author: LELE
 *
 * Things to set up:
 * 0. Includes: include all files to be tested,
 * 1. Time unit: in elapsed_time,
 * 2. What to write on time_data,
 * 3. Data type and distribution of RNG,
 * 4. Additive or multiplicative stepping,
 * 5. The experiments: in outer for loop. */

#include <cstdint>
#include <chrono>
#include <cmath>
#include <fstream>
#include <iostream>
#include <random>
#include <vector>

#include "utils_uhr.cpp"
#include "../../floyd_warshall.cpp"
#include "../../bellman_ford.cpp"
#include "../../utils.h"
#include "../../Graph.h"
#include "../../CreateGraph.h"
#include "../../GraphPrinter.h"

int main(int argc, char *argv[])
{
    // Validate and sanitize input
    std::int64_t runs;
    validate_input(argc, argv, runs);
    std::int64_t upper =1;
    std::int64_t lower=1;
    std::int64_t step=1;
    // Set up clock variables
    std::int64_t n, i, executed_runs;
    double time_fw;
    std::vector<double> q;
    double mean_time, time_stdev, dev;
    auto begin_time = std::chrono::high_resolution_clock::now();
    auto end_time = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> elapsed_time = end_time - begin_time;

    // Setear generador aleatorio de numeros
    std::random_device rd;
    std::mt19937_64 rng(rd());
    
    std::uniform_int_distribution<std::int64_t> u_distr; // change depending on app
    std::vector<int> lista_aristas = {100, 250, 500, 1000, 2500, 5000, 10000, 25000, 50000, 100000, 250000,500000,900000};
    // File to write time data
    std::ofstream time_data;
    time_data.open(argv[1]);
    time_data << "n,t_mean,t_stdev,t_Q0,t_Q1,t_Q2,t_Q3,t_Q4" << std::endl;

    // Begin testing
    std::cerr << "\033[0;36mRunning tests...\033[0m" << std::endl << std::endl;
    executed_runs = 0;

    Graph<float> grafo;
    CreateGraph::load_file(grafo, "bio-SC-TS.mtx",false,false);
    int q_nodes = grafo.get_q_nodes();
    auto& adj_ref = grafo.get_adj_ref();
    std::cout << "Valor en [4][0]: " << adj_ref[4][0] << std::endl;
    // Remember to change total depending on step type
    begin_time = std::chrono::high_resolution_clock::now();
    //asps_bellman_ford(grafo.get_edge_list(), grafo.get_q_nodes());
    floydWarshall(adj_ref);
    end_time = std::chrono::high_resolution_clock::now();

    elapsed_time = end_time - begin_time;
    time_fw = elapsed_time.count();
    std::cout << "Valor en [4][0]: " << adj_ref[4][0] << std::endl;

    time_data << q_nodes << "," << time_fw << std::endl;

    // 3. Ahora recorre esa misma referencia para generar el CSV
    time_data << "nodo 1,nodo 2,distancia_minima" << std::endl;
    for(int u = 0; u < q_nodes; u++) {
        for(int v = 0; v < q_nodes; v++) {
            float dist = adj_ref[u][v]; // Leemos de la matriz modificada
            if(dist<1e10)
            // Usamos un filtro muy permisivo para ver si ESOS datos salen
                time_data << u + 1 << "," << v + 1 << "," << dist << "\n";
            
        }
    }
}