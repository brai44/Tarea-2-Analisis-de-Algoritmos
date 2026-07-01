#ifndef CREATE_GRAPH_H
#define CREATE_GRAPH_H

#include "Graph.h"
#include <random>
#include <set>
#include <sstream>
#include <fstream>

class CreateGraph {
public:
    template<typename T>
    static void create_graph_density(Graph<T>& g, int n, int e) {
        g.init(n);
        
        // Crear todas las aristas posibles y mezclarlas
        std::vector<std::pair<int, int>> todas_las_posibles;
        todas_las_posibles.reserve(n * (n - 1));  // Reserva memoria para evitar realocaciones
        
        for(int i = 0; i < n; ++i) {
            for(int j = 0; j < n; ++j) {
                if(i == j) continue; // Evita bucles
                todas_las_posibles.push_back({i, j});
            }
        }

        // Mezclar el vector  para garantizar selección aleataoria
        std::mt19937 gen(std::random_device{}());
        std::shuffle(todas_las_posibles.begin(), todas_las_posibles.end(), gen);

        // Tomar las primeras 'e' aristas mezcladas y asignarlas al grafo
        std::uniform_real_distribution<double> dist_pesos(1.0, 100.0);
        for(int i = 0; i < e && i < (int)todas_las_posibles.size(); ++i) {
            g.add_edge(todas_las_posibles[i].first, 
                    todas_las_posibles[i].second, 
                    (T)dist_pesos(gen));
        }
    }

    template<typename T>
    static void create_path_graph(Graph<T>& g, int n) {
        g.init(n);

        // Crear una lista con las aristas que forman el camino lineal
        std::vector<std::pair<int, int>> aristas_camino;
        aristas_camino.reserve(n - 1);
        
        for(int i = 0; i < n - 1; ++i) {
            aristas_camino.push_back({i, i + 1});
        }

        // Mezclar el orden de las aristas del camino
        std::mt19937 gen(std::random_device{}());
        std::shuffle(aristas_camino.begin(), aristas_camino.end(), gen);

        // Añadir las aristas al grafo con pesos aleatorios
        std::uniform_real_distribution<double> dist_pesos(1.0, 100.0);
        for(const auto& arista : aristas_camino) {
            g.add_edge(arista.first, arista.second, (T)dist_pesos(gen));
        }
    }

    template<typename T>
    static void create_complete_graph(Graph<T>& g, int n) {
        g.init(n);

        std::uniform_real_distribution<double> dist_pesos(1.0, 100.0);
        std::mt19937 gen(std::random_device{}());

        // Conectar cada vértice con todos los demás
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                // Un grafo completo no tiene bucles
                if (i == j) continue;
                
                // Añadir arista de i a j
                g.add_edge(i, j, (T)dist_pesos(gen));
            }
        }
    }

    // Carga desde archivo MTX
    template<typename T>
    static void load_file(Graph<T>& g, const std::string& filename, bool zero_indexed = true, bool dir=true) {
        std::ifstream input(filename);
        int q_nodes=0, q_edges=0;
        std::string line;
        std::getline(input, line);

        // Extraer la configuración inicial (nodos y aristas) de la primera línea
        std::stringstream ss(line);
        ss >> q_nodes >> q_nodes >> q_edges;

        g.init(q_nodes);

        // Procesar el archivo línea por línea para extraer las aristas
        int u, v;
        T w;
        while (std::getline(input, line)) {
            std::stringstream ss2(line);
            ss2 >> u >> v >> w;

            // Ajustar índices base-1 a base-0 si el archivo lo requiere
            if (zero_indexed) {
                u--; v--;
            }
            // Añadir arista principal, y su inversa si el grafo es no dirigido
            g.add_edge(u, v, w);
            if(!dir){
                g.add_edge(v, u, w);
            }
        }
    }
};

#endif