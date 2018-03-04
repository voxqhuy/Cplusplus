#include <fstream>
#include <iostream>
#include <string>
#include <queue>          // std::priority_queue
#include <vector>         // std::vector
#include <math.h>       /* round, floor, ceil, trunc */
#include <iomanip>      // std::setprecision
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
	HuffmanNode (double freq): frequency(freq) {}
	// member function print code: print Huffman encoded codes
	// const = 0: this is a pure method, it's not supposed to change the data of the class (const)
	//https://stackoverflow.com/a/21187983/8969722
    // virtual function:  To implement polymorphism
    // if the superclass pointer is aiming at a subclass objects, and invoke a virtual function
    // that is overridden by the subclass, the subclass version will be invoked, instead of the superclass version
	virtual void printCodes (std::string bitString) const = 0;
	// Start printing the bitString (blank at first).
    // Invokes the serves of the overloaded version to do the real work.
	virtual void printCodes () { printCodes(""); }
    // virtual functon for drawing the huffman tree
    virtual void drawNode (char link, int depth) const = 0;  // pure function to be overridden
    // Draws the huffman tree rooted at t.  Invokes the serves of the 
    // overloaded version to do the real work.
    virtual void drawNode () { drawNode('-', 0); }
	// frequency getter
	double getFrequency () const { return frequency; }
};

// CharNode is a subclass of HuffmanNode (extends) for characters ('A' - 'Z')
class CharNode : public HuffmanNode {
	// character as data
	char character;
public:
	// Constructor
	CharNode (char ch, double freq): HuffmanNode(freq), character(ch) { }
	// member function printCodes: print characters ('A' - 'Z')
	// const override: a virtual function overrides another virtual function
	// http://en.cppreference.com/w/cpp/language/override
	void printCodes (std::string bitString) const override {	// overrides parent printCodes function
		cout << character << " : " << bitString << '\n';		// Ex: "A : "
	}
    // overrides the drawNode from superclass HuffmanNode to draw the leaves Ex: "/ [O:0.078509]"
    void drawNode (char link, int depth) {
        // Start drawing the node
        for (int i = 0; i < depth; i++) {
            std::cout << "   ";     // Add some space for depth
        }
        std::cout << link << " [" << character << ':' << std::setprecision(6) // rounded to 6 digits after decimal point
            << HuffmanNode::getFrequency() << ']' << '\n';      // drawing the node
    }
};

// InteriorNode is a subclass of HuffmanNode (extends). The most basic node in Huffman tree
class InteriorNode : public HuffmanNode {
	HuffmanNode *left;		    // left subtree pointer
	HuffmanNode *right;		    // right subtree pointer
public:
	// Constructor
	InteriorNode (double freq, HuffmanNode *lf, HuffmanNode *rt) :
		HuffmanNode(freq), left(lf), right(rt) { }
	// member function
	void printCodes (std::string bitString) const override {	// overrides parent printCodes function
		if (left != nullptr) 
			left->printCodes(bitString + '0');					// encode 0 for the lefts
		if (right != nullptr)
			right->printCodes(bitString + '1');                 // encode 1 for the rights
	}
    // overrides the drawNode from superclass HuffmanNode to draw the non-leaves Ex: "/ (0.152436)"
    void drawNode (char link, int depth) const override {
        // Start drawing everything on the right recursively
        right->drawNode ('/', depth + 1);
        // Start drawing the node
        for (int i = 0; i < depth; i++) {
            std::cout << "   ";     // Add some space for depth
        }
        std::cout << link << " (" << std::setprecision(6) << HuffmanNode::getFrequency() << ')' << '\n';
        // Start drawing everything on the right recursively
        left->drawNode ('\\', depth + 1);
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

// /*********** START OF THE DRAWING PART ***********/

// // Draws the huffman tree rooted at t.  Invokes the serves of the 
// // overloaded version to do the real work.
// void draw(HuffmanNode *node) {
// 	draw(node, '-', 0);
// }

// // Draws the rest of huffman tree rooted at t.  
// // "link" is a symbol to print in front of the node to which t points
// // indicating the direction of the branch leading to the node.
// // "depth" is proportional to depth of the node to which p points.
// template <typename T>
// static void draw(HuffmanNode *node, char link, int depth) {
//     // Check if the node is null, end the function
//     if (node == nullptr) return;

//     // Start drawing everything on the right recursively
//     draw (node->right, '/', depth + 1);
//     // Start drawing the root
//     // THE DRAWING PART
//     for (int i = 0; i < depth; i++) {
//         std::cout << "   ";     // Add some space for depth
//     }
//     std::cout << link << " [" << t->data << ']' << "\n"; // drawing the node
//     // Start drawing everything on the right recursively
//     draw (t->left, '\\', depth + 1);
// }

/*********** END OF THE DRAWING PART ***********/

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
    root->drawNode();
    inFile.close();
}