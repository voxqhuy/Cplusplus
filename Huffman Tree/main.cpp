#include <fstream>
#include <iostream>
#include <string>
#include <queue>          // std::priority_queue
#include <vector>         // std::vector
#include <math.h>       /* round, floor, ceil, trunc */
using namespace std;

/*********** THE CLASS PART ***********/

// These classes are based on class 318 lecture at SAU by Dr. Halterman
/**  	Huffman Node's visualization: 
 ** 
 **          (Huffman Node)
 **				 ^	  ^
 **				/      \
 **			   /		\
 **		(Char Node)	 (Interior Node)	
 **/

// Huffman Node class
class HuffmanNode {
	// Frequency as data
	double frequency;
public:
	// Constructor
	HuffmanNode(double freq): frequency(freq) {}
	// member function print code: print Huffman encoded codes
	// const = 0: this is a pure method, it's not supposed to change the data of the class (const)
	//https://stackoverflow.com/a/21187983/8969722
	virtual void printCodes(std::string bitString) const = 0;
	// print nothing if no parameters passed in
	virtual void printCodes() { printCodes(""); }
	// frequency getter
	double getFrequency() const { return frequency; }
};

// CharNode is a subclass of HuffmanNode (extends) for characters ('A' - 'Z')
class CharNode : public HuffmanNode {
	// character as data
	char character;
public:
	// Constructor
	CharNode(char ch, double freq): HuffmanNode(freq), character(ch) { }
	// member function printCodes: print characters ('A' - 'Z')
	// const override: a virtual function overrides another virtual function
	// http://en.cppreference.com/w/cpp/language/override
	void printCodes (std::string bitString) const override {			// overrides parent printCodes function
		cout << character << " : " << bitString << '\n';		// Ex: "A : "
	}
};

// InteriorNode is a subclass of HuffmanNode (extends). The most basic node in Huffman tree
class InteriorNode : public HuffmanNode {
	HuffmanNode *left;		    // left subtree pointer
	HuffmanNode *right;		    // right subtree pointer
public:
	// Constructor
	InteriorNode(double freq, HuffmanNode *lf, HuffmanNode *rt) :
		HuffmanNode(freq), left(lf), right(rt) { }
	// member function
	void printCodes(std::string bitString) const override {			// overrides parent printCodes function
		if (left != nullptr) 
			left->printCodes(bitString + '0');					// encode 0 for the lefts
		if (right != nullptr)
			right->printCodes(bitString + '1');
	}
};

// Customed strict weak ordering for the priority queue
// https://stackoverflow.com/a/19535699/8969722
class CompareFreq
{
public:
    bool operator()(HuffmanNode const * node1, HuffmanNode const * node2) {
        // return "true" if "node2" freq is ordered before "node1" freq
        return node1->getFrequency() > node2->getFrequency();   // smallest frequency stay on top => first out
    }
};

/*********** END OF THE CLASS PART ***********/

// Draws the binary tree rooted at t.  Invokes the serves of the 
// overloaded version to do the real work.
// template <typename T>
// void draw(Node<T> *t) {
// 	draw(t, '-', 0);
// }

/*********** THE FUNCTIONS PART ***********/

vector<pair<char, double>> printFrequency(int* freq, int total) {
    // the vector that keeps characters with their frequencies
    vector<pair<char, double>> symbols;
    // Loop through the freq array (keeping frequencies of 26 elements)
    for(int i = 'A'; i <= 'Z'; i++) {
        char ch =  static_cast<char>(i);        // the character
        int frequency = freq[i-'A'];            // the frequency of the character
        // keep adding each character with its % frequency (its frequency / total)
        symbols.push_back(std::make_pair(ch, round(1000000.0 * frequency / total) / 1000000.0)); // rounded to 6 numbers after the decimal point

        std::cout << ch << ": " << frequency << '\n';
    }
    std::cout << "Total = " << total << '\n';        // print the total

    return symbols;
}

// HuffmanNode *huffman(const vector<pair<char, double>>& symbols) {
//     // Make an empty priority queue
//     priority_queue<Huffman *>
// }

HuffmanNode *build_huffman(const vector<pair<char, double>>& symbols) {
    // Make an empty priority queue
    priority_queue<HuffmanNode*, vector<HuffmanNode*>, CompareFreq> queue;
    // Make a forest of single-node trees and place them in the priority queue
    for (auto p : symbols)
        queue.push(new CharNode(p.first, p.second));
    // Merge trees until only one tree remains in the priority queue
    // root is the last node after merging (the root)
    InteriorNode *root = NULL;
    // Start looping (merging)
    while (queue.size() > 1) {
        //Extract the two trees with the minimal frequencies
        HuffmanNode *n1 = queue.top();
        queue.pop();
        HuffmanNode *n2 = queue.top();
        queue.pop();
        root = new InteriorNode(n1->getFrequency() + n2->getFrequency(), n1, n2);
        // Combine them into a new tree with a common parent,
        // and put this new tree back into the priority queue
        queue.push(root);
    }
    return root;
}

int main() {
    char ch;                    // each letter
    int total;                  // the total number of letters
    // An array to keep the frequencies
    int freq[26] = { };         // initialize all frequencies to 0

    // Using the text file as input
    ifstream inFile;
    inFile.open("D:\\iRoommm\\Web dev\\Github copies\\C-\\Huffman Tree\\declaration.text");
    // Check if the text file could be opened
    if (!inFile) {
        std::cout  << "Unable to open file declaration.text";
        exit(1);                // Unable to open the file, exit the function
    }
    // Reading the text
    inFile >> noskipws;         // including the whitespace
    while (inFile >> ch) {
        std::cout << ch;        // printing out the texts
        freq[std::toupper(ch) - 'A']++;         // adding 1 to the frequency of the letter (capitialized)
        if (isalpha(std::toupper(ch))) total++;                 // increase the number of letter
    }

    std::cout << '\n' << "Counts:" << '\n' << "-------" << '\n';
    // make a vector pair with format "char: frequency" (Ex: A: 0.003)
    // print out the frequencies
    HuffmanNode *root = build_huffman(printFrequency(freq, total));
    std::cout << "---------------------------------" << '\n';
    // build Huffman tree
    // buildHuffmanTree(freq);
    inFile.close();
}