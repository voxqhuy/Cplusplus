#include <climits>      // INT_MAX
#include <queue>        // std::priority_queue
#include <map>          // std::map
#include <algorithm>    // std::fill_n
#include "spm.h"
// #include "graph.h"

// Ordering distances so that smallest gets served first
class distanceSort {
public:
    bool operator()(std::pair<int, int> num1, std::pair<int, int> num2) {
        return num1.second > num2.second;   // (pair) vertex : distance
    }
};

int dijkstra_distance(const AdjacencyMatrix& in, int start, int dest) {
    // the size of one side of passed in matrix = the number of vertices of the graph
    int size = in.size();
    // A queue that keep all the vertices with their distances from the start vertex
    std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, distanceSort> uncheckeds;
    // An array does the job of shortest path table. Intially, it is empty.
    int checkeds[size]; 
    // fill the array with INFs, except for the start vertex = 0
    std::fill_n(checkeds, size, INF);
    checkeds[start] = 0;
    // Initilize the queue
    for (int i = 0; i < size; i++) {
        // the start vertex has a distance of 0
        if ( i == start ) {
            uncheckeds.push(std::pair(i, 0));
        } else {
            // other vertices have infinity distance
            uncheckeds.push(std::pair(i, INF));
        }
    }

    // the result
    int dijkstra_distance = 0;
    while (!uncheckeds.empty()) {
        // Get the vertex with the minimum distance
        std::pair<int, int> v = uncheckeds.top();
        int dist = v.second;                // and its distance
        if (v.first == dest) {              // found the shortest path to the destination
            dijkstra_distance = dist;
            break;              
        }
        uncheckeds.pop();                   // remove the vertex. It is being solved

        // A vector that keeps the weights from the closestVertex to all others
        std::vector<int> weights = in[v.first];
        // Adding all adjacent vertices with the new distances to the queue
        for (int i = 0; i < size; i++) {
            int w = weights[i];             // the weight in between
            if (w != -1) {                  // There is an edge in between
                int d = dist + w;           // new distance = current distance + the weight
                if (d < checkeds[i]) {      // found a shorter path
                    checkeds[i] = d;        // Update the table TODO: will this actually change the element?
                    uncheckeds.push(std::pair(i, d));
                }
            }
        }
    }
    // Deallocation
    uncheckeds = {};

    return dijkstra_distance;
}

// Builds and returns the shortest path matrix from a graph's adjacency 
// matrix using Dijkstra's algorithm.
AdjacencyMatrix make_spm_dijkstra(const AdjacencyMatrix& in) {
    // the size of one side of passed in matrix = the number of vertices of the graph
    int size = in.size();
    // An empty matrix for being implemented to be the SPM "Shortest Path Matrix"
    AdjacencyMatrix spm = make_empty_graph(size);

    for (int row = 0; row < size; row++) {
        for (int col = 0; col < size; col++) {
            // fill the diagonal line with zeros (the distance from one point to itself is 0)
            if (row == col) {
                spm[row][col] = 0;
            } else {        // the path is unsolved
                // calculate the shortest path
                spm[row][col] = dijkstra_distance(in, row, col);
                // undirected graph = symmetric
                spm[row][col] = spm[row][col];
            }
        }
    }
    return spm;
}

// Return the minimum of two numbers    
int minimum (int a, int b) {
    return a > b ? b : a;
}

// Builds and returns the shortest path matrix from a graph's adjacency 
// matrix using dynamic programming.
AdjacencyMatrix make_spm_dp(const AdjacencyMatrix& in) {
    // the size of one side of passed in matrix = the number of vertices of the graph
    int size = in.size();
    // An empty matrix for being implemented to be the SPM "Shortest Path Matrix"
    AdjacencyMatrix spm = make_empty_graph(size);      // TODO: should i not initilize this INF
    AdjacencyMatrix spm_copied = make_empty_graph(size);
    // Copying 'spm' and 'spm_copied' from 'in'
    for ( int i = 0; i < size; i++ ) {
        for ( int j = 0; j < size; i++ ) {
            if (i == j) {
                spm[i][j] = 0;
                spm_copied[i][j] = 0;
            } else {
                int copy = in[i][j];        // TODO: do I need this?
                spm[i][j] = copy;           // TODO: is it copiable?
                spm_copied[i][j] = copy;
            }
        }
    }

    for (int bridge = 0; bridge < size; bridge++) {
        for (int row = 0; row < size; row++) {
            for (int col = row + 1; col < size; col++) {
                if ((bridge != row) && (bridge != col)) {  // avoid treating the same vertex as a bridge
                    spm_copied[row][col] = minimum(spm[row][col], spm[row][bridge] + spm[bridge][col]);
                }
            }
        }
        // copy spm_copied into spm
        for ( int i = 0; i < size; i++ ) {
            for ( int j = i + 1; j < size; i++ ) {   
                int copy = spm_copied[i][j];        // TODO: do I need this?    
                spm[i][j] = copy;
                spm[j][i] = copy;
            }
        }
    }

    return spm;
}