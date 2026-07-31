#include "Bank.h"

#include <iostream>
#include <limits>  //for invalid input entered
#include <stdexcept>
#include <string>

using namespace std;
// Function to clear the input buffer and reset the input state
void clearInvalidInput()
{
    cin.clear();

    cin.ignore(
        numeric_limits<streamsize>::max(), // ignore all characters in the input buffer up to the maximum stream size
        '\n'
    );
}

int main()
{
    Bank bank;
// Load existing accounts from the file, if available
    try
    {
        bank.loadAccounts();
    }
    catch (const exception& error)
    {
        cout
            << "Loading error: "
            << error.what()
            << '\n';
    }

    int choice = 0;

    do
    { // Display the main menu and prompt the user for their choice
        cout << "\n========== Bank System ==========\n";
        cout << "1. Create Account\n";
        cout << "2. Deposit Money\n";
        cout << "3. Withdraw Money\n";
        cout << "4. Transfer Money\n";
        cout << "5. Display Accounts\n";
        cout << "6. Exit\n";
        cout << "Enter your choice: ";

        if (!(cin >> choice))
        {
            cout << "Please enter a valid number.\n";

            clearInvalidInput();

            continue;
        }

        try
        {  // Handle user choices and perform corresponding actions
            if (choice == 1)
            {
                int typeChoice;

                string type;
                string accountId;
                string ownerName;

                double initialBalance;

                cout << "\n1. Savings Account\n";
                cout << "2. Checking Account\n";
                cout << "Choose account type: ";

                if (!(cin >> typeChoice))
                {
                    clearInvalidInput();

                    throw invalid_argument(
                        "Account type must be a number."
                    );
                }

                if (typeChoice == 1)
                {
                    type = "Savings";
                }
                else if (typeChoice == 2)
                {
                    type = "Checking";
                }
                else
                {
                    throw invalid_argument(
                        "Invalid account type."
                    );
                }

                cout << "Enter account ID: ";
                cin >> accountId;

                cin.ignore( // to ignore entered invalid input and clear the input buffer before reading the owner name
                    numeric_limits<streamsize>::max(),
                    '\n'
                );

                cout << "Enter owner name: ";
                getline(cin, ownerName);

                cout << "Enter initial balance: ";

                if (!(cin >> initialBalance))
                {
                    clearInvalidInput();

                    throw invalid_argument(
                        "Balance must be a number."
                    );
                }

                bank.createAccount(
                    type,
                    accountId,
                    ownerName,
                    initialBalance
                );

                cout
                    << "Account created successfully.\n";
            }
            else if (choice == 2)
            {
                string accountId;

                double amount;

                cout << "Enter account ID: ";
                cin >> accountId;

                cout << "Enter deposit amount: ";

                if (!(cin >> amount))
                {
                    clearInvalidInput();

                    throw invalid_argument(
                        "Amount must be a number."
                    );
                }

                bank.deposit(
                    accountId,
                    amount
                );

                cout
                    << "Money deposited successfully.\n";
            }
            else if (choice == 3)
            {
                string accountId;

                double amount;

                cout << "Enter account ID: ";
                cin >> accountId;

                cout << "Enter withdrawal amount: ";

                if (!(cin >> amount))
                {
                    clearInvalidInput();

                    throw invalid_argument(
                        "Amount must be a number."
                    );
                }

                bank.withdraw(
                    accountId,
                    amount
                );

                cout
                    << "Money withdrawn successfully.\n";
            }
            else if (choice == 4)
            {
                string sourceId;
                string destinationId;

                double amount;

                cout << "Enter source account ID: ";
                cin >> sourceId;

                cout << "Enter destination account ID: ";
                cin >> destinationId;

                cout << "Enter transfer amount: ";

                if (!(cin >> amount))
                {
                    clearInvalidInput();

                    throw invalid_argument(
                        "Amount must be a number."
                    );
                }

                bank.transfer(
                    sourceId,
                    destinationId,
                    amount
                );

                cout
                    << "Money transferred successfully.\n";
            }
            else if (choice == 5)
            {
                bank.displayAccounts();
            }
            else if (choice == 6)
            {
                bank.saveAccounts();

                cout
                    << "Data saved successfully.\n";

                cout
                    << "Goodbye!\n";
            }
            else
            {
                cout
                    << "Please choose a number from 1 to 6.\n";
            }
        }
        catch (const exception& error)
        {
            cout
                << "Error: "
                << error.what()
                << '\n';
        }
    }
    while (choice != 6);

    return 0;
}