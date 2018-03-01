//  tree.hpp

// Represents a node in a binary tree.
// template <typename T>
// struct Node {
// 	T data;
// 	Node *left;
// 	Node *right;
// 	Node(const T& d, Node *lf, Node *rt) :
// 		data(d), left(lf), right(rt) {}
// };

// Huffman Node 
class HuffmanNode {
	// Frequency as data
	double frequency;
	public:
		// member function print code: print Huffman encoded codes
		virtual void
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
