//#include <string> //extra
//Class bankAccount
  
#ifndef H_bankAccount 
#define H_bankAccount



using namespace std;
/**
 * @brief bankAccount
 * 
 */
class bankAccount
{
public:
    void setAccountNumber(int acct);
    void setAccountType(string accType);
    void setFirstName(string firstName);
    void setLastName(string lastName);
    void setCompanyName(string companyName);
    void setAddress(string address);
    void setCity(string city);
    void setPhone1(long int phone1);
    void setPhone2(long int phone2);
    void setBalance(int balance);
    
    int getAccountNumber() const;
    string getAccountType() const;
    string getFirstName() const;
    string getLastName() const;
    string getCompanyName() const;
    string getAddress() const;
    string getCity() const;
    long int getPhone1() const; 
    long int getPhone2() const; 
    double getBalance() const; 


    void withdraw(double amount);
    void deposit(double amount);
    // void print() const;

protected:
    int accountNumber; //2 long int
    double balance;   //10 convertdouble
    string accountType; //1
    string firstName; //3
    string lastName; //4
    string companyName; //5
    string address; //6
    string city; //7
    long int phone1; //8 long int
    long int phone2; //9 long int
};

#endif