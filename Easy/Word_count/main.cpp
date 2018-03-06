// Vo Huy
// Warmup - word - count
// 4/11/2017
// sources from Prof.O
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

int main()
{
    string fileName;
    string lineFromFile;
    string word;
    int lineCount = 0;
    int wordCount = 0;
    int charCount = 0;

    ifstream fileStream;
    cout << "Enter the file's name you want to open: " << endl;
    getline(cin, fileName);
    fileStream.open(fileName);
    if (!fileStream)
    {
        cerr << "I couldn't open that file: \"" << fileName << "\"" << endl;
        return -1;
    }

    while (getline(fileStream, lineFromFile))
    {
        std::stringstream ss(lineFromFile);
        while(ss >> word) {
            wordCount++;
        }
        charCount += lineFromFile.length() + 2;
        lineCount++;
    }

    cout << lineCount << endl;
    cout << wordCount << endl;
    cout << charCount << endl;
    return 0;
}
