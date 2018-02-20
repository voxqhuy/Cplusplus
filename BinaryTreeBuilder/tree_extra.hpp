//  Name: Vo Huy
//  Binary Tree Build
//  File name: tree_extra.cpp
//  Date last modified: Deb 25, 2018

// Draws the binary tree rooted at t.  
// Parameter link is a symbol to print in front of the node to
// which t points indicating the direction of the branch leading 
// to the node.
// Parameter depth is proportional to depth of the node to which p
// points.
template <typename T>
static void draw(Node<T> *t, char link, int depth) {
    // Check if the node is null, end the function
    if (t == nullptr) return;
    // 

    // Start drawing everything on the right recursively
    draw (t->right, '/', depth + 1);
    // Start drawing the root
    // THE DRAWING PART
    if (depth == 0) {
        std::cout << "-[" << t->data << ']'; // Can this be improved????
    } else {
        for (int i = 0; i < depth; i++) {
            std::cout << "   ";
        }
        if (link == '/') {
            std::cout << "/[" << t->data << ']';
        } else if (link == '\\') {
            std::cout << "\\[" << t->data << ']';
        }
    }
    std::cout << "\n";
    // Start drawing everything on the right recursively
    draw (t->left, '\\', depth + 1);
}


// Frees up the space held by the nodes in a binary tree 
// rooted at t.
template <typename T>
void dispose(Node<T> *t) {
    // Check if the node is null, end the function
    if (t == nullptr) return;
    // Start deleting everything on the left and right recursively, the functions will end
    // when they go out of the tree (or nullptr)
    dispose (t->right);
    dispose (t->left);
    // Delete the node itself after the left and right dispose functions are done
    free(t);
}


// Builds a binary tree from preorder and inorder traversals.
// Parameter pre_begin is an iterator to the beginning of the
// preorder traveral sequence.
// Parameter pre_end is an iterator to the end of the preorder 
// traveral sequence.
// Parameter in_begin is an iterator to the beginning of the
// inorder traveral sequence.
// Parameter in_end is an iterator to the end of the inorder
// traveral sequence.
// Returns a pointer to the root of the newly created binary tree.
template <typename T>
static Node<T> *build_tree(typename std::vector<T>::const_iterator pre_begin, 
                           typename std::vector<T>::const_iterator pre_end,
                           typename std::vector<T>::const_iterator in_begin, 
                           typename std::vector<T>::const_iterator in_end) {
    /*************************************************
     * Replace following statement with your code
     *************************************************/
    return nullptr;  
}