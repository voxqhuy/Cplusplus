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
        case 'I': // Insert a new element into the list
        case 'i':
            if (std::cin >> value)
                list.insert(value);
            else
                done = true;
            break;

        case 'A': // Append an element onto the front of the list.
        case 'a':
            if (std::cin >> value)
                list.prepend(value);
            else
                done = true;
            break;

        case 'G': // Get an element at a position of the list.
        case 'g':
            if (std::cin >> value)
                std::cout << "The element at position " << value << " is " << list[value] << "\n";
            else
                done = true;
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
        case 'P': // Print the contents of the list
        case 'p':
            list.print();
            break;
        case 'L': // Print the list's length
        case 'l':
            std::cout << "Number of elements: " << list.length() << '\n';
            break;
        case 'E': // Erase the list
        case 'e':
            list.clear();
            break;
        case 'Q': // Exit the loop (and the program)
        case 'q':
            done = true;
            break;
        }
    }
}
