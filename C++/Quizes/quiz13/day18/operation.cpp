#include <iostream>
using namespace std;

// Addition without using +
int add(int a, int b)
{
    while (b > 0)
    {
        a++;
        b--;
    }

    while (b < 0)
    {
        a--;
        b++;
    }

    return a;
}

// Subtraction without using -
int subtract(int a, int b)
{
    while (b > 0)
    {
        a--;
        b--;
    }

    while (b < 0)
    {
        a++;
        b++;
    }

    return a;
}

// Multiplication without using *
int multiply(int a, int b)
{
    int result = 0;
    bool negative = false;

    // Make a positive if it is negative
    if (a < 0)
    {
        a = subtract(0, a);
        negative = !negative;
    }

    // Make b positive if it is negative
    if (b < 0)
    {
        b = subtract(0, b);
        negative = !negative;
    }

    while (b > 0)
    {
        result = add(result, a);
        b--;
    }

    if (negative)
    {
        result = subtract(0, result);
    }

    return result;
}

int main()
{
    int firstNumber;
    int secondNumber;

    cout << "Enter first number: ";
    cin >> firstNumber;

    cout << "Enter second number: ";
    cin >> secondNumber;

    cout << "\nAddition = "
         << add(firstNumber, secondNumber) << endl;

    cout << "Subtraction = "
         << subtract(firstNumber, secondNumber) << endl;

    cout << "Multiplication = "
         << multiply(firstNumber, secondNumber) << endl;

    return 0;
}