#include "organism.h"

/*organism - constructor that set growthRate and size with value passed in
double initSize - passed size
double initRate - passed rate

Algorithm- set growthRate and size to the passed in 

*/
organism::organism(double initSize, double initRate)
{
    growthRate = initRate;
    size = initSize;
}
	
/*simualteWeek- increment the size by growthrate
return void
Algorithm - use alterSize function to increment the growthRate

*/
void organism::simulateWeek()
{   
    alterSize(growthRate);
}

/*assignRate- assign growthRate with the value passed in
double newRate - passed value to assign to growthRate
return void
Algorithm - assign growthRate with the value passed in

*/
void organism::assignRate(double newRate)
{
    growthRate = newRate;
}

/*alterSize - increase the size by amount
double amount- passed value to increse
return void
Algorithm - increment size with passed amount

*/
void organism::alterSize(double amount)
{
    size += amount; 
}
	
/*death - set growthrate and size to 0
return void
*/
void organism::death()
{
    growthRate = 0;
    size = 0;
}

/*getSize - return the size 
return double size value
*/
double organism::getSize() const
{
    return size; 
}

/*getRate - return the growthRate 
return double growthRate value
*/
double organism::getRate() const
{   
    return growthRate;
}

/*isAlvie - check to see if the it's still alive or not
Algorithm - return true if size > 0 and false if < 0
return true or false
*/
bool organism::isAlive() const
{
    if(size > 0){
        return true;
    }else{
        return false;
    }

}

/*~organism- deconstructor for organism class
Algorithm - set growthRate and size to 0

*/
organism::~organism()
{
	growthRate =0;
    size = 0;
}
