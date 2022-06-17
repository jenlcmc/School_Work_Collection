#include <iostream>
#include <iomanip>
using namespace std;

// Prints the number of balloons required to lift the given weight
extern "C" void printBalloonsRequired(double weight, double diameter, double balloonCount)
{
	cout << "In order to lift " << weight << " pounds, ";
	cout << balloonCount << " balloons " << diameter << " feet wide will be required.\n";
}