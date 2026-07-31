#ifndef SAVINGS_ACCOUNT_H
#define SAVINGS_ACCOUNT_H

#include "Account.h"
using namespace std;

class SavingsAccount : public Account
{
public:
    SavingsAccount(
        const string& id,
        const string& owner,
        double initialBalance
    );

    string getAccountType() const override;
};

#endif