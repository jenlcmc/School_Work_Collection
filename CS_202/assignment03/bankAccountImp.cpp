

// include library and header file ffor implement file
#include <string>
#include "bankAccount.h"
using namespace std;

/*void setAccountNumber - protected members are set according to the parameters
    int acct - Account number
    return void

    Algorithms - set protected member according to the parameter
*/
void bankAccount::setAccountNumber(int acct)
{
    accountNumber = acct;
}

/*void setAccountType - protected members are set according to the parameters
    string accType - name of account type
    return void

    Algorithms - set protected member according to the parameter
*/
void bankAccount::setAccountType(string accType)
{
    accountType = accType;
}

/*void setFirstName - protected members are set according to the parameters
    string firstName - first name of the account owner
    return void

    Algorithms - set protected member according to the parameter by using this keyword
*/
void bankAccount::setFirstName(string firstName)
{
    this->firstName = firstName;
}

/*void setLastName - protected members are set according to the parameters
    string lastName - last name of the account owner
    return void

    Algorithms - set protected member according to the parameter by using this keyword
*/
void bankAccount::setLastName(string lastName)
{
    this->lastName = lastName;
}

/*void setCopmpanyName - protected members are set according to the parameters
    string companyName -  company name of the account owner
    return void

    Algorithms - set protected member according to the parameter by using this keyword
*/
void bankAccount::setCompanyName(string companyName)
{
    this->companyName = companyName;
}

/*void setAddress - protected members are set according to the parameters
    string address- address of account owner
    return void

    Algorithms - set protected member according to the parameter by using this keyword
*/
void bankAccount::setAddress(string address)
{
    this->address = address;
}

/*void setCity - protected members are set according to the parameters
string city- city of the account owner
    return void

    Algorithms - set protected member according to the parameter by using this keyword
*/
void bankAccount::setCity(string city)
{
    this->city = city;
}

/*void setPhone1 - protected members are set according to the parameters
    long int phone1 - phone numbers
    return void

    Algorithms - set protected member according to the parameter by using this keyword
*/
void bankAccount::setPhone1(long int phone1)
{
    this->phone1 = phone1;
}

/*void setPhone1 - protected members are set according to the parameters
    long int phone2 - phone numbers
    return void

    Algorithms - set protected member according to the parameter by using this keyword
*/
void bankAccount::setPhone2(long int phone2)
{
    this->phone2 = phone2;
}

/*void setBalance - protected members are set according to the parameters
    double balance- total balance in the account
    return void

    Algorithms - set protected member according to the parameter by using this keyword
*/
void bankAccount::setBalance(int balance)
{
    this->balance = balance;
}

/*void getAccountNumber - return the values of the instance variable
    return int accountNumber value

    Algorithms - return the values of the instance variable based on setter functions
*/
int bankAccount::getAccountNumber() const
{
    return (accountNumber);
}

/*void getAccountType - return the values of the instance variable
    return string AccountType value

    Algorithms - return the values of the instance variable based on setter functions
*/
string bankAccount::getAccountType() const
{
    return (accountType);
}

/*void getFirstName- return the values of the instance variable
    return string 1st name value

    Algorithms - return the values of the instance variable based on setter functions
*/
string bankAccount::getFirstName() const
{
    return (firstName);
}

/*void getLastName- return the values of the instance variable
    return string last name value

    Algorithms - return the values of the instance variable based on setter functions
*/
string bankAccount::getLastName() const
{
    return (lastName);
}

/*void getCompanyName- return the values of the instance variable
    return string company name value

    Algorithms - return the values of the instance variable based on setter functions
*/
string bankAccount::getCompanyName() const
{
    return (companyName);
}

/*void getAddress- return the values of the instance variable
    return string address value

    Algorithms - return the values of the instance variable based on setter functions
*/
string bankAccount::getAddress() const
{
    return (address);
}

/*void getCity- return the values of the instance variable
    return string city value

    Algorithms - return the values of the instance variable based on setter functions
*/
string bankAccount::getCity() const
{
    return (city);
}

/*void getPhone1- return the values of the instance variable
    return long int phone1 value

    Algorithms - return the values of the instance variable based on setter functions
*/
long int bankAccount::getPhone1() const
{
    long int Phone1 = phone1;
    return (Phone1);
}

/*void getPhone2- return the values of the instance variable
    return long int phone2 value

    Algorithms - return the values of the instance variable based on setter functions
*/
long int bankAccount::getPhone2() const
{
    long int Phone2 = phone2;
    return (Phone2);
}

/*void getBalance- return the values of the instance variable
    return double balance value

    Algorithms - return the values of the instance variable based on setter functions
*/
double bankAccount::getBalance() const
{
    double Balance = balance;
    return (Balance);
}

/*void withdraw- subtract the amount from the balance and update the balance.
    double amount - amount that the user want to withdraw

    Algorithm- reduce the total amount have to amount withdraw and update
    to have to new total balance
*/
void bankAccount::withdraw(double amount)
{
    balance -= amount;
}

/*void deposit- add the amount from the balance and update the balance.
    double amount - amount that the user want to deposit

    Algorithm- add the total amount have to amount deposit and update
    to have to new total balance
*/
void bankAccount::deposit(double amount)
{
    balance += amount;
}