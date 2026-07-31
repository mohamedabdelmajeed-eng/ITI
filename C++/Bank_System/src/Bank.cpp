#include "Bank.h"
#include "CheckingAccount.h"
#include "SavingsAccount.h"

#include <algorithm>
#include <ctime>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <stdexcept>

using namespace std;

// File paths
const string ACCOUNTS_FILE =
    "data/accounts.txt";

const string TRANSACTIONS_FILE =
    "data/transactions.txt";


// Search for an account using its ID
shared_ptr<Account> Bank::findAccount(
    const string& accountId
) const
{
    auto result = find_if(
        accounts.begin(),
        accounts.end(),

        [&accountId](
            const shared_ptr<Account>& account
        )
        {
            return account->getAccountId() == accountId;
        }
    );

    if (result == accounts.end())
    {
        return nullptr;
    }

    return *result;
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

    logTransaction(
        accountId,
        "Create Account",
        initialBalance,
        "New account created"
    );

    saveAccounts();
}


// Deposit money
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

    saveAccounts();
}


// Withdraw money
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

    for (
        const shared_ptr<Account>& account :
        accounts
    )
    {
        account->display();

        cout
            << "------------------------------\n";
    }
}


// Save accounts to data/accounts.txt
void Bank::saveAccounts() const
{
    ofstream file(ACCOUNTS_FILE);

    if (!file)
    {
        throw runtime_error(
            "Could not open data/accounts.txt "
            "for saving."
        );
    }

    for (
        const shared_ptr<Account>& account :
        accounts
    )
    {
        file
            << account->getAccountType() << '|'
            << account->getAccountId() << '|'
            << account->getOwnerName() << '|'
            << account->getBalance()
            << '\n';
    }
}


// Load accounts from data/accounts.txt
void Bank::loadAccounts()
{
    ifstream file(ACCOUNTS_FILE);

    if (!file)
    {
        cout
            << "No accounts file found. "
            << "Starting with an empty bank.\n";

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

        try
        {
            double loadedBalance =
                stod(balanceText);

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
                cerr
                    << "Warning: Unknown account type "
                    << "was skipped.\n";
            }
        }
        catch (const exception&)
        {
            cerr
                << "Warning: Invalid account data "
                << "was skipped.\n";
        }
    }
}


// Save transaction to data/transactions.txt
void Bank::logTransaction(
    const string& source,
    const string& destination,
    double amount,
    const string& description
) const
{
    ofstream file(
        TRANSACTIONS_FILE,
        ios::app
    );

    if (!file)
    {
        throw runtime_error(
            "Could not open "
            "data/transactions.txt."
        );
    }

    time_t currentTime =
        time(nullptr);

    tm localTime{};

#ifdef _WIN32
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