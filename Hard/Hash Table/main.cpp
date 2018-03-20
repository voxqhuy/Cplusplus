//  Name: Vo Huy
//  Assignment number: 5
//  Assignment: Spell Checking with the Hash Table Data Structure
//  File name: huy.cpp
//  Date last modified: March 27, 2018
//  Honor statement: I have neither given nor received any unauthorized help on this assignment. 

#include <iostream>     // std::cout, std::fixed
#include <vector>       // std::vector
#include <string>
using namespace std;

class HashTable {
private:
    int mTableSize;
    string mFileName;
public:
    // Constructor
    HashTable (int tableSize, string fileName): mTableSize(tableSize), mFileName(fileName) {}

    // hash function maps a string to an index within the table
    void hash() {

    }

    // insert method inserts a string into the hash table
    // return true if it successfully inserts the word into the table
    // otherwise, it should return false if the word already is present in the table
    bool insert() {
        return false;
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

// checking for an omission
void checkOmission(HashTable& hashtable) {      // this function is changing hashtable

}

// checking for an extra letter
checkExtra(HashTable& hashtable) {

}

// checking for a typo
checkTypo(HashTable& hashtable) {

}

// checking for a transposition
checkTransposition(HashTable& hashtable) {

}

// checking for a missing space
checkMissingSpace(HashTable& hashtable) {

}

void correction(HashTable hashTable) {
    // Make an empty priority queue
    priority_queue<string> correctedWords;
    // check if the user omitted a letter
    checkOmission(correctedWords);
    // check if the user added an extraneous letter
    checkExtra(correctedWords);
    // check if the user mistyped a letter
    checkTypo(correctedWords);
    // check if the user tranposed 2 adjacent letter
    checkTransposition(correctedWords);
    // check if the user forgot to add a space
    checkMissingSpace(correctedWords);

    // print out corrected words in alphabetic order, if there's none, print ???
    if (correctedWords.empty()) {
        cout << "???";
    } else {
        while (!correctedWords.empty()) {
            cout << correctedWords.top();
            correctedWords.pop();
        }
    }
}

int main() {
    HashTable* hashTable = new HashTable(109582, "dictionary.txt");
    cout << hashTable->size();
    string userInput;

    while (userInput != ".") {
        // Prompt user to enter a word
        cout << "Please enter a word (type a single period '.' to terminate): ";
        cin >> userInput;       // save the word to userInput
        if (hashTable.contains(userInput)) {
            cout << '*';        // founded the word in hash table, it is acceptable
        }
        else {
            // the word is not found, correcting..
            correction(hashTable);
        }
    }
    
    // deallocate the hashTable
    delete hashTable;
    return 0;
}