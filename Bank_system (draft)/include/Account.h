// (Header file) abstract class for bank accounts

//header guard to prevent multiple inclusions
#ifndef ACCOUNT_H //if not defined ACCOUNT_H implement the following code
#define ACCOUNT_H// define ACCOUNT_H

#include <string>

class Account {
protected:
    std::string accountId;
    std::string ownerName;
    double balance;

public:
// Constructor to give start values to the member variables of the class and to check if the user enter invalid data  
Account(
        const std::string& accountId,//& تمرير على العنوان بدل نسخه جديده منو 
        const std::string& ownerName,// const & to avoid copying and allow passing of temporary objects
        double balance
    );

    // Virtual destructor to allow proper cleanup of derived classes
    // dafault implementation provided to make cpp make destructor تلقايى
    virtual ~Account() = default;// virtual destructor to allow proper cleanup of derived classes

    // Getter methods to access account details

    std::string getAccountId() const;// getter method to retrieve the account ID
    std::string getOwnerName() const;// getter method to retrieve the owner's name      //const method to indicate that it does not modify the object
    double getBalance() const; // getter method to retrieve the account balance

    void deposit(double amount);
    virtual void withdraw(double amount);

    virtual std::string getAccountType() const = 0;
    virtual void display() const = 0;
};

#endif// end of header guard