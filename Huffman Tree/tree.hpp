//  huffmanTree.hpp

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
	virtual void printCodes(string bitString) const = 0;
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
	void printCodes (string bitString) const override {			// overrides parent printCodes function
		cout << character << " : " << bitString << endl;		// Ex: "A : "
	}
}

// InteriorNode is a subclass of HuffmanNode (extends). The most basic node in Huffman tree
class InteriorNode : public HuffmanNode {
	HuffmanNode *left;		// left subtree pointer
	HuffmanNode *right;		// right subtree pointer
public:
	// Constructor
	InteriorNode(double freq, HuffmanNode *lf, HuffmanNode *rt) :
		HuffmanNode (freq), left(lf), right(rt) { }
	// member function
	void printCodes(string bitString) const override {			// overrides parent printCodes function
		if (left != nullptr) 
			left->printCodes(bitString + '0');					// encode 0 for the lefts
		if (right != nullptr)
			right->printCodes(bitString + '1');
	}
}

















// Draws the binary tree rooted at t.  Invokes the serves of the 
// overloaded version to do the real work.
template <typename T>
void draw(Node<T> *t) {
	draw(t, '-', 0);
}


// // Builds a binary tree from preorder and inorder traversals.
// // Invokes the services of the overloaded version that 
// // accepts iterators to the vectors.
// // Parameter preorder is a vector storing the preorder traversal sequence.
// // Parameter inorder is a vector storing the inorder traversal sequence.
// // Returns a pointer to the root of the newly created binary tree.
// template <typename T>
// Node<T> *build_tree(const std::vector<T>& preorder,
//                     const std::vector<T>& inorder) {
//     return build_tree<T>(begin(preorder), end(preorder),
//                          begin(inorder), end(inorder));
// }
