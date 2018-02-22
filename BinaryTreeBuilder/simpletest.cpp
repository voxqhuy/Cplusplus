#include <iostream>
#include <vector>
#include <string>

// Your code included here
#include "tree.hpp"


int main() {
    std::vector<int> pre{36, 100, 11, 3, 10, 5, 2, 8},  // preorder
                     in{11, 100, 10, 3, 5, 36, 8, 2};   // inorder

    Node<int> *int_tree = build_tree<int>(pre, in); 

    draw(int_tree);

    std::cout << "====================\n";

    std::vector<int> pre1{8},  // preorder
                     in1{8};   // inorder

    Node<int> *int_tree1 = build_tree<int>(pre1, in1); 

    draw(int_tree1);

    std::cout << "====================\n";

    std::vector<int> pre2{},  // preorder
                     in2{};   // inorder

    Node<int> *int_tree2 = build_tree<int>(pre2, in2); 

    draw(int_tree2);


    std::cout << "====================\n";

    std::vector<std::string> ps{"Xena", "Albert", "Quin", "Pat", "Henry", "Kit"},
                             is{"Quin", "Albert", "Pat", "Xena", "Kit", "Henry"};

    Node<std::string> *str_tree = build_tree<std::string>(ps, is);
    draw(str_tree);

    std::cout << "====================\n";

     Node<int> *sample_tree = new Node<int>(14, 
                                       new Node<int>(11,
                                            new Node<int>(12, nullptr, nullptr),
                                            new Node<int>(5, nullptr, nullptr)),
                                       new Node<int>(6, 
                                            nullptr, 
                                            new Node<int>(5, nullptr, nullptr)));

    draw(sample_tree);
}