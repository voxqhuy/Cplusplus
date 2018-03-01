#include <fstream>
#include <iostream>
using namespace std;

int main() {
    ifstream inFile;
    inFile.open("D:\\iRoommm\\Web dev\\Github copies\\C-\\Huffman Tree\\declaration.text");

    if (!inFile) {
        cerr  << "Unable to open file declaration.text";
        exit(1);        // Unable to open the file, exit the function
    }

    while (!inFile >> x) {
        std::cout << x;
    }
    inFile.close();
}
