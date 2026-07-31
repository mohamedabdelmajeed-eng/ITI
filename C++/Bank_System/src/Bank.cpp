// Bank.cpp this file contains the implementation of the Bank class, which manages bank accounts and transactions. It includes methods for creating accounts, depositing and withdrawing money, transferring funds between accounts, displaying account information, and saving/loading account data to/from a file.
#include "Bank.h"
#include "CheckingAccount.h"
#include "SavingsAccount.h"

#include <algorithm>// for using find_if algorithm to search for an account in the vector of accounts
#include <ctime>
#include <fstream> 
#include <iomanip> 
#include <iostream>
#include <sstream>// for dividing the line read from the file into separate components (type, accountId, ownerName, balance)
#include <stdexcept>

using namespace std;

// Search for an account using its ID
shared_ptr<Account> Bank::findAccount(
    const string& accountId
) const
{
    auto result = find_if(
        accounts.begin(),
        accounts.end(),
        [&accountId](const shared_ptr<Account>& account)// lambda function to compare account IDs
        {
            return account->getAccountId() == accountId;
        }
    );

    if (result == accounts.end())
    {
        return nullptr;
    }

    return *result; // return the found account or nullptr if not found
}

// Create a new account
void Bank::createAccount(
    const string& type,
    const string& accountId,
    const string& ownerName,
    double initialBalance
)
{  
    if (findAccount(accountId) != nullptr)
    {
        throw runtime_error(
            "An account with this ID already exists."
        );
    }

    if (type == "Savings")
    {  
        accounts.push_back(
            make_shared<SavingsAccount>(
                accountId,
                ownerName,
                initialBalance
            )
        );
    }
    else if (type == "Checking")
    {
        accounts.push_back(
            make_shared<CheckingAccount>(
                accountId,
                ownerName,
                initialBalance
            )
        );
    }
    else
    {
        throw invalid_argument(
            "Invalid account type."
        );
    }
// Log the account creation transaction
    logTransaction(
        accountId,
        "Create Account",
        initialBalance,
        "New account created"
    );

    saveAccounts();
}

// Deposit money into an account
void Bank::deposit(
    const string& accountId,
    double amount
)
{
    shared_ptr<Account> account =
        findAccount(accountId);

    if (account == nullptr)
    {
        throw runtime_error(
            "Account not found."
        );
    }

    account->deposit(amount);

    logTransaction(
        accountId,
        "Deposit",
        amount,
        "Money deposited"
    );

    saveAccounts();// Save the updated account information to the file
}

// Withdraw money from an account
void Bank::withdraw(
    const string& accountId,
    double amount
)
{
    shared_ptr<Account> account =
        findAccount(accountId);

    if (account == nullptr)
    {
        throw runtime_error(
            "Account not found."
        );
    }

    account->withdraw(amount);

    logTransaction(
        accountId,
        "Withdraw",
        amount,
        "Money withdrawn"
    );

    saveAccounts();
}

// Transfer money between two accounts
void Bank::transfer(
    const string& sourceId,
    const string& destinationId,
    double amount
)
{
    if (sourceId == destinationId)
    {
        throw invalid_argument(
            "Cannot transfer to the same account."
        );
    }

    shared_ptr<Account> sourceAccount =
        findAccount(sourceId);

    shared_ptr<Account> destinationAccount =
        findAccount(destinationId);

    if (sourceAccount == nullptr)
    {
        throw runtime_error(
            "Source account not found."
        );
    }

    if (destinationAccount == nullptr)
    {
        throw runtime_error(
            "Destination account not found."
        );
    }

    sourceAccount->withdraw(amount);

    destinationAccount->deposit(amount);

    logTransaction(
        sourceId,
        destinationId,
        amount,
        "Money transferred"
    );

    saveAccounts();
}

// Display all accounts
void Bank::displayAccounts() const
{
    if (accounts.empty())
    {
        cout << "\nNo accounts available.\n";
        return;
    }

    cout << "\n========== Accounts ==========\n";
  // Loop through each account in the accounts vector and call the display method to show account details
    for (const shared_ptr<Account>& account : accounts)
    {
        account->display();

        cout << "------------------------------\n";
    }
}

// Save all accounts to accounts.txt
void Bank::saveAccounts() const
{
    ofstream file("accounts.txt"); // ofstream is used to create and write to a file named "accounts.txt"

    if (!file)
    {
        throw runtime_error(
            "Could not open accounts.txt for saving."
        );
    }

    for (const shared_ptr<Account>& account : accounts)
    {
        file
            << account->getAccountType() << '|'
            << account->getAccountId() << '|'
            << account->getOwnerName() << '|'
            << account->getBalance()
            << '\n';
    }
}

// Load accounts from accounts.txt
void Bank::loadAccounts()
{ 
    ifstream file("accounts.txt");  // ifstream is used to read from a file named "accounts.txt"

    if (!file)
    {
        return;
    }

    accounts.clear();

    string line;

    while (getline(file, line))
    {
        if (line.empty())
        {
            continue;
        }

        stringstream stream(line);

        string type;
        string accountId;
        string ownerName;
        string balanceText;

        getline(stream, type, '|');
        getline(stream, accountId, '|');
        getline(stream, ownerName, '|');
        getline(stream, balanceText);

        try // used to transfer the balanceText string to a double value, which represents the account balance. If the conversion fails (e.g., if the string is not a valid number), it will throw an exception that is caught in the catch block.
        {
            double loadedBalance =
                stod(balanceText);  // stod string to double function to convert the balanceText string to a double value, which represents the account balance.

            if (type == "Savings")
            {
                accounts.push_back(
                    make_shared<SavingsAccount>(
                        accountId,
                        ownerName,
                        loadedBalance
                    )
                );
            }
            else if (type == "Checking")
            {
                accounts.push_back(
                    make_shared<CheckingAccount>(
                        accountId,
                        ownerName,
                        loadedBalance
                    )
                );
            }
            else
            {
                cerr // cerr is used to print error messages to the standard error stream, which is typically displayed in the console or terminal. In this case, it is used to inform the user that an unknown account type was encountered while loading accounts from the file.
                    << "Warning: Unknown account type skipped.\n";
            }
        }
        catch (const exception&)
        {
            cerr
                << "Warning: Invalid account data skipped.\n";
        }
    }
}

// Save transaction information to transactions.txt
void Bank::logTransaction(
    const string& source,
    const string& destination,
    double amount,
    const string& description
) const
{
    ofstream file(
        "transactions.txt",
        ios::app // ios::app is used to open the file in append mode
    );

    if (!file)
    {
        throw runtime_error(
            "Could not open transaction log."
        );
    }

    time_t currentTime =
        time(nullptr); // time(nullptr) is used to get the current time as a time_t value

    tm localTime{};

#ifdef _WIN32  // _WIN32 is a preprocessor directive that checks for  Windows platform
    localtime_s(
        &localTime,
        &currentTime
    );
#else
    localtime_r(
        &currentTime,
        &localTime
    );
#endif 

    file
        << put_time( 
            &localTime,
            "%Y-%m-%d %H:%M:%S"
        )
        << " | Source: "
        << source
        << " | Destination/Operation: "
        << destination
        << " | Amount: "
        << amount
        << " | Description: "
        << description
        << '\n';
}