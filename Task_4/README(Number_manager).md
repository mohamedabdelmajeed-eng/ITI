# Number Manager (Pointers in C++)

## Overview
This project is a simple C++ console application that demonstrates the use of **pointers** to modify and access variables through functions. The user can manage a single integer using a menu-driven interface.

---

## Objective
Practice using pointers in C++ by passing the address of a variable to functions instead of returning values or using global variables.

---

## Features
- Read an integer from the user.
- Increment the number.
- Decrement the number.
- Reset the number to zero.
- Display the current number.
- Menu-driven interface.
- Uses pointers in every function.

---

## Function Signatures

```cpp
void increment(int *num);
void decrement(int *num);
void reset(int *num);
void printNumber(int *num);
```

---

## How It Works

1. The program asks the user to enter an integer.
2. A menu is displayed with five options:
   - Increment
   - Decrement
   - Reset to 0
   - Show Number
   - Exit
3. The selected operation is performed using pointers.
4. The menu repeats until the user chooses to exit.

---

## Sample Output

```text
Enter number: 15

1. Increment
2. Decrement
3. Reset to 0
4. Show Number
5. Exit

Choice: 1
Current Number = 16

Choice: 2
Current Number = 15

Choice: 3
Current Number = 0

Choice: 4
Current Number = 0

Choice: 5
Program ended.
```

---

## Concepts Used

- C++
- Functions
- Pointers
- Pass by Address
- Switch Statement
- Loops (`do...while`)
- Console Input/Output

---

## Project Structure

```
Task_4/
└── Task_4_1 (Number Manager)/
    ├── Number_manager.cpp
    └── README.md
```

---

## Requirements

- C++ Compiler (g++, MSVC, MinGW, etc.)
- Visual Studio Code (recommended)

---

## How to Run

### Compile

```bash
g++ Number_manager.cpp -o Number_manager
```

### Run

```bash
./Number_manager
```

---

## Author

**Moham Abdelmajeed**

GitHub: https://github.com/mohamedabdelmajeed-eng

---

## License

This project was created for educational purposes as part of the ITI C++ training program.