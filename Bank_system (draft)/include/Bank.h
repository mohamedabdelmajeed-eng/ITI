#ifndef BANK_H
#define BANK_H

#include "Account.h"

#include <memory>// for using shared_ptr type of smart pointer to manage the lifetime of Account objects
#include <string>
#include <vector>

class Bank
{
private:
    std::vector<std::shared_ptr<Account>> accounts;// vector of shared pointers to Account objects to store all the accounts in the bank
//<shared_ptr<Account>> is a smart pointer that manages the lifetime of Account objects, ensuring that they are properly deleted when no longer needed. This allows for dynamic memory management and prevents memory leaks.
   
    std::shared_ptr<Account> findAccount(// Helper function to find an account by ID
        const std::string& accountId
    ) const;

    void logTransaction(
        const std::string& source,
        const std::string& destination,
        double amount,
        const std::string& description
    ) const;

public:
    void createAccount(
        const std::string& type,
        const std::string& accountId,
        const std::string& ownerName,
        double initialBalance
    );

    void deposit(
        const std::string& accountId,
        double amount
    );

    void withdraw(
        const std::string& accountId,
        double amount
    );

    void transfer(
        const std::string& sourceId,
        const std::string& destinationId,
        double amount
    );

    void displayAccounts() const;

    void saveAccounts() const;
    void loadAccounts();
};

#endif