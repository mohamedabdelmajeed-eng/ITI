#include "../include/Account.h"

#include <stdexcept>// used for if the user enter invalid data(throw runtime_error and invalid_argument)

using namespace std;

Account::Account(
    const string& accountId,
    const string& ownerName,
    double balance
)
    : accountId(accountId),
      ownerName(ownerName),
      balance(balance)
{
    if (accountId.empty())
    {
        throw invalid_argument("Account ID cannot be empty.");
    }

    if (ownerName.empty())
    {
        throw invalid_argument("Owner name cannot be empty.");
    }

    if (balance < 0)
    {
        throw invalid_argument("Initial balance cannot be negative.");
    }
}

string Account::getAccountId() const
{
    return accountId;
}

string Account::getOwnerName() const
{
    return ownerName;
}

double Account::getBalance() const
{
    return balance;
}

void Account::deposit(double amount)
{
    if (amount <= 0)
    {
        throw invalid_argument(
            "Deposit amount must be greater than zero."
        );
    }

    balance += amount;
}

void Account::withdraw(double amount)
{
    if (amount <= 0)
    {
        throw invalid_argument(
            "Withdrawal amount must be greater than zero."
        );
    }

    if (amount > balance)
    {
        throw runtime_error("Insufficient balance.");
    }

    balance -= amount;
}