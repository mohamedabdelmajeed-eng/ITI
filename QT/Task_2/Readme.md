<div align="center">

# 🚗 Car Store Application

<img src="images/logo.png" width="180"/>

### A Modern Qt Quick (QML) Desktop Application

Interactive Car Store UI built using **Qt 6**, **QML**, and **C++**

<br>

![Qt](https://img.shields.io/badge/Qt-6.11-41CD52?style=for-the-badge&logo=qt)
![QML](https://img.shields.io/badge/QML-Qt%20Quick-blue?style=for-the-badge)
![C++](https://img.shields.io/badge/C++-17-00599C?style=for-the-badge&logo=cplusplus)
![Platform](https://img.shields.io/badge/Platform-Windows%20%7C%20Linux-success?style=for-the-badge)
![License](https://img.shields.io/badge/License-MIT-orange?style=for-the-badge)

</div>

---

# 📑 Table of Contents

- 📌 Overview
- ✨ Features
- 🖼 Application Preview
- 🏗 Project Structure
- ⚙ Technologies Used
- 🧩 Project Components
- 🚀 Installation
- ▶ Running the Project
- 📚 Learning Objectives
- 🔮 Future Improvements
- 👨‍💻 Author

---

# 📌 Overview

The **Car Store Application** is a desktop application developed using **Qt 6**, **Qt Quick (QML)**, and **C++**.

It demonstrates how to build a modern graphical user interface using reusable QML components while following clean and organized project architecture.

The application starts with an animated **Splash Screen**, then automatically navigates to a **Home Screen** displaying multiple car products. Each product card is interactive and displays detailed information when clicked.

---

# ✨ Features

## 🚀 Splash Screen

- Beautiful application logo
- Welcome message
- Automatically disappears after **3 seconds**

---

## 🏠 Home Screen

Displays multiple car products in a modern card layout.

Each card includes:

- 🖼 Car Image
- 🚘 Car Name

---

## 🖱 Interactive Product Cards

Clicking a car image displays:

- 🎨 Color
- 🚗 Type
- 📅 Model

A **Hide Details** button returns to the product card.

---

## ♻ Reusable Components

The application uses reusable QML components.

Instead of writing the same code multiple times, one component (**CarCard.qml**) is reused for every product.

---

# 🖼 Application Preview

## Splash Screen

<p align="center">
<img src="screenshots/splash.png" width="800">
</p>

---

## Home Screen

<p align="center">
<img src="screenshots/home.png" width="800">
</p>

---

## Product Details

<p align="center">
<img src="screenshots/details.png" width="800">
</p>

---

# 🏗 Project Structure

```text
Task_2
│
├── images
│   ├── logo.png
│   ├── car1.jpg
│   ├── car2.jpg
│   └── car3.jpg
│
├── Main.qml
├── CarCard.qml
├── main.cpp
├── CMakeLists.txt
└── README.md
```

---

# ⚙ Technologies Used

| Technology | Purpose |
|------------|----------|
| Qt 6 | GUI Framework |
| Qt Quick | User Interface |
| QML | Frontend Design |
| C++17 | Application Logic |
| CMake | Build System |

---

# 🧩 Project Components

## 📄 main.cpp

Responsible for:

- Creating the application
- Loading the QML Engine
- Launching Main.qml

---

## 📄 Main.qml

Responsible for:

- Splash Screen
- Home Screen
- Timer
- Product Layout
- Creating Car Cards

---

## 📄 CarCard.qml

Reusable custom component that contains:

- Product Image
- Product Name
- Details Page
- Hide Details Button

---

# 🚀 Installation

## Clone Repository

```bash
git clone https://github.com/YourUserName/CarStore.git
```

---

## Open Project

Open the project using **Qt Creator**.

Open:

```
CMakeLists.txt
```

---

## Configure Project

Qt Creator configures CMake automatically.

---

## Build

```
Ctrl + B
```

---

## Run

```
Ctrl + R
```

---

# 📂 Resources

The application uses Qt Resources for loading images.

```
images/logo.png
images/car1.jpg
images/car2.jpg
images/car3.jpg
```

---

# 📚 Learning Objectives

This project demonstrates:

✅ Qt Quick

✅ QML Basics

✅ Reusable Components

✅ MouseArea

✅ Property Binding

✅ Anchors

✅ Layouts

✅ Images

✅ Timers

✅ Resource System

---

# 🔮 Future Improvements

- 🔍 Search Cars
- ❤️ Favorite Cars
- 🛒 Shopping Cart
- 🌙 Dark Mode
- 💰 Car Prices
- 🗂 Categories
- 📱 Responsive Design
- 💾 Database Integration
- ✨ Smooth Animations

---

# 📊 Project Statistics

| Category | Value |
|----------|-------|
| Language | C++17 |
| Framework | Qt 6 |
| UI | QML |
| Build System | CMake |
| Components | Reusable |
| Platform | Linux / Windows |

---

# 👨‍💻 Author

<div align="center">

## Mohamed Abdelmajeed

**Mechatronics Engineering Student**

Interested in

Embedded Systems • Qt/QML • C++ • Robotics • Software Development

### Connect with me

[![LinkedIn](https://img.shields.io/badge/LinkedIn-Profile-blue?style=for-the-badge&logo=linkedin)](https://www.linkedin.com/)

</div>

---

<div align="center">

## ⭐ If you like this project

Please consider giving this repository a ⭐

It motivates me to build more open-source projects.

Made with ❤️ using Qt & QML

</div>