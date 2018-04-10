#ifndef GRAPH_H_
#define GRAPH_H_

#include <vector>
#include <string>


// Convenient type name for an adjacency matrix
using  AdjacencyMatrix = std::vector<std::vector<int>>;

// Represents infinity.  Infinity within an adjacency matrix 
// indicates no connection between the vertices.
extern const int INF;  

// Represents a non-matrix. Useful for when an adjacency matrix is 
// required but for some reason the necessary matrix is not available.
extern const AdjacencyMatrix NO_MATRIX;

// Reads an adjacency matrix from a textfile.  Returns NO_MATRIX if 
// an adjacency matrix cannot be made (perhaps due to an incorrect
// file name or improper data format).  File format is 
//
// <number of vertices>
// <first row entries>
// <second row entries>
// <third row entries>
// . . .
// <last row entries>
//
AdjacencyMatrix load_graph(const std::string& filename);

// Makes a graph consisting of a forest of n single vertex trees
// (no vertex connected to any other vertex).
AdjacencyMatrix make_empty_graph(int n);

// Displays the adjacency matrix on the given output stream
std::ostream& operator<<(std::ostream& os, const AdjacencyMatrix& m);


#endif