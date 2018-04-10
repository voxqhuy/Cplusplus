#include "graph.h"
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <climits>  //  For INT_MAX


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
AdjacencyMatrix load_graph(const std::string& filename) {
    int number_of_vertices;
    //  Open file
    std::fstream fin(filename, std::ios::in);
    if (fin.good()) {
        //  Read number of vertices
        fin >> number_of_vertices;
        //  Create the appropriately-sized matrix
        AdjacencyMatrix matrix = make_empty_graph(number_of_vertices);
        //  Populate the adjacency matrix
        for (int row = 0; row < number_of_vertices; row++)
            for (int col = 0; col < number_of_vertices; col++) {
                int in_value;
                fin >> in_value;
                matrix[row][col] = (in_value == -1)? INF : in_value;
            }
        //  Close file
        fin.close();
        return matrix;
    }
    return NO_MATRIX;   //  Could not load the adjacency matrix
}

// Makes a graph consisting of a forest of n single vertex trees
// (no vertex connected to any other vertex).
AdjacencyMatrix make_empty_graph(int n) {
    return AdjacencyMatrix(n, std::vector<int>(n, INF));
}


// Displays the adjacency matrix on the given output stream
std::ostream& operator<<(std::ostream& os, const AdjacencyMatrix& m) {
    if (m == NO_MATRIX)
        os << "No adjacency matrix" << '\n';
    else {
        for (unsigned row = 0; row < m.size(); row++) {
            for (unsigned col = 0; col < m[row].size(); col++) {
                if (m[row][col] != INF)
                    os << std::setw(3) << m[row][col];
                else
                    os << std::setw(3) << '.';
            }
            os << '\n';
        }
    }
    return os;
}

const AdjacencyMatrix NO_MATRIX;

const int INF = INT_MAX;