#include <iostream>
using namespace std;

// Function prototypes
void increment(int *num);
void decrement(int *num);
void reset(int *num);
void printNumber(int *num);

int main()
{
    int number;
    int choice;

    cout << "Enter number: ";
    cin >> number;

    do
    {
        cout << "\n1. Increment" << endl;
        cout << "2. Decrement" << endl;
        cout << "3. Reset to 0" << endl;
        cout << "4. Show Number" << endl;
        cout << "5. Exit" << endl;
        cout << "Choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            increment(&number);
            break;

        case 2:
            decrement(&number);
            break;

        case 3:
            reset(&number);
            break;

        case 4:
            printNumber(&number);
            break;

        case 5:
            cout << "Program ended." << endl;
            break;

        default:
            cout << "Invalid choice." << endl;
        }

    } while (choice != 5);

    return 0;
}

void increment(int *num)
{
    (*num)++;
    cout << "Current Number = " << *num << endl;
}

void decrement(int *num)
{
    (*num)--;
    cout << "Current Number = " << *num << endl;
}

void reset(int *num)
{
    *num = 0;
    cout << "Current Number = " << *num << endl;
}

void printNumber(int *num)
{
    cout << "Current Number = " << *num << endl;
}