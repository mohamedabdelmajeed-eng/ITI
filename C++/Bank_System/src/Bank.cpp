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

// Helper function to find an account by ID
shared_ptr<Account> Bank::findAccount(
    const string& accountId
) const
{
    auto result = find_if(
        accounts.begin(),
        accounts.end(),
        [&accountId](const shared_ptr<Account>& account)
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


// Helper function to log create account
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


// deposit function to deposit money into an account
void Bank::deposit(
    const string& accountId,
    double amount
)
{
    shared_ptr<Account> account =
        findAccount(accountId);

    if (account == nullptr)
    {
        throw runtime_error("Account not found.");
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