#include <iostream>
#include <iomanip>
#include "linkedlist.h"

int main() {
    LinkedList<int> seq1;
    seq1.insert(10);
    seq1.insert(20);
    seq1.insert(30);

    std::cout << seq1 << '\n';

    // Check prepend
    seq1.prepend(5);
    std::cout << seq1 << '\n';
    seq1.prepend(88);
    std::cout << seq1 << '\n';

    // Check rvalue operator[]
    for (int i = 0; i < seq1.length(); i++)
        std::cout << seq1[i] << ' ';
    std::cout << '\n' << seq1 << '\n';

    // Check lvalue operator[]
    for (int i = 0; i < seq1.length(); i++)
        seq1[i] = 2*i;
    std::cout << seq1 << '\n';  // should print {0, 2, 4, 6, 8}

    // Condition the output stream to print Booleans as true or false
    std::cout << std::boolalpha;

    for (int i = 0; i < 10; i++) 
        std::cout << seq1.member(i) << ' ';
    std::cout << '\n';

    auto seq2{seq1};
    std::cout << (seq1 == seq2) << '\n';
    std::cout << (seq2 == seq1) << '\n';
    seq1.insert(9);
    std::cout << (seq1 == seq2) << '\n';
    std::cout << (seq2 == seq1) << '\n';

    auto const seq3{seq1};
    std::cout << (seq1 == seq3) << '\n';
    std::cout << (seq3 == seq1) << '\n';

    std::cout << seq1 << '\n';
    std::cout << seq1.unique() << '\n';
    seq1.prepend(8);
    std::cout << seq1 << '\n';
    std::cout << seq1.unique() << '\n';

    auto const seq4{seq1};
    std::cout << seq4.unique() << '\n';

    LinkedList<int> seq5;
    seq5.insert(1);
    seq5.insert(2);
    seq5.insert(3);
    std::cout << seq5 << '\n';
    auto const seq6{seq5};
    std::cout << seq6.unique() << '\n';

    LinkedList<int> seq7;
    std::cout << seq7 << '\n';
    std::cout << seq7.unique() << '\n';



}
