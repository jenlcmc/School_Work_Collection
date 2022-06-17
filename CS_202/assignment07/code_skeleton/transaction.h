/*Transaction class to hold each transaction*/
#include <iostream>
using namespace std;
//This file is already implement for students
class Transaction
{
private:
	int transactionId;//Transaction ID
	Date transactionDate;//Date of transaction 
	string product;//Product
	int price;//Price 
	string paymentType;//Payment type of transaction like Mastercard, visa
	string name;//Name of person making transaction
	string city;//City of the person
	string state;//State 
	string country;//country

public:
	//constructor
	Transaction(int tID,Date t,string pro,int pri,string pt,string n,string c,string s,string coun):transactionDate(t)
	{
		transactionId=tID;
		product=pro;
		price=pri;
		paymentType=pt;
		name=n;
		city=c;
		state=s;
		country=coun;
	}
	/*Transaction()
	{

	}*/

	int getId()
	{
		return transactionId;
	}
	
	int getPrice()
	{
		return price;
	}
	string getName()
	{
		return name;
	}
	Date getDate()
	{
		return transactionDate;
	}
	string getProduct()
	{
		return product;
	}
	virtual ~Transaction(){}


};
