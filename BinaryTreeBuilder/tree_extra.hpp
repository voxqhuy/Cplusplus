//  Name: Vo Huy
//  Binary Tree Build
//  File name: tree_extra.cpp
//  Date last modified: Dec 19, 2018

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
        std::cout << "-[" << t->data << ']';                    // Can this be improved????
    } else {
        for (int i = 0; i < depth; i++) {
            std::cout << "   ";     // Add some space for depth
        }
        if (link == '/') {
            std::cout << "/[" << t->data << ']';    // right branch 
        } else if (link == '\\') {
            std::cout << "\\[" << t->data << ']';   // left branch
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
    // Create a new tree (or node) for returning
    // The root is the first element in the pre-ordered tree
    Node<T> *new_tree = new Node<T>(*pre_begin, nullptr, nullptr);  // Unsure about this line of code. how to get the number to data
    // If the sequence has only one element, end the function and return the node
    if (pre_begin == pre_end) return new_tree;

    // Making copies of iterators 
    // Unsure about these, could be improved
    //typename std::vector<T>::const_iterator new_pre_begin, new_pre_end, new_in_begin, new_in_end;
    //new_pre_begin = pre_begin + 1;      // The sub pre-ordered tree starts at the first element after the root
    //new_in_begin = in_begin;        // The sub in-ordered tree starts at the first element

    typename std::vector<T>::const_iterator it;     // New iterator for looping
    int passedElements = 0;     // Keep track of looped elements for making sub-trees
    // Looping through in-odered tree until reaching the root element
    for (it = in_begin; it != in_end; it++) {
        if (*it == *pre_begin) break;        //Reached the root element, break the for loop
        passedElements++;       //Number passed +1
    }

    //new_pre_end = new_pre_begin + passedElements;
    //new_in_end = new_in_begin + passedElements;
    // Can iterator go beyond the range? before it_begin or after it_end?
    //if (passedElements == 0) {
    //    new_tree->left = nullptr;
    //} else {
    new_tree->left = build_tree<T>(pre_begin + 1, pre_begin + passedElements,
                                in_begin, in_begin + passedElements - 1);
    //}

    //if ((pre_begin + passedElements == pre_end) || (in_begin + passedElements == in_end)) {
    //    new_tree->right = nullptr;
    //} else {
    new_tree->right = build_tree<T>(pre_begin + 1 + passedElements, pre_end,
                                 in_begin + passedElements + 1, in_end);
    //}

    // Return the newly created binary tree
    return new_tree;  
}