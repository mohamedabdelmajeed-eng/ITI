#include "CheckingAccount.h"

using namespace std;
// Constructor for CheckingAccount class, which initializes the account with an ID, owner name, and initial balance
CheckingAccount::CheckingAccount(
    const string& id,
    const string& owner,
    double initialBalance
)
    : Account(id, owner, initialBalance)// call the constructor of the base class Account to initialize the member variables of the CheckingAccount class
{
}

string CheckingAccount::getAccountType() const
{
    return "Checking";
}