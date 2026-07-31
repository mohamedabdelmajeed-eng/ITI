#include "../include/Account.h"// call header file to use it in cpp file(Account.h)

#include <stdexcept> // used for if the user enter invalid data

using namespace std;
// Constructor to initialize account details
//Account ::Account =for wrriting the constructor of the Account class outside the class definition 
Account::Account(
    const string& accountId,
    const string& ownerName,
    double balance
)
// Member initializer list to initialize member variables and give start values to them
 // left account word to refer to the class name and right accountId is the parameter passed to the constructor   
: accountId(accountId),
      ownerName(ownerName),
      balance(balance)

    //body of the constructor to check if the user enter invalid data
    //thrrow is used to throw an exception if the user enter invalid data
      {
    if (accountId.empty())// check if the accountId is empty
    {
        throw invalid_argument("Account ID cannot be empty."); // throw an exception if the accountId is empty
    }

    if (ownerName.empty())// check if the ownerName is empty
    {
        throw invalid_argument("Owner name cannot be empty."); // throw an exception if the ownerName is empty
    }

    if (balance < 0)
    {
        throw invalid_argument("Initial balance cannot be negative.");
    }
}
// Getter method to retrieve the account ID
string Account::getAccountId() const
{
    return accountId;
}
// Getter method to retrieve the owner's name
string Account::getOwnerName() const
{
    return ownerName;
}

double Account::getBalance() const
{
    return balance;
}
// Method to deposit an amount into the account , deposit is a fun related to the account class and it is used to add money to the account balance
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
// check if the amount to withdraw is greater than the balance, if it is then throw an exception
// runtime_error is used to indicate that an error has occurred during the execution of the program, and it is not recoverable. In this case, it is used to indicate that the user is trying to withdraw more money than they have in their account.

    if (amount > balance)
    {
        throw runtime_error("Insufficient balance.");
    }

    balance -= amount;
}