#include "animal.h"
/*animal - animal constructor for animal class
double initSize - passed size value
double initRate- passed rate value
double initNeed- passed need value
Algorithm - use base class constructor to initializing size and rate. Then assign needThisWeek to passed
Need value and set eatenThisWeek to 0

*/
animal::animal(double initSize, double initRate, double initNeed) : organism(initSize, initRate)
{	
    needThisWeek = initNeed;
    eatenThisWeek = 0;
}

/*assignNeed - reassigns needThisWeek to value passed in 
double newNeed - passed value for reassign
return void
Algorithm - reassigns needThisWeek to value passed in 

*/
void animal::assignNeed(double newNeed)
{
    needThisWeek = newNeed;
}

/*eat- reassigns needThisWeek to value passed in 
double newNeed - passed value for increment
return void
Algorithm - increments eatenThisWeek with amount passed in

*/
void animal::eat(double amount)
{
    eatenThisWeek += amount;
}

/*simulateWeek-  simulate a week for the pond
return void
Algorithm - Changes the sign on growthRate based on whether the value returned by stillNeed();  
sets the  sign  to  negative  if stillNeed() returns a positive number and sets the sign to positive if 
stillNeed()returns 0
Then the function calls organism’s simulateWeek() function, sets eatenThisWeek to 0, 
checks if stillAlive() if no longer alive then call death()function

*/
void animal::simulateWeek()
{
    if(stillNeed() == 0){
        if(growthRate > 0){
            growthRate = (1* growthRate);
        }
    }else{
        if(growthRate > 0){
            growthRate = (-1 * growthRate);
        }
    }

/*stillNeed - check to see the amount of needed for a week
return either 0 or differenceNeed
Algorithm -returns 0 if eatenThisWeek is greater than or equal to needThisWeek,
and returns the difference between needThisWeek and eatenThisWeek otherwise

*/
    organism::simulateWeek();
    eatenThisWeek = 0;
    if(isAlive() == false){
        death();
    }
}

/*totalNeed - return need this week
double return need this week value

*/
double animal::stillNeed() const
{
    if(eatenThisWeek >= needThisWeek){
        return 0;
    }else{
        double DifferenceNeed = 0;
        DifferenceNeed = needThisWeek - eatenThisWeek;
        return DifferenceNeed;
    }
}

/*~animal - destructor for class anima;
Algorithm - set needThisWeek and eatenThisWeek to 0
*/
double animal::totalNeed() const
{
    return(needThisWeek);
}

animal::~animal()
{
	needThisWeek = 0;
    eatenThisWeek = 0;
}