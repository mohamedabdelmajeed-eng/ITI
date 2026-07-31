#include "CheckingAccount.h"

using namespace std;

CheckingAccount::CheckingAccount(
    const string& id,
    const string& owner,
    double initialBalance
)
    : Account(id, owner, initialBalance)
{
}

string CheckingAccount::getAccountType() const
{
    return "Checking";
}