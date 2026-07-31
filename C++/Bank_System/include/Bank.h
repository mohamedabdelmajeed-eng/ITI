#ifndef BANK_H
#define BANK_H

#include "Account.h"

#include <memory>
#include <string>
#include <vector>

using namespace std;

class Bank
{
private:
    vector<shared_ptr<Account>> accounts;

    shared_ptr<Account> findAccount(
        const string& accountId
    ) const;

    void logTransaction(
        const string& source,
        const string& destination,
        double amount,
        const string& description
    ) const;

public:
    void createAccount(
        const string& type,
        const string& accountId,
        const string& ownerName,
        double initialBalance
    );

    void deposit(
        const string& accountId,
        double amount
    );

    void withdraw(
        const string& accountId,
        double amount
    );

    void transfer(
        const string& sourceId,
        const string& destinationId,
        double amount
    );

    void displayAccounts() const;

    void saveAccounts() const;
    void loadAccounts();
};

#endif