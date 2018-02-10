// linkedlist.h

/* 
    Author: Vo Huy
    Modified date: 1/18/18
    Assignment #1 LinkedList
    CPTR 318 Data Structures and Algorithms
*/

#include <iostream>
#include <utility> // For std::swap
#include <memory>  // For std::shared_ptr

template <typename T>
class LinkedList
{
    // The nested private Node class from before
    struct Node
    {
        T data;                     // A data element of the list
        std::shared_ptr<Node> next; // The node that follows this one
        // Constructor
        Node(const T &item) : data(item), next(nullptr) {}
    };

    std::shared_ptr<Node> head; // Points to the first item in the list
    std::shared_ptr<Node> tail; // Points to the last item in the list

    int len; // Number of elements in the list

  public:
    // The constructor makes an initially empty list.
    // The list is empty when head and tail are null.
    LinkedList() : head(nullptr), tail(nullptr), len(0) {}

    // Copy constructor makes a copy of the other object's list
    LinkedList(const LinkedList &other) : LinkedList()
    {
        // Walk through other's list inserting each of its elements
        // into this list
        for (auto cursor = other.head; cursor; cursor = cursor->next)
            insert(cursor->data);
    }

    // Move constructor takes possession of the temporary's list
    LinkedList(LinkedList &&temp) : LinkedList()
    {
        // Swap contents with the temporary
        std::swap(head, temp.head);
        std::swap(tail, temp.tail);
        std::swap(len, temp.len);
    }

    // The indexing operator allows a client to access an element
    // by its offset from the beginning of the list
    T &operator[](int index)
    {
        // if (index > len - 1) {
        //     return 
        // }
        auto cursor = head, // Start at head of list
            prev = head;    // Keep track of previous node seen
        // Loop until the cursor goes to the element at position "index" in the list
        // start from the beginning of the list
        for (int i = 0; i < index; ++i)
        {
            prev = cursor;         // Remember previous node
            cursor = cursor->next; // Move to next node
        }
        // Return the node for the element the client wants to access
        return cursor->data;
    }

    // Assignment operator
    LinkedList &operator=(const LinkedList &other)
    {
        // Make a local, temporary copy of other
        LinkedList temp{other};
        // Exchange the head and tail pointers and len from this list
        // with those of the new, temporary list
        std::swap(head, temp.head);
        std::swap(tail, temp.tail);
        std::swap(len, temp.len);
        // The temporary list now points to this list's original contents,
        // and this list now points to the copy of other's list
        // The temporary list will be destroyed since it is a temporary
        return *this;
    }

    // Move assignment operator
    LinkedList &operator=(LinkedList &&temp)
    {
        // Exchange the head and tail pointers and len from this list
        // with those of the new, temporary list
        std::swap(head, temp.head);
        std::swap(tail, temp.tail);
        std::swap(len, temp.len);
        // The temporary list now points to this list's original contents,
        // and this list now points to the temporary's list
        // The temporary list will be destroyed since it is a temporary
        return *this;
    }

    // Equality operator
    bool operator==(const LinkedList &other) const
    {
        // Make a local, temporary copy of other
        LinkedList temp{other};

        // If they have different lens, they are not equal, return false
        if (len != temp.len) 
            return false;

        auto cursor = head, tempCursor = temp.head; // Start at head of list
        while (cursor)
        {
            // Check the current values in both lists.
            if (cursor->data != tempCursor->data) {
                return false; // They don't match
            } 
            // Move to next node    
            cursor = cursor->next; 
            tempCursor = tempCursor->next;
        }
        return true; // The two lists contain the same elements in the same order
    }

    // The destructor deallocates the memory held by the list
    ~LinkedList()
    {
        clear();
    }

    // Inserts item onto the back of the list.
    // item is the element to insert.
    void insert(const T &item)
    {
        // Make a node for the new element n
        auto new_node = std::make_shared<Node>(item);
        if (tail)
        {                          // Is tail non-null?
            tail->next = new_node; // Link the new node onto the back
            tail = new_node;       // The new node is the new tail of the list
        }
        else // List is empty, so make head and tail point to new node
            head = tail = new_node;
        len++;
    }

    // Appends an element onto the front of the list.
    // item is the element to append.
    void prepend(const T &item)
    {
        // Make a node for the new element n
        auto new_node = std::make_shared<Node>(item);
        if (head) // Is head non-null?
        {
            // Make a node having data and next from the old head
            auto copiedHead = std::make_shared<Node>(head->data);
            copiedHead->next = head->next;
            // append the new element n to the front of copiedHead
            new_node->next = copiedHead;
            // change the head to the new element n
            head = new_node;

            // auto cursor = head, // Start at head of list
            // prev = head;    // Keep track of previous node seen
            // // Loop until we run off the end of the list.
            // while (cursor && cursor->data != item)
            // {
            //     prev = cursor;         // Remember previous node
            //     cursor = cursor->next; // Move to next node
            // }
        }
        else // List is empty, so make head and tail point to new node
            head = tail = new_node;
        len++;
    }

    // Accepts an argument of the same type as the elements in the list.
    // The function returns true if the argument appears in the list;
    // otherwise, the function returns false.
    bool member(const T &item)
    {
        auto cursor = head; // Start at head of list
        while (cursor && cursor->data != item)
        {
            cursor = cursor->next; // Move to next node
        }
        if (!cursor) // Did we run off the end of the list?
            // We did not find the argument in the list.
            return false;
        else
            // The argument appears in the list.
            return true;
    }

    // Removes the first occurrence of item from the list.
    // Returns true if successful (found item and removed it).
    // Returns false if item is not originally present in the list.
    bool remove(const T &item)
    {
        auto cursor = head, // Start at head of list
            prev = head;    // Keep track of previous node seen
        // Loop until we run off the end of the list or find n,
        // whichever comes first
        while (cursor && cursor->data != item)
        {
            prev = cursor;         // Remember previous node
            cursor = cursor->next; // Move to next node
        }
        if (!cursor)      // Did we run off the end of the list?
            return false; // Indicate we did not find n

        // Found n; cursor is pointing at the node containing n
        if (head == tail)              // n was the only element in the list
            head = tail = nullptr;     // cursor still points to node with n
        else if (cursor == head)       // Is n the first element in the list?
            head = head->next;         // Redirect head around n
        else                           // n is not the first element
            prev->next = cursor->next; // Redirect previous node around n
        if (cursor == tail)            // Was n the last element in the list?
            tail = prev;               // Update tail to new last element

        // No need to delete node; shared_ptr takes care of it
        len--;       // List size decreases by 1
        return true; // We found n and deleted its node
    }

    // Check the uniqueness of the elements
    bool unique() const 
    {
        // If the list is empty or contain only one element, it will be unique.
        if (len < 2) 
            return true;

        auto cursor = head, // Start at head of list
            prev = head,    // Keep track of previous node seen
            others = head; // The rest of the nodes in the list, excluding the "prev" node.
        // Loop until we run off the end of the list.
        while (cursor)
        {
            prev = cursor; // Remember previous node
            cursor = cursor->next; // Move to next node
            others = cursor; // Start checking others at the element right after the "prev"
            // Loop until we run off the end of the list
            // starting from the "next" node after the checkingElement
            while (others)
            {
                // Check if there is another element exist in the list
                if (prev->data == others->data) 
                    return false; 
                others = others->next; // Move to next node
            }
        }
        return true;
    }

    // Prints the contents of the linked list of integers.
    void print() const
    {
        for (auto cursor = head; cursor; cursor = cursor->next)
            std::cout << cursor->data << ' ';
        std::cout << '\n';
    }

    // Returns the length of the linked list.
    int length() const
    {
        return len;
    }

    // Removes all the elements in the linked list.
    void clear()
    {
        head = tail = nullptr; // Null head signifies list is empty
        len = 0;
    }

    // Provide a convenient way to print a linked list
    template <typename V>
    friend std::ostream &operator<<(std::ostream &os,
                                    const LinkedList<V> &list);
};

// Prints a linked list object to an output stream
template <typename T>
std::ostream &operator<<(std::ostream &os, const LinkedList<T> &list)
{
    os << '{';
    auto cursor = list.head;
    if (cursor)
    {
        os << cursor->data;
        cursor = cursor->next;
        while (cursor)
        {
            os << ", " << cursor->data;
            cursor = cursor->next;
        }
    }
    os << '}';
    return os;
}