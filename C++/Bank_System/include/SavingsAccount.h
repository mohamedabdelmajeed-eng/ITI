#ifndef SAVINGS_ACCOUNT_H
#define SAVINGS_ACCOUNT_H

#include "Account.h"

class SavingsAccount : public Account
{
public:
    SavingsAccount(
        const std::string& id,
        const std::string& owner,
        double initialBalance
    );

    std::string getAccountType() const override;
};

#endif