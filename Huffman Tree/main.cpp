#include <fstream>
#include <iostream>
#include <string>
#include <queue>          // std::priority_queue
#include <vector>         // std::vector
using namespace std;

/** THE CLASS PART **/

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
		cout << character << " : " << bitString << endl;		// Ex: "A : "
	}
};

// InteriorNode is a subclass of HuffmanNode (extends). The most basic node in Huffman tree
class InteriorNode : public HuffmanNode {
	HuffmanNode *left;		// left subtree pointer
	HuffmanNode *right;		// right subtree pointer
public:
	// Constructor
	InteriorNode(double freq, HuffmanNode *lf, HuffmanNode *rt) :
		HuffmanNode (freq), left(lf), right(rt) { }
	// member function
	void printCodes(std::string bitString) const override {			// overrides parent printCodes function
		if (left != nullptr) 
			left->printCodes(bitString + '0');					// encode 0 for the lefts
		if (right != nullptr)
			right->printCodes(bitString + '1');
	}
};

// Draws the binary tree rooted at t.  Invokes the serves of the 
// overloaded version to do the real work.
// template <typename T>
// void draw(Node<T> *t) {
// 	draw(t, '-', 0);
// }

/** THE FUNCTIONS PART **/

void printFrequency(int* freq) {
    int total = 0;
    for(int i = 'A'; i <= 'Z'; i++) {
        std::cout << static_cast<char>(i) << ": " << freq[i-65] << "\n";
        total += freq[i-65];
    }
    cout << "Total = " << total << "\n";
}

// HuffmanNode *huffman(const vector<pair<char, double>>& symbols) {
//     // Make an empty priority queue
//     priority_queue<Huffman *>
// }

HuffmanNode *huffman(const vector<pair<char, double>>& symbols) {
    // Make an empty priority queue
    priority_queue<HuffmanNode *> queue;
    // Make a forest of single-node trees and place them in the priority queue
    for (auto p : symbols)
        queue.push(new CharNode(p.first, p.second));
    // Merge trees until only one tree remains in the priority queue
    // root is the last node after merging (the root)
    HuffmanNode *root = NULL;
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
    // buildHuffmanTree(freq);
    inFile.close();
}

