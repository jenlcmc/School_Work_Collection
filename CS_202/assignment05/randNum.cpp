#include "randNum.h"
#include <string>
using namespace std;

/*randNum - constructor that will open the flile

*/
randNum::randNum(string filename)
{
    infile.open(filename.c_str());
}

/*getNextRand - returns the next random number from the file
Algorithm- take data from the file and return it
*/
int randNum::getNextRand()
{
    int x;

    infile >> x;

    return x;
}