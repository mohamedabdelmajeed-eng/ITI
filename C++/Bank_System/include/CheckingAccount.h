#ifndef CHECKING_ACCOUNT_H
#define CHECKING_ACCOUNT_H

#include "Account.h"

using namespace std;

class CheckingAccount : public Account
{
public:
    CheckingAccount(
        const string& id,
        const string& owner,
        double initialBalance
    );

    string getAccountType() const override;
};

#endif