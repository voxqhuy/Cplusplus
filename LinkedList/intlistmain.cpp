// intlistmain.cpp

#include <iostream>
#include <string>
#include "linkedlist.h"

int main()
{
    bool done = false;
    char command;
    int value;
    LinkedList<int> list; // Instantiated for integers

    while (!done)
    {
        std::cout << "I)nsert <item> A)ppend <item> G)et <item> M)ember <item> D)elete <item> P)rint  L)ength  E)rase Q)uit >>";
        std::cin >> command;
        switch (command)
        {
        case 'A': // Append an element onto the front of the list.
        case 'a':
            if (std::cin >> value)
                list.prepend(value);
            else
                done = true;
            break;

        case 'D': // Delete an element from the list
        case 'd':
            if (std::cin >> value)
                if (list.remove(value))
                    std::cout << value << " removed\n";
                else
                    std::cout << value << " not found\n";
            else
                done = true;
            break;

        case 'E': // Erase the list
        case 'e':
            list.clear();
            break;

        case 'G': // Get an element at a position of the list.
        case 'g':
            if (std::cin >> value)
                std::cout << "The element at position " << value << " is " << list[value] << "\n";
            else
                done = true;
            break;

        case 'I': // Insert a new element into the list
        case 'i':
            if (std::cin >> value)
                list.insert(value);
            else
                done = true;
            break;

        case 'L': // Print the list's length
        case 'l':
            std::cout << "Number of elements: " << list.length() << '\n';
            break;

        case 'M': //  Check if an element appears in the list
        case 'm':
            if (std::cin >> value)
            {
                std::string result = (list.member(value) == 1) ? "true\n" : "false\n";
                std::cout << result;
            }
            else
                done = true;
            break;

        case 'P': // Print the contents of the list
        case 'p':
            list.print();
            break;

        case 'Q': // Exit the loop (and the program)
        case 'q':
            done = true;
            break;

        case 'U': //  Check if all elements in the list are unique
        case 'u':
            std::string result = (list.unique() == 1) ? "true\n" : "false\n";
            std::cout << result;
            break;
        }
    }
}

// #include <iostream>
// #include <iomanip>
// #include "linkedlist.h"

// int main() {
//     LinkedList<int> seq1;
//     seq1.insert(10);
//     seq1.insert(20);
//     seq1.insert(30);

//     std::cout << seq1 << '\n';

//     // Check prepend
//     seq1.prepend(5);
//     std::cout << seq1 << '\n';
//     seq1.prepend(88);
//     std::cout << seq1 << '\n';

//     // Check rvalue operator[]
//     for (int i = 0; i < seq1.length(); i++)
//         std::cout << seq1[i] << ' ';
//     std::cout << '\n' << seq1 << '\n';

//     // Check lvalue operator[]
//     for (int i = 0; i < seq1.length(); i++)
//         seq1[i] = 2*i;
//     std::cout << seq1 << '\n';  // should print {0, 2, 4, 6, 8}

//     // Condition the output stream to print Booleans as true or false
//     std::cout << std::boolalpha;

//     for (int i = 0; i < 10; i++) 
//         std::cout << seq1.member(i) << ' ';
//     std::cout << '\n';

//     auto seq2{seq1};
//     std::cout << (seq1 == seq2) << '\n';
//     std::cout << (seq2 == seq1) << '\n';
//     seq1.insert(9);
//     std::cout << (seq1 == seq2) << '\n';
//     std::cout << (seq2 == seq1) << '\n';

//     auto const seq3{seq1};
//     std::cout << (seq1 == seq3) << '\n';
//     std::cout << (seq3 == seq1) << '\n';

//     std::cout << seq1 << '\n';
//     std::cout << seq1.unique() << '\n';
//     seq1.prepend(8);
//     std::cout << seq1 << '\n';
//     std::cout << seq1.unique() << '\n';

//     auto const seq4{seq1};
//     std::cout << seq4.unique() << '\n';

//     LinkedList<int> seq5;
//     seq5.insert(1);
//     seq5.insert(2);
//     seq5.insert(3);
//     std::cout << seq5 << '\n';
//     auto const seq6{seq5};
//     std::cout << seq6.unique() << '\n';

//     LinkedList<int> seq7;
//     std::cout << seq7 << '\n';
//     std::cout << seq7.unique() << '\n';



// }