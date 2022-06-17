//Class savingsAccount 

#ifndef H_savingsAccount
#define H_savingsAccount
   
#include "bankAccount.h"

const double DEFAULT_INTEREST_RATE_SAVINGS = 2.5;

/**
 * @brief savingsAccount is a derived class from base class bankAccount and is inherited as public
 * 
 */
class savingsAccount: public bankAccount
{ 
public:
    void withdraw(double amount); // update balance after withdrawal; balance=balance-withdraw;
    void print() const; /*This function should outputs the values of instance variables like AccountType, AccountNumber, FirstName, 
    						LastName, Balance. Interest you can earn after 1 Year, 2 Year, and 3 Year in a separate line.
    						You no need print all the above instance variables. (Hint: Use getters */
    savingsAccount(double intRate = DEFAULT_INTEREST_RATE_SAVINGS); /*Constructor with a parameter having a default value – 
    															Write the definition of this constructor with the instance variable 
    															interestRate(protected member)*/

protected:
    double interestRate;
};

#endif