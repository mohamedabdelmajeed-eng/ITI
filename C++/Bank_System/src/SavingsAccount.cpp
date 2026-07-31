#include "SavingsAccount.h"

SavingsAccount::SavingsAccount(
    const std::string& id,
    const std::string& owner,
    double initialBalance
)
    : Account(id, owner, initialBalance)
{
}

std::string SavingsAccount::getAccountType() const
{
    return "Savings";
}