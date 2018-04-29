#include <iostream>  //  For normal output: cout, endl
#include <fstream>   //  For file streams
#include <iomanip>   //  For the hex and dec stream manipulators
#include <vector>    //  std::vector
#include <string>
#include <cstddef>   //  std::size_t

using namespace std;

struct Node {
    int data;
    Node *left;
    Node *right;
    Node (const int d, Node *lf, Node *rt) :
        data(d), left(lf), right(rt) {}
};

int main() {
    Node *node1 = new Node(
        1,
        new Node(
            2,
            new Node(
                3,
                nullptr,
                nullptr
            ),
            new Node (
                4,
                nullptr,
                nullptr
            )
        ),
        new Node(
            3,
            new Node(
                2,
                nullptr,
                nullptr
            ),
            new Node (
                4,
                nullptr,
                nullptr
            )
        )
    );

    Node *node2 = new Node(
        1,
        new Node(
            2,
            new Node(
                3,
                nullptr,
                nullptr
            ),
            new Node (
                4,
                nullptr,
                nullptr
            )
        ),
        new Node(
            3,
            new Node(
                2,
                nullptr,
                nullptr
            ),
            new Node (
                4,
                nullptr,
                nullptr
            )
        )
    );

    Node *node3 = new Node(
        1,
        new Node(
            2,
            nullptr,
            nullptr
        ),
        nullptr
    );

    Node *node4 = new Node(
        1,
        new Node(
            2,
            nullptr,
            nullptr
        ),
        nullptr
    );

    Node *node5 = new Node(
        1,
        new Node(
            1,
            nullptr,
            nullptr
        ),
        new Node(
            2,
            nullptr,
            nullptr
        )
    );

    Node *node6 = new Node(
        1,
        new Node(
            1,
            nullptr,
            nullptr
        ),
        new Node(
            2,
            nullptr,
            nullptr
        )
    );

    Node *node7 = new Node(
        1,
        nullptr,
        nullptr
    );

    Node *node8 = new Node(
        1,
        nullptr,
        nullptr
    );

    Node *node9 = new Node(
        1,
        new Node(
            1,
            nullptr,
            nullptr
        ),
        new Node(
            1,
            nullptr,
            nullptr
        )
    );

    Node *node10 = new Node(
        1,
        new Node(
            1,
            nullptr,
            nullptr
        ),
        new Node(
            1,
            nullptr,
            nullptr
        )
    );

    Node *node11 = new Node(
        1,
        new Node(
            1,
            nullptr,
            new Node (
                2,
                nullptr,
                nullptr
            )
        ),
        new Node(
            1,
            nullptr,
            nullptr
        )
    );

    Node *node12 = new Node(
        1,
        new Node(
            1,
            nullptr,
            new Node (
                2,
                nullptr,
                nullptr
            )
        ),
        new Node(
            1,
            nullptr,
            nullptr
        )
    );

    Node *node13 = new Node(
        1,
        new Node(
            1,
            nullptr,
            new Node (
                2,
                nullptr,
                nullptr
            )
        ),
        new Node(
            1,
            nullptr,
            new Node (
                2,
                nullptr,
                nullptr
            )
        )
    );

    Node *node14 = new Node(
        1,
        new Node(
            2,
            new Node(
                3,
                nullptr,
                nullptr
            ),
            new Node (
                4,
                nullptr,
                nullptr
            )
        ),
        new Node(
            2,
            nullptr,
            nullptr
        )
    );

    Node *node15 = new Node(
        1,
        new Node(
            2,
            new Node(
                3,
                nullptr,
                nullptr
            ),
            new Node (
                4,
                nullptr,
                nullptr
            )
        ),
        new Node(
            3,
            nullptr,
            nullptr
        )
    );

    Node *node16 = new Node(
        1,
        new Node(
            2,
            new Node(
                3,
                nullptr,
                nullptr
            ),
            nullptr
        ),
        new Node(
            3,
            nullptr,
            nullptr
        )
    );

    Node *node17 = new Node(
        1,
        new Node(
            2,
            new Node(
                3,
                nullptr,
                nullptr
            ),
            new Node (
                4,
                nullptr,
                nullptr
            )
        ),
        new Node(
            3,
            nullptr,
            new Node(
                4,
                nullptr,
                nullptr
            )
        )
    );
}