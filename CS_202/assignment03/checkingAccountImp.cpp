

// include library and header file for implement file
#include <iostream>
#include <iomanip>
#include "checkingAccount.h"

/*void withdraw() - function to check the withdraw amount to the balance. If amount more than or equal balance
then it will display error. Else, it will update balance after withdraw
double amount - amount of money withdraw
return void

Algorithm- use if-else statement to check for condition and output error if withdraw amount more
or equal balance. If not, then show new update of the balance
*/
void checkingAccount::withdraw(double amount)
{
    if (amount >= balance)
    {
        cout << "Not enough money in the checking account !!" << endl;
    }
    else
    {
        balance -= amount;
    }
}

/*
void print - function to outputs the values of instance variables like AccountType, AccountNumber,
FirstName, LastName, Balance
return void

Algorithm- use getter funtions in bankAccountImp.cpp to print out the value. checkingAccount inheritance
from bankAccount so no no need to use scope resolution.
*/
void checkingAccount::print() const
{
    string AccTypes = getAccountType();
    cout << AccTypes << " ACCT#:" << endl;
    cout << "Account Type \t:" << AccTypes << endl;

    int AcctNums = getAccountNumber();
    cout << "Account Number:\t" << AcctNums << endl;

    string firstNAme = getFirstName();
    cout << "First Name \t:   " << firstNAme << endl;

    string LAstName = getLastName();
    cout << "Last Name \t:   " << LAstName << endl;

    long int PhoneNum = getPhone1();
    cout << "Phone1 \t:   " << PhoneNum << endl;

    double BalanceTotal = getBalance();
    cout << "Balance \t:   " << setprecision(8) << "$" << BalanceTotal << ".00" << endl;
}