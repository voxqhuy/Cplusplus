#include "spm.h"
#include <climits>      // INT_MAX
#include <queue>        // std::priority_queue
#include <map>          // std::map
#include <algorithm>    // std::fill_n

// Ordering distances so that smallest gets served first
class distanceSort {
public:
    bool operator()(pair<int, int> num1, pair<int, int> num2) {
        return num1.second > num2.second;   // (pair) vertex : distance
    }
};

int dijkstra_distance(const AdjacencyMatrix& in, int start, int dest) {
    // the size of one side of passed in matrix = the number of vertices of the graph
    int size = in.size();
    // A queue that keep all the vertices with their distances from the start vertex
    priority_queue<pair<int, int>, std::vector<pair<int, int>>, distanceSort> uncheckeds;
    // An array does the job of shortest path table. Intially, it is empty.
    int checkeds[size]; 
    // fill the array with INFs, except for the start vertex = 0
    std::fill_n(checkeds, size, INF);
    checkeds[start] = 0;
    // Initilize the queue
    for ( unsigned i = 0; i < size; i++) {
        // the start vertex has a distance of 0
        if ( i == start ) {
            uncheckeds.push(i, 0);
        } else {
            // other vertices have infinity distance
            uncheckeds.push(i, INF);
        }
    }

    // the result
    int dijkstra_distance = 0;
    while (!uncheckeds.empty()) {
        // Get the vertex with the minimum distance
        std::pair<int, int> v = uncheckeds.top();
        int dist = v.second();              // and its distance
        if (v.first() == dest) {            // found the shortest path to the destination
            dijkstra_distance = dist;
            break;              
        }
        uncheckeds.pop();                   // remove the vertex. It is solved

        // A vector that keeps the weights from the closestVertex to all others
        std::vector<int> weights = in[v];
        // Adding all adjacent vertices with the new distances to the queue
        for ( unsigned i = 0; i < size; i++) {
            int w = weights[i];             // the weight in between
            if (w != -1) {                  // There is an edge in between
                int d = dist + w;           // new distance = current distance + the weight
                if (d < checkeds[i]) {      // found a shorter path
                    checkeds[i] = d;        // Update the table
                    uncheckeds.push(i, d);
                }
            }
        }
    }
    // Deallocation
    uncheckeds = {};
    delete [] checkeds;  // Free memory allocated for the array.
    checkeds = NULL;     // Be sure the deallocated memory isn't used.

    return dijkstra_distance;
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
            else if (in [i][j] != INF) {    // the path is solved
                spm[i][j] == in[i][j];      // if it is copiable, otherwise just + 0
            } else {                        // the path is unsolved
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