# 🎓 Student Management System

![C++](https://img.shields.io/badge/C%2B%2B-17-blue.svg)
![OOP](https://img.shields.io/badge/Object--Oriented-Programming-success)
![Status](https://img.shields.io/badge/Status-Completed-brightgreen)
![License](https://img.shields.io/badge/License-MIT-yellow)

A simple **Object-Oriented Programming (OOP)** project written in **C++** that demonstrates the use of **classes**, **encapsulation**, **getters**, and **setters** to manage student information.

---

# 📖 Overview

This project implements a `Student` class that stores a student's:

- Name
- Age
- Student ID
- Average Grade
- Letter Grade

The program creates a student object, assigns values using setter functions, and displays the information in a formatted report.

---

# ✨ Features

✔ Object-Oriented Design

✔ Private Data Members

✔ Public Getters & Setters

✔ Encapsulation

✔ Clean Console Output

✔ Easy to Extend

---

# 📂 Project Structure

```
Student-Management-System/
│
├── main.cpp
└── README.md
```

---

# 🏗 Class Diagram

```text
                +----------------------+
                |       Student        |
                +----------------------+
                | - name               |
                | - age                |
                | - studentID          |
                | - gradesAvg          |
                | - grade              |
                +----------------------+
                | + setName()          |
                | + setAge()           |
                | + setStudentID()     |
                | + setAverage()       |
                | + setGrade()         |
                |                      |
                | + getName()          |
                | + getAge()           |
                | + getID()            |
                | + getAverage()       |
                | + getGrade()         |
                |                      |
                | + printInfo()        |
                +----------------------+
```

---

# 🔄 Program Flow

```text
        Start
          │
          ▼
 Create Student Object
          │
          ▼
  Set Student Information
          │
          ▼
 Store Data Inside Object
          │
          ▼
 Display Student Information
          │
          ▼
         End
```

---

# ⚙ Technologies Used

- C++
- Object-Oriented Programming (OOP)
- Standard Library
- Visual Studio Code / Code::Blocks / Visual Studio

---

# 💻 Example Output

```text
Let's set student data

====== Student Info ======
Name       : Mohamed
Age        : 20
Student ID : 253335
Average    : 97%
Grade      : A+
==========================
```

---

# 🚀 How to Compile

### Using g++

```bash
g++ main.cpp -o StudentManagement
```

Run:

### Windows

```bash
StudentManagement.exe
```

### Linux / macOS

```bash
./StudentManagement
```

---

# 📚 OOP Concepts Demonstrated

| Concept | Used |
|---------|:----:|
| Class | ✅ |
| Object | ✅ |
| Encapsulation | ✅ |
| Private Members | ✅ |
| Public Methods | ✅ |
| Getters | ✅ |
| Setters | ✅ |

---

# 📈 Project Workflow

```text
Input
  │
  ▼
Setter Functions
  │
  ▼
Private Variables
  │
  ▼
Getter / printInfo()
  │
  ▼
Console Output
```

---

# 🔮 Future Improvements

- Read data from the keyboard
- Store multiple students
- Calculate averages automatically
- Save data to files
- Search by Student ID
- Delete student records
- Update student information

---

# 👩‍💻 Author

**Ella Matthew**

Computer Science Student

---

## ⭐ If you found this project useful, consider giving it a star!