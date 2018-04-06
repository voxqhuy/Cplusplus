#include "spm.h"
#include <iostream>
#include <iomanip>

int dijkstra_distance()

// Builds and returns the shortest path matrix from a graph's adjacency 
// matrix using Dijkstra's algorithm.
AdjacencyMatrix make_spm_dijkstra(const AdjacencyMatrix& in) {
    for ( unsigned row = 0; row < in.size(); row++ ) {
        for ( unsigned col = 0; col < in[row].size(); col++) {
            // calculate the shortest path
            in[i][j] = dijkstra_distance(in, i, j);
            // undirected graph = symmetric
            in[j][i] = in[i][j];
        }
    }
}

// Builds and returns the shortest path matrix from a graph's adjacency 
// matrix using dynamic programming.
AdjacencyMatrix make_spm_dp(const AdjacencyMatrix& in);