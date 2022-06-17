#include "plant.h"
#include <iostream>
using namespace std;

/*plant - plant constructor
double initSize - passed value size
double initRate - passed rate value

Algorithm - call base class constructor to set the values
*/
plant::plant(double initSize, double initRate) : organism(initSize, initRate)
{
    organism(initSize, initRate);
}

/*NibbleOn - decrease the size by amount, if the amount is larger than the size, then set the 
size to 0
double amount - passed amount to decrease
return void
Algorithm - use alterSize() to decrease the amount and check if the size is < 0 or not
If yes, then use alterSize(to decrease the current size)

*/
void plant::nibbledOn(double amount)
{
    alterSize(-1 * amount);
    //alter size already check for negative
    if(getSize() < 0){
        alterSize(-1 * getSize());
    }
    //else{
        //alterSize(-1 * amount);
    //}
    // notes: if alter size 1st, do liek this
    //otherwise, keep it ike old one but remove alterSize
}

/*~plant- deconstructor for the clas plant
Algorithm - cout the plant died
*/
plant::~plant()
{
    cout << "PLANT DIED" << endl;
}