# Employee Salary Management System (C++)

## Overview
The **Employee Salary Management System** is a simple console-based application developed in **C++**. The program allows users to enter employee information, calculates the employee's salary based on working hours and hourly rate, applies a bonus depending on the employee's position, deducts tax, and displays a detailed salary report.

This project is designed for beginners who are learning C++ programming concepts such as user input, variables, conditional statements, arithmetic operations, and formatted output.

---

## Features
- Read employee information from the user.
- Calculate the gross salary.
- Calculate bonus based on employee position.
- Calculate tax deduction.
- Calculate the net salary.
- Display a detailed salary report.

---

## Employee Information
The program reads the following information:

- Employee Name
- Employee ID
- Working Hours
- Hourly Rate
- Position (Manager or Employee)

---

## Salary Calculation

### Gross Salary
```
Gross Salary = Working Hours × Hourly Rate
```

### Bonus
- **Manager:** 20% of Gross Salary
- **Employee:** 10% of Gross Salary

### Tax
```
Tax = 15% × (Gross Salary + Bonus)
```

### Net Salary
```
Net Salary = Gross Salary + Bonus − Tax
```

---

## Technologies Used
- **Programming Language:** C++
- **Compiler:** g++, MinGW, Visual Studio, or any C++ compiler
- **IDE (Optional):**
  - Visual Studio Code
  - Code::Blocks
  - Dev-C++
  - Visual Studio

---

## Project Structure
```
Salary-System/
│
├── main.cpp
└── README.md
```

---

## How to Compile

Using **g++**:

```bash
g++ main.cpp -o salary
```

Run the program:

### Windows
```bash
salary.exe
```

### Linux / macOS
```bash
./salary
```

---

## Example

### Input
```
Employee Name : Ahmed Ali
Employee ID   : 1001
Working Hours : 160
Hourly Rate   : 25
Position      : Manager
```

### Output
```
========== Salary Report ==========
Name         : Ahmed Ali
Employee ID  : 1001
Position     : Manager
Working Hours: 160
Hourly Rate  : $25

Gross Salary : $4000
Bonus        : $800
Tax          : $720
Net Salary   : $4080
```

---

## Learning Objectives
This project helps students practice:

- Variables and data types
- User input and output
- String handling
- Arithmetic calculations
- Conditional statements (`if-else`)
- Program organization
- Console application development

---

## Future Improvements
Possible enhancements include:

- Menu-driven interface
- Support for multiple employees
- Overtime pay calculation
- Different tax rates
- Save employee records to a file
- Search employee by ID
- Update employee information
- Delete employee records
- Monthly salary reports
- Employee database integration

---

## Requirements
- C++11 or later
- Any standard C++ compiler

---

## Author
Created as a beginner C++ project for learning salary calculations and basic programming concepts.

---

## License
This project is open source and available for educational purposes.