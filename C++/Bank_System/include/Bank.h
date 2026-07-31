#ifndef BANK_H
#define BANK_H

#include "Account.h"

#include <memory>// for using shared_ptr type of smart pointer to manage the lifetime of Account objects
#include <string>
#include <vector>
// Bank class to manage bank accounts
class Bank
{
private:
    std::vector<std::shared_ptr<Account>> accounts;

    std::shared_ptr<Account> findAccount( // Helper function to find an account by ID
        const std::string& accountId
    ) const;

    void logTransaction(// Helper function to save transactions
        const std::string& source,
        const std::string& destination,
        double amount,
        const std::string& description
    ) const;

public:
    void createAccount( // Helper function to log create account
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

    void displayAccounts() const;// Helper function to display all accounts

    void saveAccounts() const;// Helper function to save all accounts to a file
    void loadAccounts();//
};

#endif