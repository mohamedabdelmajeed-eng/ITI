#include <iostream>
#include <vector>
#include <string>
using namespace std;

int main()
{
    string sentence, word;
    vector<string> words;

    cout << "Enter a sentence: ";
    getline(cin, sentence);

    for (int i = 0; i < sentence.length(); i++)
    {
        if (sentence[i] != ' ')
        {
            word += sentence[i];
        }
        else
        {
            if (!word.empty())
            {
                words.push_back(word);
                word = "";
            }
        }
    }


    if (!word.empty())
    {
        words.push_back(word);
    }

    cout << "Number of words = " << words.size() << endl;

    return 0;
}