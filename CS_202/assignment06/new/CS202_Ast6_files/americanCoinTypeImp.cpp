#include <iostream>
#include <string>
#include <vector>
#include "americanCoinType.h"
using namespace std;


/* setPennyCount- set value to penny attribute
int initialPenny- passed value
return void
Algorithm- set penny to argument
*/
void coinsBox::setPennyCount(int initialPenny){
    penny = initialPenny;
}

/* setNickelCount- set value to nickel attribute
int initialNickel- passed value
return void
Algorithm- set nickel to argument
*/
void coinsBox::setNickelCount(int initialNickel){
    nickel = initialNickel;
}

/* setDimeCount- set value to dime attribute
int initialDime- passed value
return void
Algorithm- set dime to argument
*/
void coinsBox::setDimeCount(int initialDime){
    dime = initialDime;
}

/* setQuarterCount- set value to quarter attribute
int initialQuarter- passed value
return void
Algorithm- set quarter to argument
*/
void coinsBox::setQuarterCount(int initialQuater){
    quarter = initialQuater;
}

/* setFiftycentpieceCount- set value to fifty_centpiece attribute
int initialFiftyCent- passed value
return void
Algorithm- set fifty_centpiece to argument
*/
void coinsBox::setFiftycentpieceCount(int initialFiftyCent){
    fifty_centpiece = initialFiftyCent;
}

/* setName- set value to name attribute
string initialName - paased value
return void
Algorithm- loop through the string and parse each character of string into array char *name
*/
void coinsBox::setName(string initialName){ 
    for(unsigned int i = 0; i < initialName.length(); i++){
        name[i] = initialName[i]; 
    }
}

/**getPennyCount- get value of penny attribute
 * return value of penny attribute
 * Algorithm- return penny attribute
**/
int coinsBox::getPennyCount() const{
    return penny;
}

/**getNickelCount- get value of nickel attribute
 * return value of nickel attribute
 * Algorithm- return nickel attribute
 **/
int coinsBox::getNickelCount() const{
    return nickel;
}

/**getDimeCount- get value of dime attribute
 * return value of dime attribute
 * Algorithm- return dime attribute
 **/
int coinsBox::getDimeCount() const{
    return dime;
}

/**getQuarterCount- get value of quarter attribute
 * return value of quarter attribute
 * Algorithm- return quarter attribute
 **/
int coinsBox::getQuarterCount() const{
    return quarter;
}

/**getFiftycentpieceCount- get value of fifty_centpiece attribute
 * return value of fifty_centpiece attribute
 * Algorithm- return fifty_centpiece attribute
 **/
int coinsBox::getFiftycentpieceCount() const{
    return fifty_centpiece;
}

/**getTotalAmountinCent- convert all coins to cent
 * return- value of cent
 * Algorithm- cent = penny + (nickel*5) + (dime*10) + (quarter*25) + (fifty*50)
 **/
double coinsBox::getTotalAmountinCent() const{
    double cent;
    cent = penny + (nickel * 5) + (dime * 10) + (quarter * 25) + (fifty_centpiece * 50);
    return cent;
}

/**getTotalAmountinDollars- convert all coins to dollars
 * return- value of dollars
 * Algorithm- dollars = total amount of cent / 100
 **/
double coinsBox::getTotalAmountinDollars() const{
    double dollar;
    dollar = (getTotalAmountinCent() / 100);
    return dollar;
}

/**CoinsBox - default contructor for coinsBox class
 * Algorithm - set all attributes to 0 and char *name to NULL
 * */
coinsBox::coinsBox(){
    penny = 0;
    nickel = 0;
    dime = 0;
    quarter = 0;
    fifty_centpiece = 0;
    name = NULL; 
}

/**coinsBox - constructor for coinsBox class
 * int Penny- passed penny value
 * int Nickel - passed nickel value
 * int Dime - passed dime value
 * int Quarter - passed quarter value
 * int FiftyCent- passed fifty cent value
 * char Name[LEN]- passed string in style of char with length of 50
 * Algorithm- create a dynamic array with LEN num
 * loop through LEN to initializing it to NULL
 * call setName() to set passed name value
 * call all setter functions to set all passed value
 * */
coinsBox::coinsBox(int Penny, int Nickel, int Dime, int Quarter, int FiftyCent, char Name[LEN]){ 
    name = new char[LEN]; //create a array with LEN num
    for(int i = 0; i < LEN; i++){ //initialize to NULL, otherwise, it will cause error
        name[i] = '\0';
    }
    setName(Name); //call setName to assignt _name to char *name 

    setPennyCount(Penny);
    setQuarterCount(Quarter);
    setNickelCount(Nickel);
    setDimeCount(Dime);
    setFiftycentpieceCount(FiftyCent);
}

/**destructor- destructor of coinsBox class
 * Algorithm- delete array of char*name
 * put the char *name to null to prevent dangling pointer
 * */
coinsBox::~coinsBox(){
    delete []name;
    name = NULL;
}

/**operator= - assignment operator overloading. It allows the deep copy when you use pointers as member variables in any class.
 * const &original - passed object
 * return *this
 * Alorithm- set all coinsBox attributes to passed object value that access that attributes
 * */
coinsBox &coinsBox::operator=(const coinsBox &original){ 
    //notes: do not need to copy name because it's already call in setName in main
    //which also mean that we dont have to do deep copy?
    penny = original.penny;
    nickel = original.nickel;
    dime = original.dime;
    quarter = original.quarter;
    fifty_centpiece = original.fifty_centpiece; 

    return *this;
}

/**operator<< - To display/print data use the friend function:
 * const &original - passed object
 * return ofstream object
 * Alorithm- output all the values and messagaes using ofstream object and overloading 
 * */
ostream &operator<<(ostream & out, const coinsBox & original){ 
    out << original.name << " :- Penny = " << original.getPennyCount() << "; Nickel = " << original.getNickelCount() << "; Dime = " << original.getDimeCount() << 
        "; Quarter= " << original.getQuarterCount() << "; Fifty_centpiece = " << original.getFiftycentpieceCount() << ";Cent = " << original.getTotalAmountinCent() << 
        "; Dollar = " << original.getTotalAmountinDollars() << "; Adress = " << &original << endl;
    return out;
}

/**operator<< - To read the data use the friend function:
 * const &original - passed object
 * return ifstream object
 * Alorithm- initialize all attributes to 0 and prompt the user to enter the value
 * then the attributes value of object = add the value the user enter
 * */
istream &operator>>(istream & in, coinsBox & original){ 
    int Penny = 0, Nickel = 0, Dime = 0, Quarter = 0, Fifty = 0;

    cout << "penny : \n";
    in >> Penny;
    cout << "nickel : \n";
    in >> Nickel;
    cout << "dime : \n";
    in >> Dime;
    cout << "quarter : \n";
    in >> Quarter;
    cout << "fifty_centpiece : \n";
    in >> Fifty;

    original.penny += Penny;
    original.nickel += Nickel;
    original.dime += Dime;
    original.quarter += Quarter;
    original.fifty_centpiece += Fifty;

    return in;
}

/**operator+- To Adds two numbers represented as coinsBoxobject:
 * const &original - passed object
 * return temp/3th object of coinsBox class
 * Alorithm- add all attributes of 1st to 2nd object and assign it to 3th object 
 * then call getTotalinCent() and getTotalinDollar() for total amount
 * and then check to see if any values are less than 0 or not
 * if yes, set that object's instance to 0
 * */
coinsBox coinsBox::operator+(const coinsBox &original) const{
    coinsBox returnValue; 
    
    returnValue.penny = penny + original.penny;
    returnValue.nickel = nickel + original.nickel;
    returnValue.dime = dime + original.dime;
    returnValue.quarter = quarter + original.quarter;
    returnValue.fifty_centpiece = fifty_centpiece + original.fifty_centpiece;
    getTotalAmountinCent();
    getTotalAmountinDollars();

    if(returnValue.penny < 0){
        returnValue.penny = 0;
    }
    if(returnValue.nickel < 0){
        returnValue.nickel = 0;
    }
    if(returnValue.dime < 0){
        returnValue.dime = 0;
    }
    if(returnValue.quarter < 0){
        returnValue.quarter = 0;
    }
    if(returnValue.fifty_centpiece < 0){
        returnValue.fifty_centpiece = 0;
    }
    return returnValue;  
}

/**operator+- To subtarct two numbers represented as coinsBoxobject:
 * const &original - passed object
 * return temp/3th object of coinsBox class
 * Alorithm- subtract all attributes of 1st to 2nd object and assign it to 3th object 
 * then call getTotalinCent() and getTotalinDollar() for total amount
 * and then check to see if any values are less than 0 or not
 * if yes, set that object's instance to 0
 * */
coinsBox coinsBox::operator-(const coinsBox & original) const{
    coinsBox returnValue; 
    
    returnValue.penny = penny - original.penny;
    returnValue.nickel = nickel - original.nickel;
    returnValue.dime = dime - original.dime;
    returnValue.quarter = quarter - original.quarter;
    returnValue.fifty_centpiece = fifty_centpiece - original.fifty_centpiece;
    getTotalAmountinCent();
    getTotalAmountinDollars();

    if(returnValue.penny < 0){
        returnValue.penny = 0;
    }
    if(returnValue.nickel < 0){
        returnValue.nickel = 0;
    }
    if(returnValue.dime < 0){
        returnValue.dime = 0;
    }
    if(returnValue.quarter < 0){
        returnValue.quarter = 0;
    }
    if(returnValue.fifty_centpiece < 0){
        returnValue.fifty_centpiece = 0;
    }
    return returnValue; 
}

/**operator+- To multiply two numbers represented as coinsBoxobject:
 * const &original - passed object
 * return temp/3th object of coinsBox class
 * Alorithm- multiple all attributes of 1st to 2nd object and assign it to 3th object 
 * then call getTotalinCent() and getTotalinDollar() for total amount
 * and then check to see if any values are less than 0 or not
 * if yes, set that object's instance to 0
 * */
coinsBox coinsBox::operator*(const coinsBox & original) const{
    coinsBox returnValue; 
    
    returnValue.penny = penny * original.penny;
    returnValue.nickel = nickel * original.nickel;
    returnValue.dime = dime * original.dime;
    returnValue.quarter = quarter * original.quarter;
    returnValue.fifty_centpiece = fifty_centpiece * original.fifty_centpiece;
    getTotalAmountinCent();
    getTotalAmountinDollars();

    if(returnValue.penny < 0){
        returnValue.penny = 0;
    }
    if(returnValue.nickel < 0){
        returnValue.nickel = 0;
    }
    if(returnValue.dime < 0){
        returnValue.dime = 0;
    }
    if(returnValue.quarter < 0){
        returnValue.quarter = 0;
    }
    if(returnValue.fifty_centpiece < 0){
        returnValue.fifty_centpiece = 0;
    }
    
    return returnValue;  
}

/**operator-= -Subtracts coinBox1 from CoinBox2 and the result is assigned tocoinBox2. (coinBox2 -= coinBox1)
 * const &value - passed object
 * return *this
 * Alorithm- subtract all attributes of 1st object from 2nd object
 * then check to see if the value if less than 0 or not
 * if yes then set attributes to 0
 * */
coinsBox &coinsBox::operator-=(const coinsBox & value){
    penny -= value.penny;
    if(penny < 0){
        penny = 0; 
    }
    nickel -= value.nickel;
    if(nickel < 0){
        nickel = 0;
    }
    dime -= value.dime;
    if(dime < 0){
        dime = 0;
    }
    quarter -= value.quarter;
    if(quarter < 0){
        quarter= 0;
    }
    fifty_centpiece -= value.fifty_centpiece;
    if(fifty_centpiece < 0){
        fifty_centpiece = 0;
    }

    getTotalAmountinCent();
    getTotalAmountinDollars();
    return *this;  
}

/**operator++ - post increment/ postfix operator) – It increments all the 5 members by 1 individually.
 * return temp object of coinsBox class
 * Algorithm- post increment all 5 attributes of class by 1 
 * then check to see if it less than 0 or not
 * if yes than set that attribuet to 0
 * */
coinsBox coinsBox::operator++(){
    
    coinsBox temp;
    temp.penny = ++penny;
    temp.dime = ++dime;
    temp.nickel = ++nickel;
    temp.quarter = ++quarter;
    temp.fifty_centpiece = ++fifty_centpiece;

    if(temp.penny < 0){
        penny = 0;
    }
    if(temp.dime < 0){
        dime = 0;
    }
    if(temp.nickel < 0){
        nickel = 0;
    }
    if(temp.quarter < 0){
        quarter = 0;
    }
    if(temp.fifty_centpiece < 0){
        fifty_centpiece = 0;
    }
    
    return temp;
}    

/**operator++ - preincrement/ pretfix operator) – It increments all the 5 members by 1 individually.
 * return temp object of coinsBox class
 * Algorithm- pre increment all 5 attributes of class by 1 
 * then check to see if it less than 0 or not
 * if yes than set that attribuet to 0
 * */
coinsBox coinsBox::operator++(int dummy){

    coinsBox temp;
    temp.penny = penny++;
    temp.dime = dime++;
    temp.nickel = nickel++;
    temp.quarter = quarter++;
    temp.fifty_centpiece = fifty_centpiece++;

    if(temp.penny < 0){
        penny = 0;
    }
    if(temp.dime < 0){
        dime = 0;
    }
    if(temp.nickel < 0){
        nickel = 0;
    }
    if(temp.quarter < 0){
        quarter = 0;
    }
    if(temp.fifty_centpiece < 0){
        fifty_centpiece = 0;
    }
    
    return temp;
} 

/**operator-- - post decrement/ destfix operator) – It decrements all the 5 members by 1 individually.
 * return temp object of coinsBox class
 * Algorithm- post decrement all 5 attributes of class by 1 
 * then check to see if it less than 0 or not
 * if yes than set that attribuet to 0
 * */
coinsBox coinsBox::operator--(){

    coinsBox temp;
    temp.penny = --penny;
    temp.dime = --dime;
    temp.nickel = --nickel;
    temp.quarter = --quarter;
    temp.fifty_centpiece = --fifty_centpiece;

    if(temp.penny < 0){
        penny = 0;
    }
    if(temp.dime < 0){
        dime = 0;
    }
    if(temp.nickel < 0){
        nickel = 0;
    }
    if(temp.quarter < 0){
        quarter = 0;
    }
    if(temp.fifty_centpiece < 0){
        fifty_centpiece = 0;
    }
    
    return temp;
}

/**operator-- - pre decrement/ destfix operator) – It decrements all the 5 members by 1 individually.
 * return temp object of coinsBox class
 * Algorithm- pre decrement all 5 attributes of class by 1 
 * then check to see if it less than 0 or not
 * if yes than set that attribuet to 0
 * */
coinsBox coinsBox::operator--(int dummy){

    coinsBox temp;
    temp.penny = penny--;
    temp.dime = dime--;
    temp.nickel = nickel--;
    temp.quarter = quarter--;
    temp.fifty_centpiece = fifty_centpiece--;

    if(temp.penny < 0){
        penny = 0;
    }
    if(temp.dime < 0){
        dime = 0;
    }
    if(temp.nickel < 0){
        nickel = 0;
    }
    if(temp.quarter < 0){
        quarter = 0;
    }
    if(temp.fifty_centpiece < 0){
        fifty_centpiece = 0;
    }
    
    return temp;
}

/**operator== Compare two coinsBox  objects if they are equal
 * return the compare of all members of both object
 **/
bool coinsBox::operator==(const coinsBox & original) const{
    return (penny == original.penny && nickel == original.nickel && dime == original.dime && quarter == original.quarter
        && fifty_centpiece == original.fifty_centpiece); 
}

/**operator!= Compare two coinsBox  objects if they are not equal
 * return the compare of all members of both object
 **/
bool coinsBox::operator!=(const coinsBox & original) const{
    return !((*this) == original);
}

/**operator== Compare two coinsBox objects if object 1 <= object2
 * return the compare of all members of both object
 **/
bool coinsBox::operator<=(const coinsBox & original) const{
    return (penny <= original.penny && nickel <= original.nickel && dime <= original.dime && quarter <= original.quarter
        && fifty_centpiece <= original.fifty_centpiece);
}

/**operator== Compare two coinsBox objects if object 1 < object2
 * return the compare of all members of both object
 **/
bool coinsBox::operator<(const coinsBox & original) const{
    return (penny < original.penny && nickel < original.nickel && dime < original.dime && quarter < original.quarter
        && fifty_centpiece < original.fifty_centpiece); 
}

/**operator== Compare two coinsBox objects if object 1 >= object2
 * return the compare of all members of both object
 **/
bool coinsBox::operator>=(const coinsBox & original) const{
    return (penny >= original.penny && nickel >= original.nickel && dime >= original.dime && quarter >= original.quarter
        && fifty_centpiece >= original.fifty_centpiece); 
}

/**operator== Compare two coinsBox objects if object 1 > object2
 * return the compare of all members of both object
 **/
bool coinsBox::operator>(const coinsBox & original) const{
    return (penny > original.penny && nickel > original.nickel && dime > original.dime && quarter > original.quarter
        && fifty_centpiece > original.fifty_centpiece); 
}
