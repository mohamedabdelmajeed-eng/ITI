# Simple Calculator in C++

## Description
This is a simple calculator program written in C++. It allows the user to perform basic arithmetic operations on two integers.

## Features
- Addition (+)
- Subtraction (-)
- Multiplication (*)
- Division (/)
- Modulus (%)

## How It Works
1. Enter the first number.
2. Enter an operator (`+`, `-`, `*`, `/`, or `%`).
3. Enter the second number.
4. The program displays the result.

## Example

```text
Enter first number: 10
Enter operator (+ - * / %): *
Enter second number: 5
Result = 50
```

## Technologies Used
- C++
- Standard Input/Output (`iostream`)

## How to Run

1. Compile the program:
   ```bash
   g++ calculator.cpp -o calculator
   ```

2. Run the executable:
   ```bash
   ./calculator
   ```

## Notes
- The program works with integer values only.
- Division performs integer division.
- Entering an unsupported operator will display:
  ```
  Invalid operator!
  ```

## Author
Mohamed Elsiekh