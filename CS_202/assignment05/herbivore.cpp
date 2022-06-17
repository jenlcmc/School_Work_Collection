#include "herbivore.h"
#include <iostream>
using namespace std;

const double herbivore::PORTION = 0.5;
const double herbivore::MAX_FRACTION = 0.1;

/*herbivore - constructor for herbivore class
double initSize - passed size value
double initRate - passed rate value
double initNeed - passed need value
Algorithm - use base class constructor to set each value 

*/
herbivore::herbivore(double initSize, double initRate, double initNeed) : animal(initSize, initRate, initNeed)
{

}

/*nibble - function that consumes a portion of a plant object
plant meal - passed meal amount by reference for effective
rerturn void
Algorithm- amount is set by PORTION multipled by size of the meal object
If amount is larger than MAX_FRACTION, multiplied by needThisWeek, then set amount to MAX_FRACTION multipled
by needTHisWeek
If amount is larger than value returned by stillNeed(), then set amount to stillNeed()
Call eat and meal object'snibbleOn() and pass the same amount into both functions

*/
void herbivore::nibble(plant& meal) 
{
    
    double amount = 0;
    amount = PORTION * meal.getSize(); 

    if(amount > (MAX_FRACTION * totalNeed())){
        amount = MAX_FRACTION * totalNeed();
    }
    if(amount > stillNeed()){
        amount = stillNeed();
    }

    eat(amount);
    meal.nibbledOn(amount); 
}

/*~herbivore - destructor for herbivore class
Algorithms- output "FISH DIED"

*/
herbivore::~herbivore()
{
    cout << "FISH DIED" << endl;
}