// Header file

// Prevent the header file from repeating
#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <string>

using namespace std;

class Account
{
protected:
    string accountId;
    string ownerName;
    double balance;

public:
    Account(
        const string& accountId,
        const string& ownerName,
        double balance
    );

    virtual ~Account() = default;

    string getAccountId() const;
    string getOwnerName() const;
    double getBalance() const;

    void deposit(double amount);

    virtual void withdraw(double amount);

    virtual string getAccountType() const = 0;

    virtual void display() const;
};

#endif