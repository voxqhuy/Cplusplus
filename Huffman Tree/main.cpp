#include <fstream>
#include <iostream>
using namespace std;

void printFrequency(int* freq) {

}

int main() {
    // each letter
    char letter;
    // An array to keep the frequencies
    int freq[90] = { }; // initialize all frequencies to 0

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
        freq[std::toupper(letter)]++;       // adding 1 to the frequency of the letter (capitialized)
    }

    std::cout << "\n" << "Counts:" << "\n" << "-------" << "\n";
    // print out the frequencies
    printFrequency(freq);

    inFile.close();
}

