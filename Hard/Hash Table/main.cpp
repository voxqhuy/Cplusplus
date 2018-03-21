//  Name: Vo Huy
//  Assignment number: 5
//  Assignment: Spell Checking with the Hash Table Data Structure
//  File name: huy.cpp
//  Date last modified: March 27, 2018
//  Honor statement: I have neither given nor received any unauthorized help on this assignment. 

#include <iostream>     // std::cout, std::fixed
#include <vector>       // std::vector
#include <string>
#include <queue>        // std::priority_queue
#include <cstddef>      // std::size_t
using namespace std;

// Each Node in HashTable
class HashNode {
private:
    string str;
    HashNode* next = nullptr;
public:
//     // Constructor
//     HashNode(int key, string value): mKey(key), mValue(value) {

//     }
    string getString() {
        return str;
    }
    HashNode* getNext() {
        return next;
    }
    void setString(string str) {
        this->str = str;
    }
    void setNext(HashNode* next) {
        this->next = next;
    }
};

// HashTable class
class HashTable {
private:
    // hash nodes array
    HashNode **nodesArray;
    // hash table size
    unsigned mTableSize;
    string mFileName;
public:
    // Constructor
    HashTable (unsigned tableSize, string fileName) {
        this->mTableSize = tableSize;
        this->mFileName = fileName;
        // Initialize the size of hash table
        nodesArray = new HashNode*[tableSize];

        // initialize all nodes as null
        for (unsigned i = 0; i < tableSize; i++) 
            nodesArray[i] = NULL;
    }

    // hash function maps a string to an index within the table
    // Using Fowler-Noll-Vo Hash (FNV1a)
    // based on:https://www.programmingalgorithms.com/algorithm/fnv-hash?lang=C%2B%2B
    unsigned hash(string str) {
        const unsigned fnv_prime = 0x811C9DC5;
        unsigned hash = 0;      // hashing index

        for (unsigned i = 0; i < str.length(); i++)
        {
            hash *= fnv_prime;
            hash ^= (str[i]);
        }
        // return the index the string is mapping to
        return hash % mTableSize;
    }

    // insert method inserts a string into the hash table
    // return true if it successfully inserts the word into the table
    // otherwise, it should return false if the word already is present in the table
    bool insert(string str) {
        unsigned location = hash(str); 
        if(nodesArray[location] == NULL) {
            // the position is empty, create a note
            nodesArray[location].setString(str);
        } else {        // the position is non empty
            // the pointer at the position
            HashNode* ptr = nodesArray[location];
            if (ptr.getString() == str) 
                retrun false;       // the word already is present
            // Create a new node to add
            HashNode* hashNode = new HashNode;
            hashNode->setString(str);
            // loop to the end of the list at the position
            while (ptr->next != nullptr) {
                ptr = ptr->next;
                if (ptr.getString() == str) 
                    retrun false;   // the word already is present 
            }
            // stick the new node to the position
            ptr->next = hashNode;
        }
        return true;
    }

    // remove method removes a string from the hash table 
    // returns true if it removes the word
    // otherwise, it returns false if the word to remove is not in the hash table
    bool remove() {
        return false;
    }

    // returns true if the hash table contains a given string
    // otherwise, the method returns false if the string is not present
    bool contains(string str) {
        return false;
    }

    // returns the total number of strings in the hash table
    int size() {
        return mTableSize;
    }
};

// Ordering a to z for priority queue
class CompareAlphabets
{
public:
    bool operator()(string str1, string str2) {
        // return a is ordered after z
        return str1 > str2; 
    }
};

// checking for an omission
void checkOmission(string userInput, HashTable* hashTable, 
    priority_queue<string, std::vector<string>, CompareAlphabets>& correctedWords) {  
    // Try adding a single letter at all possible places in the word
    // If any match a word in the hash table, push into the queue for printing later
    for (size_t i = 0; i <= userInput.length(); i++) {
        for (char j = 'a'; j <= 'z'; j++) {
            string testingWord = userInput;     // make a copy of userInput to test 
            if (hashTable->contains(testingWord.insert(i, string(1, j)))) { // FIXME: j doesn't work, has to convert j to string??
                correctedWords.push(testingWord);
            }
        }
    }
}

// checking for an extra letter
void checkExtra(string userInput, HashTable* hashTable, 
    priority_queue<string, std::vector<string>, CompareAlphabets>& correctedWords) {
    // Try removing a single letter from the word
    // If any match a word in the hash table, push into the queue for printing later
    for (size_t i = 0; i < userInput.length(); i++) {
        string testingWord = userInput;         // make a copy of userInput to test
        if (hashTable->contains(testingWord.erase(i, 1))) {
            correctedWords.push(testingWord);
        }
    }
}

// checking for a typo
void checkTypo(string userInput, HashTable* hashTable, 
    priority_queue<string, std::vector<string>, CompareAlphabets>& correctedWords) {
    // Try replacing an existing letter in the word with some other letter
    // If any match a word in the hash table, push into the queue for printing later
    for (size_t i = 0; i < userInput.length(); i++) {
        for (char j = 'a'; j <= 'z'; j++) {
            string testingWord = userInput;     // make a copy of userInput to test 
            if (hashTable->contains(testingWord.replace(i, 1, string(1, j)))) { // FIXME: j doesn't work, has to convert j to string??
                correctedWords.push(testingWord);
            }
        }
    }
}

// checking for a transposition
void checkTransposition(string userInput, HashTable* hashTable, 
    priority_queue<string, std::vector<string>, CompareAlphabets>& correctedWords) {
    // Try transposing adjacent letters
    // If any match a word in the hash table, push into the queue for printing later
    for (size_t i = 0; i < userInput.length() - 1; i++) {
        string testingWord = userInput;         // make a copy of userInput to test
        swap(testingWord[i], testingWord[i + 1]);       // swapping 2 adjacent elements
        if (hashTable->contains(testingWord)) {
            correctedWords.push(testingWord);
        }
    }
}

// checking for a missing space
void checkMissingSpace(string userInput, HashTable* hashTable, 
    priority_queue<string, std::vector<string>, CompareAlphabets>& correctedWords) {
    // Try adding a single space at all possible places in the word
    // If any match a word in the hash table, push into the queue for printing later
    for (size_t i = 1; i < userInput.length(); i++) {
        string testingWord = userInput;         // make a copy of userInput to test 
        if (hashTable->contains(testingWord.insert(i, string(1, ' ')))) { // FIXME: j doesn't work, has to convert j to string??
            correctedWords.push(testingWord);
        }
    }
}

// Attempt to correct the user input
void correction(string userInput, HashTable* hashTable) {
    // Make an empty priority queue
    priority_queue<string, std::vector<string>, CompareAlphabets> correctedWords;
    // Note: The functions below CHANGE correctedWords
    // check if the user omitted a letter
    checkOmission(userInput, hashTable, correctedWords);
    // check if the user added an extraneous letter
    checkExtra(userInput, hashTable, correctedWords);
    // check if the user mistyped a letter
    checkTypo(userInput, hashTable, correctedWords);
    // check if the user tranposed 2 adjacent letter
    checkTransposition(userInput, hashTable, correctedWords);
    // check if the user forgot to add a space
    checkMissingSpace(userInput, hashTable, correctedWords);

    // print out corrected words in alphabetic order, if there's none, print ???
    if (correctedWords.empty()) {   // found none
        cout << "???";
    } else {
        while (!correctedWords.empty()) {
            cout << correctedWords.top() << "\n";
            correctedWords.pop();
        }
    }
}

int main() {
    HashTable* hashTable = new HashTable(109582, "dictionary.txt");
    cout << hashTable->size();      // For testing. TODO: erase this
    string userInput;

    while (userInput != ".") {
        // Prompt user to enter a word
        cout << "Please enter a word (type a single period '.' to terminate): ";
        cin >> userInput;           // save the word to userInput
        if (hashTable->contains(userInput)) {
            cout << '*';            // founded the word in hash table, it is acceptable
        }
        else {
            // the word is not found, correcting..
            correction(userInput, hashTable);
        }
    }
    
    // deallocate the hashTable
    delete hashTable;
    return 0;
}