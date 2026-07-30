// (Header file) 

//saving file from repeating 
#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <string>

class Account {
protected:
    std::string accountId;
    std::string ownerName;
    double balance;

public:
    Account(
        const std::string& accountId,
        const std::string& ownerName,
        double balance
    );

    virtual ~Account() = default;

    std::string getAccountId() const;
    std::string getOwnerName() const;
    double getBalance() const;

    void deposit(double amount);
    virtual void withdraw(double amount);

    virtual std::string getAccountType() const = 0;
    virtual void display() const = 0;
};

#endif