//  Name: Vo Huy
//  Assignment number: 6
//  Assignment: Shortest Path Matrix
//  File name: spm.cpp
//  Date last modified: April 19, 2018
//  Honor statement: I have neither given nor received any unauthorized help on this assignment. 

#include <climits>      // INT_MAX
#include <queue>        // std::priority_queue
#include <algorithm>    // std::fill_n
#include <cstddef>
#include <iostream>
#include "spm.h"
#include "graph.h"

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
            if (w != INF) {                 // There is an edge in between
                int d = dist + w;           // new distance = current distance + the weight
                if (d < checkeds[i]) {      // found a shorter path
                    checkeds[i] = d;        
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
        for (int col = row; col < size; col++) {
            // fill the diagonal line with zeros (the distance from one point to itself is 0)
            if (row == col) {
                spm[row][col] = 0;
            } else {        // not the diagonal line
                // calculate the shortest path
                spm[row][col] = dijkstra_distance(in, row, col);
                // undirected graph = symmetric
                spm[col][row] = spm[row][col];
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
    AdjacencyMatrix spm = make_empty_graph(size); 
    AdjacencyMatrix spm_copied = make_empty_graph(size);
    // Copying 'spm' and 'spm_copied' from 'in'
    for ( int i = 0; i < size; i++ ) {
        for ( int j = 0; j < size; j++ ) {
            if (i == j) {       // the diagonal line
                spm[i][j] = 0;
                spm_copied[i][j] = 0;
            } else {            // copying
                spm[i][j] = in[i][j];           
                spm_copied[i][j] = in[i][j];
            }
        }
    }

    for (int bridge = 0; bridge < size; bridge++) {
        for (int row = 0; row < size; row++) {
            for (int col = row + 1; col < size; col++) {
                if ((bridge != row) && (bridge != col)) {  // avoid treating the same vertex as a bridge
                    if ((spm[row][bridge] == INF) || (spm[bridge][col] == INF)) {
                        spm_copied[row][col] = spm[row][col];
                    } else {
                        spm_copied[row][col] = minimum(spm[row][col], spm[row][bridge] + spm[bridge][col]);
                    }
                }
            }
        }
        // copy spm_copied into spm
        for ( int i = 0; i < size; i++ ) {
            for ( int j = i + 1; j < size; j++ ) {     
                spm[i][j] = spm_copied[i][j];
                spm[j][i] = spm_copied[i][j];
            }
        }
    }
    return spm;
}

bool connected(const AdjacencyMatrix& m, int v, int w) {
    if (v == w) {return false;}
    if (m[v][w] == 1) {return true;}
    for (int i = 0; i < m[v].size(); i++) {
        if ((i != v) && (i != w)) {
            if (connected(m, v, i) && connected(m, i, w)) {
                return true;
            }
        }
    }
    return false;
}

/*                                  RESULTS REPORT  
/            
/   15-word matrix: 0.003 seconds (Dijkstra), 0 seconds (Dynamic Programming)
/   20-word matrix: 0.025 seconds (Dijkstra), 0.001 seconds (Dynamic Programming)
/   50-word matrix: 0.064 seconds (Dijkstra), 0.004 seconds (Dynamic Programming)
/   100-word matrix: 1.172 seconds (Dijkstra), 0.049 seconds (Dynamic Programming)
/   200-word matrix: 24.28 seconds (Dijkstra), 0.43 seconds (Dynamic Programming)
/   300-word matrix: 98.944 seconds (Dijkstra), 1.406 seconds (Dynamic Programming)
/
*/