#include "spm.h"
#include <iostream>
#include <iomanip>

int dijkstra_distance(const AdjacencyMatrix& in, int row, int column) {
    
}

// Builds and returns the shortest path matrix from a graph's adjacency 
// matrix using Dijkstra's algorithm.
AdjacencyMatrix make_spm_dijkstra(const AdjacencyMatrix& in) {
    // TODO: create an empty matrix maybe?
    for ( unsigned row = 0; row < in.size(); row++ ) {
        for ( unsigned col = 0; col < in[row].size(); col++) {
            if (int [i][j] == INF) {
                // calculate the shortest path
                in[i][j] = dijkstra_distance(in, i, j);
                // undirected graph = symmetric
                in[j][i] = in[i][j];
            } else {
                // FIXME: handle already solved paths
            }
        }
    }
}

// Builds and returns the shortest path matrix from a graph's adjacency 
// matrix using dynamic programming.
AdjacencyMatrix make_spm_dp(const AdjacencyMatrix& in);