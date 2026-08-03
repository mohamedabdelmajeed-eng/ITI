#include <iostream>
#include <string>

using namespace std;

int main()
{
    string str;

    cout << "Enter a string: ";
    cin >> str;

    // Bubble Sort
    for (int i = 0; i < str.length() - 1; i++)
    {
        for (int j = 0; j < str.length() - i - 1; j++)
        {
            if (str[j] > str[j + 1])
            {
                char temp = str[j];
                str[j] = str[j + 1];
                str[j + 1] = temp;
            }
        }
    }

    cout << "Sorted string: " << str << endl;

    return 0;
}