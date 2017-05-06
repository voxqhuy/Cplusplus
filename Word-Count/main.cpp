#include <iostream>
#include <fstream>
#include <string>

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
    cin >> fileName;
    fileStream.open(fileName);
    if (!fileStream)
    {
        cerr << "I couldn't open that file: \"" << fileName << "\"" << endl;
        return -1;
    }

    while (getline(fileStream, lineFromFile))
    {
//        stringstream ss(lineFromFile);
//        while( ss >> word ) {
//            charCount += word.length();
//            wordCount++;
//        }
        lineCount++;
    }

    cout << lineCount << endl;
    return 0;
}
