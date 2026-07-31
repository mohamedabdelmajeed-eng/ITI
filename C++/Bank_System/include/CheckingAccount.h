#ifndef CHECKING_ACCOUNT_H
#define CHECKING_ACCOUNT_H

#include "Account.h"
// CheckingAccount class derived from Account
class CheckingAccount : public Account
{
public:
    CheckingAccount(
        const std::string& id,
        const std::string& owner,
        double initialBalance
    );

    std::string getAccountType() const override;
};

#endif