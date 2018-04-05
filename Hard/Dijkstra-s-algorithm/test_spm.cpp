#include "graph.h"
#include "spm.h"
#include <iostream>
#include <iomanip>
#include <ctime>

int main(int argc, char *argv[]) {
    if (argc > 0) {
        // Load the adjacency matrix for a graph
        AdjacencyMatrix adj = load_graph(argv[1]);
        //std::cout << adj << '\n';

        std::cout << "-------------------\n";
        clock_t start_time, stop_time;
        start_time = clock();
        auto A1 = make_spm_dijkstra(adj);
        stop_time = clock();
        std::cout << A1 << '\n';
        std::cout << "Dijkstra:       " << std::setw(10) 
                  << static_cast<double>(stop_time - start_time)/CLOCKS_PER_SEC 
                  << " seconds\n";
        std::cout << "-------------------\n";
        // Compute the table containing the weights of the shortest
        // paths between every pair of vertices in the graph
        start_time = clock();
        auto A2 = make_spm_dp(adj);
        stop_time = clock();
        std::cout << A2 << '\n';
        std::cout << "Dynamic Programming: " << std::setw(10)
                  << static_cast<double>(stop_time - start_time)/CLOCKS_PER_SEC 
                  << " seconds\n";
        std::cout << "Same matrix: " << std::boolalpha << (A1 == A2) << '\n';
    }
    else
        std::cout << "File name required" << '\n';
}
