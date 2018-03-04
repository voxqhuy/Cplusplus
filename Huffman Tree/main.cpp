/* NOTICES 
    1. These classes are based on class 318 lecture at SAU by Dr. Halterman

    2.virtual function:  To implement polymorphism 
    If the superclass pointer is aiming at a subclass objects, and invoke a virtual function
    that is overridden by the subclass, the subclass version will be invoked, instead of the superclass version
    https://www.ntu.edu.sg/home/ehchua/programming/cpp/cp6_Inheritance.html
    
    3.Customed strict weak ordering
    https://stackoverflow.com/a/19535699/8969722

    4."= 0" : this is a pure method https://stackoverflow.com/a/21187983/8969722

    5. override: a virtual function overrides another virtual function
	http://en.cppreference.com/w/cpp/language/override
*/

/*********** THE CLASS PART ***********/

/*   
   Huffman Node's visualization: 
 
          (Huffman Node)
			 ^	  ^
			/      \
		   /		\
	(Char Node)	 (Interior Node)	
*/

#include <fstream>
#include <iostream>     // std::cout, std::fixed
#include <string>
#include <queue>        // std::priority_queue
#include <vector>       // std::vector
#include <math.h>       // round, floor, ceil, trunc 
#include <iomanip>      // std::setprecision
using namespace std;

// A class that contains a Compare (for sorting A to Z) for all Nodes subclasses
class AZNode 
{
public:
    // Ordering A to Z
    class CompareAlphabets
    {
    public:
        bool operator()(pair<char, string> code1, pair<char, string> code2) {
            // return A is ordered after Z
            return code1.first > code2.first; 
        }
    };
};

// Huffman Node class
class HuffmanNode : public AZNode {
private:
	double frequency;       // Frequency as data
public:
	// Constructor
	HuffmanNode (double freq): frequency(freq) {}
	// member function encode: Huffman encoding (and attach each code to each character)
	virtual void encode (string bitString,
        priority_queue<pair<char, string>, vector<pair<char, string>>, 
        AZNode::CompareAlphabets>& codes) = 0;      
	// Start encoding, start with blank
	virtual void encode (priority_queue<pair<char, string>, 
        vector<pair<char, string>>, AZNode::CompareAlphabets>& codes) 
    { 
        encode("", codes); 
    }
    // Draws the huffman tree
    virtual void drawNode (char link, int depth) const = 0;  
    // Draws the huffman tree rooted at t.  Invokes the serves of the 
    // overloaded version to do the real work.
    virtual void drawNode () { drawNode('-', 0); }
	// frequency getter
	double getFrequency () const { return frequency; }
    // Compare the frequency, smaller first
    class CompareFreq
    {
    public:
        bool operator()(HuffmanNode const * node1, HuffmanNode const * node2) {
            // return "true" if "node2" freq is ordered before "node1" freq
            return node1->frequency > node2->frequency;
        }
    };
};

// CharNode is a subclass of HuffmanNode (extends) for characters ('A' - 'Z')
class CharNode : public HuffmanNode {
private:
	char character;     // character as data
public:
	// Constructor
	CharNode (char ch, double freq): HuffmanNode(freq), character(ch) { }
	// member function encode
	void encode (string bitString, 
        priority_queue<pair<char, string>, vector<pair<char, string>>, 
        AZNode::CompareAlphabets>& codes) override
    {	
        codes.push(make_pair(character, bitString));    // add to the sorted queue ("char: codes")
	}
    // overrides the drawNode from superclass HuffmanNode to draw the leaves Ex: "/ [O:0.078509]"
    void drawNode (char link, int depth) const override {
        // Start drawing the node
        for (int i = 0; i < depth; i++) {
            cout << "     ";     // Add some space for depth
        }
        cout << link << " [" << character << ':' << fixed       // rounded to 6 digits after decimal point
            << setprecision(6) << HuffmanNode::getFrequency() << ']' << '\n';   // drawing the node
    }
};

// InteriorNode is a subclass of HuffmanNode (extends). The most basic node in Huffman tree
class InteriorNode : public HuffmanNode {
private:
	HuffmanNode *left;		    // left subtree pointer
	HuffmanNode *right;		    // right subtree pointer
public:
	// Constructor
	InteriorNode (double freq, HuffmanNode *lf, HuffmanNode *rt) :
		HuffmanNode(freq), left(lf), right(rt) { }
	// member function
	void encode (string bitString, 
        priority_queue<pair<char, string>, vector<pair<char, string>>, 
        AZNode::CompareAlphabets>& codes) override
    {	
		if (left != nullptr) 
			left->encode(bitString + '0', codes);					// encode 0 for the lefts
		if (right != nullptr)
			right->encode(bitString + '1', codes);                 // encode 1 for the rights
	}
    // overrides the drawNode from superclass HuffmanNode to draw the non-leaves Ex: "/ (0.152436)"
    void drawNode (char link, int depth) const override {
        // Start drawing everything on the right recursively
        right->drawNode ('/', depth + 1);
        // Start drawing the node
        for (int i = 0; i < depth; i++) {
            cout << "     ";     // Add some space for depth
        }
        cout << link << " (" << fixed << setprecision(6)
            << HuffmanNode::getFrequency() << ')' << '\n';
        // Start drawing everything on the right recursively
        left->drawNode ('\\', depth + 1);
    }
};

/*********** THE FUNCTIONS PART ***********/

vector<pair<char, double>> printFrequency(int* freq, int total) {
    // the vector that keeps characters with their frequencies
    vector<pair<char, double>> symbols;
    // Loop through the freq array (keeping frequencies of 26 elements)
    for(int i = 'A'; i <= 'Z'; i++) {
        char ch =  static_cast<char>(i);        // the character
        int frequency = freq[i-'A'];            // the frequency of the character
        // keep adding each character with its % frequency (its frequency / total)
        symbols.push_back(make_pair(ch, 
            round(1000000.0 * frequency / total) / 1000000.0)); // rounded to 6 numbers after the decimal point

        cout << ch << ": " << frequency << '\n';
    }
    cout << "Total = " << total << '\n';        // print the total

    return symbols;
}

HuffmanNode *build_huffman(const vector<pair<char, double>>& symbols) {
    // Make an empty priority queue
    priority_queue<HuffmanNode*, vector<HuffmanNode*>, HuffmanNode::CompareFreq> queue;
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

void printCodes(priority_queue<pair<char, string>, vector<pair<char, string>>, 
    AZNode::CompareAlphabets> codes) 
{
    while(codes.size() > 0) {
        pair<char, string> code = codes.top();
        codes.pop();
        cout << code.first << ": " << code.second << '\n';
    }
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
        cout  << "Unable to open file declaration.text";
        exit(1);                // Unable to open the file, exit the function
    }
    // Reading the text
    inFile >> noskipws;         // including the whitespace
    while (inFile >> ch) {
        cout << ch;             // printing out the texts
        freq[toupper(ch) - 'A']++;         // adding 1 to the frequency of the letter (capitialized)
        if (isalpha(toupper(ch))) total++;                 // increase the number of letter
    }

    cout << '\n' << "Counts:" << '\n' << "-------" << '\n';
    // make a vector pair with format "char: frequency" (Ex: A: 0.003)
    // print out the frequencies
    HuffmanNode *root = build_huffman(printFrequency(freq, total));
    cout << "---------------------------------" << '\n' << '\n';

    // build Huffman tree
    root->drawNode();
    cout << "---------------------------------" << '\n' << '\n';

    priority_queue<pair<char, string>, vector<pair<char, string>>, 
        AZNode::CompareAlphabets> sortedEncodeds; 
    // attach encoded bits to each character
    root->encode(sortedEncodeds);
    // print encoded bits with each character
    printCodes(sortedEncodeds);
    
    inFile.close();     
}