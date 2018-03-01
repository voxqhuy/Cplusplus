#include <fstream>
#include <iostream>
#include "tree.hpp"
using namespace std;


void printFrequency(int* freq) {
    int total = 0;
    for(int i = 'A'; i <= 'Z'; i++) {
        std::cout << static_cast<char>(i) << ": " << freq[i-65] << "\n";
        total += freq[i-65];
    }
    cout << "Total = " << total << "\n";
}

void buildHuffmanTree(int* freq) {

}

int main() {
    // each letter
    char letter;
    // An array to keep the frequencies
    int freq[26] = { }; // initialize all frequencies to 0

    // Using the text file as input
    ifstream inFile;
    inFile.open("D:\\iRoommm\\Web dev\\Github copies\\C-\\Huffman Tree\\declaration.text");
    // Check if the text file could be opened
    if (!inFile) {
        std::cout  << "Unable to open file declaration.text";
        exit(1);        // Unable to open the file, exit the function
    }
    // Reading the text
    inFile >> noskipws;     // including the whitespace
    while (inFile >> letter) {
        std::cout << letter;        // printing out the texts
        freq[std::toupper(letter) - 65]++;       // adding 1 to the frequency of the letter (capitialized)
    }

    std::cout << "\n" << "Counts:" << "\n" << "-------" << "\n";
    // print out the frequencies
    printFrequency(freq);
    std::cout << "---------------------------------" << "\n";
    // build Huffman tree
    buildHuffmanTree(freq);
    inFile.close();
}

