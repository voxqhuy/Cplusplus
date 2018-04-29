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

// Calculate the distance from the root to the closest node
// that holds the given data value
int distance(const Node *t, int value) {
    if (t == nullptr) {
        return -1;
    }
    int d = -1;
    if ((t->data == value) 
        || (d = distance(t->left, value)) >= 0 
        || (d = distance(t->right, value)) >= 0) {
        return d + 1;
    }
    return d;
}

int count(const Node*t, int value) {
    if (t == nullptr) {
        return 0;
    }
    int c = 0;
    if (t->data == value) {c++;}
    c += count(t->left, value);
    c += count(t->right, value);
    return c;
}

bool equals(const Node*t1, const Node *t2) {
    if (!t1  && !t2) {
        return true;
    } else if (!t1 || !t2) {
        return false;
    }
    if (t1->data != t2->data) {
        return false;
    }
    if (!equals(t1->left, t2->left) || !equals(t1->right, t2->right)) {return false;}
    return true;        // no falses
}

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

    // cout << distance(node2, 4);
    // cout << distance(node2, 5);
    // cout << distance(node2, 2);
    // cout << distance(node2, 1);
    // cout << distance(node2, 3);

    // cout << count(node2, 4);
    // cout << count(node2, 5);
    // cout << count(node2, 2);
    // cout << count(node2, 1);
    // cout << count(node2, 3);

    cout << equals(node1, node2);
    cout << equals(node1, node1);
    cout << equals(node1, node17);
    cout << equals(node14, node15);
    cout << equals(node12, node13);
    cout << equals(node15, node16);
}