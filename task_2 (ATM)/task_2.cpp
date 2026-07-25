#include <iostream>
using namespace std;

int main() {
    double balance = 1000.0; 
    int choice;
    double amount;

    do {
        cout << "\n===== ATM MENU =====" << endl;
        cout << "1. Check Balance" << endl;
        cout << "2. Deposit" << endl;
        cout << "3. Withdraw" << endl;
        cout << "4. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Your current balance is: $" << balance << endl;
                break;

            case 2:
                cout << "Enter amount to deposit: $";
                cin >> amount;

                if (amount > 0) {
                    balance += amount;
                    cout << "Deposit successful!" << endl;
                    cout << "New balance: $" << balance << endl;
                } else {
                    cout << "Invalid amount!" << endl;
                }
                break;

            case 3:
                cout << "Enter amount to withdraw: $";
                cin >> amount;

                if (amount <= 0) {
                    cout << "Invalid amount!" << endl;
                } else if (amount > balance) {
                    cout << "Insufficient balance!" << endl;
                } else {
                    balance -= amount;
                    cout << "Withdrawal successful!" << endl;
                    cout << "Remaining balance: $" << balance << endl;
                }
                break;

            case 4:
                cout << "Thank you for using the ATM!" << endl;
                break;

            default:
                cout << "Invalid choice! Please try again." << endl;
        }

    } while (choice != 4);

    return 0;
}