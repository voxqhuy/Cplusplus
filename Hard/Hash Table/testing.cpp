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
#include <stdexcept>      // std::out_of_range
using namespace std;

// // checking for an omission
// void checkOmission(string userInput) {  
//     // Try adding a single letter at all possible places in the word
//     // If any match a word in the hash table, push into the queue for printing later
//     for (size_t i = 0; i <= userInput.length(); i++) {
//         for (char j = 'a'; j <= 'z'; j++) {
//             string testingWord = userInput.insert(i, string(1, j));        // FIXME: j doesn't work, has to convert j to string??
//             if (hashTable->contains(testingWord)) {
//                 correctedWords.push(testingWord);
//             }
//         }
//     }
// }

// // checking for an extra letter
// void checkExtra(string userInput) {
//     // Try removing a single letter from the word
//     // If any match a word in the hash table, push into the queue for printing later
//     // StringBuilder testingWord = new StringBuilder(userInput);
//     cout << userInput;
//     string testingWord = userInput.erase(1, 1);
//     cout << userInput << testingWord;
// }

// Ordering a to z

int main () {
  vector<vector<string>> a(10);
  if (a[0].empty())
    cout << "ga";
  return 0;
}