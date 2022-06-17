
//Class checkingAccount 
  
#ifndef H_checkingAccount
#define H_checkingAccount
 
#include "bankAccount.h"

/**
 * @brief checkAccount is a derived class from bankAccount base class and is inherited as public
 * 
 */
class checkingAccount: public bankAccount 
{
public:
    void withdraw(double amount);  // // update balance after withdrawal; balance=balance-withdraw;
    void print() const; /*This function should outputs the values of instance variables like AccountType, AccountNumber, FirstName, 
    						LastName, Balance. You no need print all the above instance variables. (Hint: Use getters */      
};

#endif