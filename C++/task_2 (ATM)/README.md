# ATM Simulation (C++)

## Overview
This project is a simple ATM (Automated Teller Machine) simulation written in C++. It is a console-based application that allows users to perform basic banking operations such as checking their balance, depositing money, withdrawing money, and exiting the program.

The project is designed for beginners who are learning C++ programming concepts such as variables, loops, conditional statements, and switch-case menus.

---

## Features
- Check current account balance.
- Deposit money into the account.
- Withdraw money from the account.
- Prevent withdrawals that exceed the available balance.
- Validate deposit and withdrawal amounts.
- User-friendly menu interface.
- Exit the application safely.

---

## Technologies Used
- **Language:** C++
- **Compiler:** g++, MinGW, Visual Studio, or any C++ compiler
- **IDE (Optional):** Visual Studio Code, Code::Blocks, Dev-C++, Visual Studio

---

## Menu
```
===== ATM MENU =====
1. Check Balance
2. Deposit
3. Withdraw
4. Exit
```

---

## How It Works
1. The program starts with an initial account balance.
2. A menu is displayed for the user.
3. The user selects one of the available options.
4. The balance is updated after deposits or withdrawals.
5. The menu continues to appear until the user chooses **Exit**.

---

## Project Structure
```
ATM-Simulation/
│
├── main.cpp      # Main source code
└── README.md     # Project documentation
```

---

## How to Compile

Using **g++**:

```bash
g++ main.cpp -o atm
```

Run the program:

### Windows
```bash
atm.exe
```

### Linux / macOS
```bash
./atm
```

---

## Example Output
```
===== ATM MENU =====
1. Check Balance
2. Deposit
3. Withdraw
4. Exit

Enter your choice: 2
Enter amount to deposit: $500

Deposit successful!
New balance: $1500
```

---

## Learning Objectives
This project demonstrates:
- Variables and data types
- User input and output
- Loops (`do-while`)
- Conditional statements (`if-else`)
- `switch` statements
- Basic program design
- Input validation

---

## Future Improvements
- PIN authentication
- Multiple user accounts
- Transaction history
- File handling to save account data
- Transfer money between accounts
- Change PIN feature
- Interest calculation
- Better error handling

---

## Author
Created as a beginner C++ project for learning basic programming concepts.

---

## License
This project is open source and available for educational purposes.