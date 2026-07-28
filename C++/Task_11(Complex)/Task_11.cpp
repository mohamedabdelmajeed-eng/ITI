#include <iostream>
#include <cmath>

using namespace std;

class Complex
{
private:
    int real;
    int img;

public:

    // Default constructor
    Complex() : real(0), img(0)
    {
        cout << "Default constructor used" << endl;
    }

    // One parameter constructor
    Complex(int r) : real(r), img(r)
    {
        cout << "One parameter constructor used" << endl;
    }

    // Two parameter constructor
    Complex(int r, int i) : real(r), img(i)
    {
        cout << "Two parameter constructor used" << endl;
    }

    // Copy constructor
    Complex(const Complex& other)
    {
        real = other.real;
        img = other.img;

        cout << "Copy constructor used" << endl;
    }

    // Destructor
    ~Complex()
    {
        cout << "Destructor used" << endl;
    }

    // Setters
    void setReal(int r)
    {
        real = r;
    }

    void setImg(int i)
    {
        img = i;
    }

    // Getters
    int getReal()
    {
        return real;
    }

    int getImg()
    {
        return img;
    }

    // Print complex number
    void PrintComplex()
    {
        if (real == 0 && img == 0)
        {
            cout << 0;
        }
        else if (img == 0)
        {
            cout << real;
        }
        else if (real == 0)
        {
            cout << img << "i";
        }
        else
        {
            cout << real;

            if (img > 0)
            {
                cout << " + " << img << "i";
            }
            else
            {
                cout << " - " << -img << "i";
            }
        }
    }

    // Normal addition function
    Complex Add(Complex other)
    {
        Complex result;

        result.real = real + other.real;
        result.img = img + other.img;

        return result;
    }

    // Normal subtraction function
    Complex Sub(Complex other)
    {
        Complex result;

        result.real = real - other.real;
        result.img = img - other.img;

        return result;
    }

    // Addition operator
    Complex operator+(const Complex& other)
    {
        Complex temp;

        temp.real = real + other.real;
        temp.img = img + other.img;

        return temp;
    }

    // Subtraction operator
    Complex operator-(const Complex& other)
    {
        Complex temp;

        temp.real = real - other.real;
        temp.img = img - other.img;

        return temp;
    }

    // Multiplication operator
    Complex operator*(const Complex& other)
    {
        Complex temp;

        temp.real = real * other.real - img * other.img;
        temp.img = real * other.img + img * other.real;

        return temp;
    }

    // Division operator
    Complex operator/(const Complex& other)
    {
        Complex temp;

        int denominator =
            other.real * other.real +
            other.img * other.img;

        if (denominator == 0)
        {
            cout << "Cannot divide by zero" << endl;
            return temp;
        }

        temp.real =
            (real * other.real + img * other.img)
            / denominator;

        temp.img =
            (img * other.real - real * other.img)
            / denominator;

        return temp;
    }

    // += operator
    Complex operator+=(const Complex& other)
    {
        real = real + other.real;
        img = img + other.img;

        return *this;
    }

    // -= operator
    Complex operator-=(const Complex& other)
    {
        real = real - other.real;
        img = img - other.img;

        return *this;
    }

    // Prefix increment
    Complex operator++()
    {
        real++;
        img++;

        return *this;
    }

    // Postfix increment
    Complex operator++(int)
    {
        Complex old = *this;

        real++;
        img++;

        return old;
    }

    // Prefix decrement
    Complex operator--()
    {
        real--;
        img--;

        return *this;
    }

    // Postfix decrement
    Complex operator--(int)
    {
        Complex old = *this;

        real--;
        img--;

        return old;
    }

    // Equal operator
    bool operator==(const Complex& other)
    {
        return real == other.real && img == other.img;
    }

    // Not equal operator
    bool operator!=(const Complex& other)
    {
        return real != other.real || img != other.img;
    }

    // Greater than operator
    bool operator>(const Complex& other)
    {
        double firstMagnitude =
            sqrt(real * real + img * img);

        double secondMagnitude =
            sqrt(other.real * other.real +
                 other.img * other.img);

        return firstMagnitude > secondMagnitude;
    }

    // Less than operator
    bool operator<(const Complex& other)
    {
        double firstMagnitude =
            sqrt(real * real + img * img);

        double secondMagnitude =
            sqrt(other.real * other.real +
                 other.img * other.img);

        return firstMagnitude < secondMagnitude;
    }

    // Output stream operator
    friend ostream& operator<<(ostream& out, const Complex& number)
    {
        if (number.real == 0 && number.img == 0)
        {
            out << 0;
        }
        else if (number.img == 0)
        {
            out << number.real;
        }
        else if (number.real == 0)
        {
            out << number.img << "i";
        }
        else
        {
            out << number.real;

            if (number.img > 0)
            {
                out << " + " << number.img << "i";
            }
            else
            {
                out << " - " << -number.img << "i";
            }
        }

        return out;
    }

    // Input stream operator
    friend istream& operator>>(istream& in, Complex& number)
    {
        cout << "Enter real part: ";
        in >> number.real;

        cout << "Enter imaginary part: ";
        in >> number.img;

        return in;
    }

    // Type casting to double
    operator double()
    {
        double magnitude;

        magnitude = sqrt(real * real + img * img);

        return magnitude;
    }

    // Function call operator
    void operator()(int r, int i)
    {
        real = r;
        img = i;
    }
};

int main()
{
    Complex c1;
    Complex c2(5);
    Complex c3(3, 4);

    // Copy constructor
    Complex c4(c3);

    cout << "\nC1 = ";
    c1.PrintComplex();

    cout << "\nC2 = ";
    c2.PrintComplex();

    cout << "\nC3 = ";
    c3.PrintComplex();

    cout << "\nC4 = ";
    c4.PrintComplex();

    // Setters and getters
    c1.setReal(2);
    c1.setImg(3);

    cout << "\n\nAfter using setters:" << endl;
    cout << "C1 = " << c1 << endl;
    cout << "Real part = " << c1.getReal() << endl;
    cout << "Imaginary part = " << c1.getImg() << endl;

    // Math operators
    Complex sum = c2 + c3;
    Complex sub = c2 - c3;
    Complex multiply = c2 * c3;
    Complex divide = c2 / c3;

    cout << "\nMath operators:" << endl;
    cout << "C2 + C3 = " << sum << endl;
    cout << "C2 - C3 = " << sub << endl;
    cout << "C2 * C3 = " << multiply << endl;
    cout << "C2 / C3 = " << divide << endl;

    // += and -=
    Complex result = c2;

    result += c3;
    cout << "\nAfter result += C3: " << result << endl;

    result -= c3;
    cout << "After result -= C3: " << result << endl;

    // Increment
    cout << "\nIncrement operators:" << endl;
    cout << "C1 before increment = " << c1 << endl;
    cout << "++C1 = " << ++c1 << endl;
    cout << "C1++ = " << c1++ << endl;
    cout << "C1 after increment = " << c1 << endl;

    // Decrement
    cout << "\nDecrement operators:" << endl;
    cout << "--C1 = " << --c1 << endl;
    cout << "C1-- = " << c1-- << endl;
    cout << "C1 after decrement = " << c1 << endl;

    // Comparison operators
    cout << boolalpha;

    cout << "\nComparison operators:" << endl;
    cout << "C2 == C3: " << (c2 == c3) << endl;
    cout << "C2 != C3: " << (c2 != c3) << endl;
    cout << "C2 > C3: " << (c2 > c3) << endl;
    cout << "C2 < C3: " << (c2 < c3) << endl;

    // Type casting
    double value = c3;

    cout << "\nMagnitude of C3 = " << value << endl;

    // Function call operator
    c1(10, 7);

    cout << "\nAfter function call operator:" << endl;
    cout << "C1 = " << c1 << endl;

    // Input operator
    Complex userComplex;

    cout << "\nEnter a complex number:" << endl;
    cin >> userComplex;

    cout << "You entered: " << userComplex << endl;

    return 0;
}
