#define DOCTEST_CONFIG_IMPLEMENT
#include "doctest.h"
#include <iostream>
#include <string>

using namespace std;

int main()
{
    int result = (new doctest::Context())->run();
    return result;
}

bool isPangram(string words) {
    vector<int> letterFrequency(26, 0);
    for (int wordIndex = 0; wordIndex < words.length(); wordIndex++)
    {
        char letter = tolower(words.at(wordIndex));
        if (isalpha(letter))
        {
            int letterIndex = letter - 'a';
            letterFrequency.at(letterIndex)++;
        }
    }
    for (int i = 0; i < letterFrequency.size(); i++)
    {
        if (letterFrequency.at(i) == 0) return false;
    }
    return true;
}

TEST_CASE("isPangram")
{
    CHECK(isPangram("abcdefghijklmnopqrstuvwxyz") == true);
    CHECK(isPangram("Pack my box with five dozen liquor jugs") == true);
    CHECK(isPangram("Jackdaws love my big sphinx of quartz.") == true);
    CHECK(isPangram("Sphinx of black quartz, judge my vow.") == true);
    CHECK(isPangram("RETURN FALSE") == false);
    CHECK(isPangram("jlj sf^%$@@%&#@$fwei WEjofiwe") == false);
    CHECK(isPangram("Thi is not Pangam") == false);
    CHECK(isPangram("") == false);
}
