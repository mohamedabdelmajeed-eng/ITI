#include <iostream>
#include <string>
using namespace std;

int main() {
    string name, position;
    int id;
    double workingHours, hourlyRate;
    double grossSalary, bonus, tax, netSalary;

    // Input
    cout << "========== Salary System ==========\n";

    cout << "Enter Employee Name: ";
    getline(cin, name);

    cout << "Enter Employee ID: ";
    cin >> id;

    cout << "Enter Working Hours: ";
    cin >> workingHours;

    cout << "Enter Hourly Rate: ";
    cin >> hourlyRate;

    cin.ignore();

    cout << "Enter Position (Manager/Employee): ";
    getline(cin, position);

    // Calculate Gross Salary
    grossSalary = workingHours * hourlyRate;

    // Calculate Bonus
    if (position == "Manager" || position == "manager") {
        bonus = grossSalary * 0.20;
    } else {
        bonus = grossSalary * 0.10;
    }

    // Calculate Tax
    tax = (grossSalary + bonus) * 0.15;

    // Calculate Net Salary
    netSalary = grossSalary + bonus - tax;

    // Display Salary Report
    cout << "\n========== Salary Report ==========\n";
    cout << "Name         : " << name << endl;
    cout << "Employee ID  : " << id << endl;
    cout << "Position     : " << position << endl;
    cout << "Working Hours: " << workingHours << endl;
    cout << "Hourly Rate  : $" << hourlyRate << endl;
    cout << "-----------------------------------" << endl;
    cout << "Gross Salary : $" << grossSalary << endl;
    cout << "Bonus        : $" << bonus << endl;
    cout << "Tax          : $" << tax << endl;
    cout << "Net Salary   : $" << netSalary << endl;
    cout << "===================================" << endl;

    return 0;
}