#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <typeinfo>
#include "date.h"
#include "transaction.h"
#include "sorter.h"
using namespace std;

/**Transaction parse(string record) - parse the data to put it in correct fields
 * string record - string passe to parse
 * return temp Transaction object that use Transaction constructor to set data
 * Algorithm - use getline + stringstream to parse the line using ',' to parse all temp string
	using stringstream to convert ids and price from string to int
	using stringstream + getline again to parse Date to seperate fields
	using stringstream to convert the strings to int for Date
	Then create temp obj of Date type and using Date constructor to set the variables
	After that, create Transaction obj and call it constructor to set the variables
 */
Transaction parse(string record)
{
	string IdString;//Transaction ID strinng
	int transactionId = 0; //int ID

	string transDate;
	Date transactionDate;//Date of transaction 
	
	string product;//Product

	string priceString;//Price String
	int price = 0; //int price

	string paymentType;//Payment type of transaction like Mastercard, visa
	string name;//Name of person making transaction
	string city;//City of the person
	string state;//State 
	string country;//country

	//parse data
	stringstream split(record);
	getline(split, IdString, ','); //special case, need to convert
	getline(split, transDate, ','); //special case, need to convert
	getline(split, product, ',');
	getline(split, priceString, ','); //special case, need to convert
	getline(split, paymentType, ',');
	getline(split, name, ',');
	getline(split, city, ',');
	getline(split, state, ',');
	getline(split, country, ',');

	//convert few string to int 
	stringstream tempID(IdString);
	tempID >> transactionId;

	stringstream tempPrice(priceString);
	tempPrice >> price;

	//parse Date and convert
	stringstream parseDate(transDate);
	int year = 0, month = 0, day = 0, hour = 0, min = 0;
	string YY, MM, DD, Hr, Min;
	getline(parseDate, MM, '/');
    getline(parseDate, DD, '/');
    getline(parseDate, YY, ' ');
    getline(parseDate, Hr, ':');
    getline(parseDate, Min, ' ');

	stringstream tempMM(MM);
	tempMM >> month;
	stringstream tempDD(DD);
	tempDD >> day;
	stringstream tempYY(YY);
	tempYY >> year;
	stringstream tempHr(Hr);
	tempHr >> hour;
	stringstream tempMin(Min);
	tempMin >> min;

	Date tempDate = Date(year, month, day, hour, min); //use this to set Data variables
	Transaction tempTrans = Transaction(transactionId, tempDate, product, price, paymentType, name, city, state, country);
	
	return tempTrans;
}


/*Function to readfile and return vector of Transaction
objects.*/
vector<Transaction> readFile(string filename)
{

	vector<Transaction> transactions;
	string line;

	try
	{
		ifstream myFile(filename);

		if(!myFile)
			throw string(filename);
		
		int lineCount=0;
		while(getline(myFile,line))
		{
			//Parse the line here ignoring the first line
			if(lineCount>0)
			{
				transactions.push_back(parse(line));
			}
			lineCount++;
		}
	}
	catch(string str)
	{
		cout <<"File "<<str<<" not found"<<endl;
	}

	return transactions;
	
}

/**int findModeTransaction - find the element that appear the most
 * vector<T> records- Data vector that can be either price ot Date
 * type T is tenplate to it can have different data type
 * vector<int>  ids -vector of ids
 * return the mode 
 * Algorithm - loop through the vector of data, then set the current variable to the current element
	Then set tempcount to 0;
	Loop again but this time, the element is the next one 
	Check to see if the current element is the same with current variable
	If yes, then increment count and set it to mode variable
	Exit the second loop and check to see if temp > count
	If yes, count = tempcount and mode = ids[i] of that count
	This one use to check to see if the last element  is the most occur or not/ duplicate one
	Then cout the highest variable
 */
template <class T>
//general idea = find the element that occur the most in records -> this can be either date or price -> need to use T type
//then it will return the id of the element that occurs the most
int findModeTransaction(vector<T> records,vector<int>  ids)
{
	int count = 0; 
	int mode = 0;
	T current;

	for(unsigned int i = 0; i < records.size(); i++){
		int tempCount = 0;
		current = records.at(i);

		for(unsigned int j = i + 1; j < records.size(); j++){
			if(records[i] == records[j]){
				tempCount++;
			}
		}

		if(tempCount > count){
			count = tempCount;
			mode = ids[i];
		}
		cout << current << endl;
	}
	return mode;
}



int main(int argc,char * argv[])
{

	//Correct file name
	string file="SalesJan2009.csv";

	//vector to hold all the transactions
	vector<Transaction> transactions;


	cout<<"Reading SalesJan2009.csv"<<endl;
	transactions= readFile(file);


	cout <<"File read."<<transactions.size()<<" transactions returned"<<endl;

	//vectors to hold the transaction dates, ids and prices
	vector<Date>* dates=new vector<Date>(); //leak
	vector<int> ids;
	vector<int>* prices=new vector<int>(); //leak

	//populating the vectors
	for(unsigned int i=0;i<transactions.size();i++) //notes: extra
	{
		dates->push_back(transactions[i].getDate()); //leak
		ids.push_back(transactions[i].getId());
		prices->push_back(transactions[i].getPrice()); //leak

	}

	//creating a sorter object to sort by transaction dates
	Sorter<Date> * sortByDate=new Sorter<Date>(dates,ids); //leak

	sortByDate->sort();

	//find the mode transaction date
	int modeDay=findModeTransaction(*sortByDate->getListVector(),sortByDate->getIdsVector());

	//printing the mode date
	for(unsigned int i=0;i<transactions.size();i++) //note = extra
	{
		if(transactions[i].getId()==modeDay)
		{
			Date d=transactions[i].getDate();
			cout <<"Maximum number of transaction happened on:"<<d.getMonth()<<":"<<d.getDay()<<":"<<d.getYear()<<endl;
			break;
		}
	}

	//creating a sorter object to sort by product price
	Sorter<int> * sortByPrice=new Sorter<int>(prices,ids); //leak

	sortByPrice->sort();
	
	//find the mode product price
	int modePrice=findModeTransaction(*sortByPrice->getListVector(),sortByPrice->getIdsVector());

	//print the product relating to the mode price
	for(unsigned int i=0;i<transactions.size();i++) //note extra
	{
		if(transactions[i].getId()==modePrice)
		{
			string product=transactions[i].getProduct();
			cout <<"Maximum transactions happened for:"<<product<<endl;
			break;
		}
	}
	//extra delete because of vector pointer 
	//this prevent memory leak
	delete dates;
	delete prices;
	delete sortByDate;
	delete sortByPrice;
	dates = NULL;
	prices = NULL;
	sortByDate = NULL;
	sortByPrice = NULL;

	return 0;
}