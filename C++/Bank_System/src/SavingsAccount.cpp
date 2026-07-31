#include "SavingsAccount.h"

using namespace std;

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