#include "SavingsAccount.h"

using namespace std;
// Constructor for SavingsAccount class, which initializes the account with an ID, owner name, and initial balance
SavingsAccount::SavingsAccount(
    const string& id,
    const string& owner,
    double initialBalance
)
    : Account(id, owner, initialBalance)
{
}

string SavingsAccount::getAccountType() const
{
    return "Savings";
}