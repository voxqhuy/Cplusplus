#ifndef SPM_H_INCUDED
#define SPM_H_INCUDED

#include "graph.h"

// Builds and returns the shortest path matrix from a graph's adjacency 
// matrix using Dijkstra's algorithm.
AdjacencyMatrix make_spm_dijkstra(const AdjacencyMatrix& in);

// Builds and returns the shortest path matrix from a graph's adjacency 
// matrix using dynamic programming.
AdjacencyMatrix make_spm_dp(const AdjacencyMatrix& in);

bool connected(const AdjacencyMatrix&m, int v, int w);
#endif
