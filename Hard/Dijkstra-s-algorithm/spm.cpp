#include "spm.h"

int dijkstra_distance(const AdjacencyMatrix& in, int row, int column) {
    // Create 
}

// Builds and returns the shortest path matrix from a graph's adjacency 
// matrix using Dijkstra's algorithm.
AdjacencyMatrix make_spm_dijkstra(const AdjacencyMatrix& in) {
    // the size of one side of passed in matrix = the number of vertices of the graph
    int size = in.size();
    // An empty matrix for being implemented to be the SPM "Shortest Path Matrix"
    AdjacencyMatrix spm = make_empty_graph(size, std::vector<int>(size, INF));

    for ( unsigned row = 0; row < size; row++ ) {
        for ( unsigned col = 0; col < size; col++) {
            // fill the diagonal line with zeros (the distance from one point to itself is 0)
            if (i == j) {
                spm[i][j] = 0;
            } 
            else if (in [i][j] != INF) {            // the path is solved
                spm[i][j] == in[i][j];              // if it is copiable, otherwise just + 0
            } else {                                // the path is unsolved
                // calculate the shortest path
                in[i][j] = dijkstra_distance(in, i, j);
                // undirected graph = symmetric
                in[j][i] = in[i][j];
            }
        }
    }
}

// Builds and returns the shortest path matrix from a graph's adjacency 
// matrix using dynamic programming.
AdjacencyMatrix make_spm_dp(const AdjacencyMatrix& in);