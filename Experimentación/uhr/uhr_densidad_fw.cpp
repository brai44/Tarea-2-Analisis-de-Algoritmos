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
    std::int64_t runs, lower, upper, step;
    validate_input(argc, argv, runs, lower, upper, step);

    // Set up clock variables
    std::int64_t n, i, executed_runs;
    std::vector<double> times(runs);
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
    for (int q_aristas: lista_aristas) {
        mean_time = 0;
        time_stdev = 0;

        // Test configuration goes here
        Graph<double> grafo;
        CreateGraph::create_graph_density(grafo, 1000, q_aristas);
        
        // Run to compute elapsed time
        for (i = 0; i < runs; i++) {
            std::vector<std::vector<double>> adj = grafo.get_adj_copy();
            // Remember to change total depending on step type
            begin_time = std::chrono::high_resolution_clock::now();
            //asps_bellman_ford(grafo.get_edge_list(), grafo.get_q_nodes());
            floydWarshall(adj);
            end_time = std::chrono::high_resolution_clock::now();

            elapsed_time = end_time - begin_time;
            times[i] = elapsed_time.count();

            mean_time += times[i];
        }

        // Compute statistics
        mean_time /= runs;

        for (i = 0; i < runs; i++) {
            dev = times[i] - mean_time;
            time_stdev += dev * dev;
        }

        time_stdev /= runs - 1; // Subtract 1 to get unbiased estimator
        time_stdev = std::sqrt(time_stdev);

        quartiles(times, q);

        time_data << q_aristas << "," << mean_time << "," << time_stdev << ",";
        time_data << q[0] << "," << q[1] << "," << q[2] << "," << q[3] << "," << q[4] << std::endl;
    }

    // This is to keep loading bar after testing
    std::cerr << std::endl << std::endl;
    std::cerr << "\033[1;32mDone!\033[0m" << std::endl;

    time_data.close();

    return 0;
}
