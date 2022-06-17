//  CS 218 - Provided C++ program
//	This programs calls assembly language routines.

//  NOTE: To compile this program, and produce an object file
//	must use the "g++" compiler with the "-c" option.
//	Thus, the command "g++ -c main.c" will produce
//	an object file named "main.o" for linking.

//  Must ensure g++ compiler is installed:
//	sudo apt-get install g++

// ***************************************************************************

#include <cstdlib>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <iomanip>

using namespace std;

#define MAXLENGTH 500

#define SUCCESS 0
#define BADNUMBER 1
#define INPUTOVERFLOW 2
#define OUTOFRANGE 3
#define ENDOFINPUT 4

// ***************************************************************
//  Prototypes for external functions.
//	The "C" specifies to use the C/C++ style calling convention.

extern "C" int readB13Num(int *);
extern "C" void gnomeSort(int[], int);
extern "C" void basicStats(int[], int, int *, int *, int *, int *, int *);
extern "C" double corrCoefficient(int[], int[], int);

// ***************************************************************
//  Begin a basic C++ program.
//	Notes, does not use any objects.

int main()
{

// --------------------------------------------------------------------
//  Declare variables and simple display header
//	By default, C++ integers are doublewords (32-bits).

	string	bars;
	bars.append(50,'-');

	int	i, status, newNumber;
	int	xList[MAXLENGTH], yList[MAXLENGTH];
	int	len = 0;
	int	xMin, xMax, xMed, xSum, xAve;
	int	yMin, yMax, yMed, ySum, yAve;
	double	corCof;
	bool	endOfNumbers = false;
	bool	readX = true;

	cout << bars << endl;
	cout << "CS 218 - Assignment #9" << endl << endl;

// --------------------------------------------------------------------
//  Loops to read numbers from user.
//		read input from user.
//		must ensure that the both an X and Y value
//			are read from user
//		check return status code
//			if needed, display error message
//			else, store read value

	while (!endOfNumbers && len < MAXLENGTH) {

		if(readX)
			printf ("Enter X Value (base-13): " );
		else
			printf ("Enter Y Value (base-13): " );
		fflush(stdout);
		status = readB13Num(&newNumber);

		switch (status) {
			case SUCCESS:
				if(readX)
					xList[len] = newNumber;
				else
					yList[len++] = newNumber;
				readX = !readX;
				break;
			case BADNUMBER:
				cout << "Error, invalid number. ";
				cout << "Please re-enter." << endl;
				break;
			case INPUTOVERFLOW:
				cout << "Error, user input exceeded " <<
					"length. ";
				cout << "Please re-enter." << endl;
				break;
			case OUTOFRANGE:
				cout << "Error, number of out of range. ";
				cout << "Please re-enter." << endl;
				break;
			case ENDOFINPUT:
				if (readX)
					endOfNumbers = true;
				else
					cout << "Must enter a matching" <<
						" Y value (base-36)." << endl;
				break;
			default:
				cout << "Error, invalid return status. ";
				cout << "Program terminated" << endl;
				exit(EXIT_FAILURE);
				break;
		}
		if (len > MAXLENGTH)
			break;
	}

// --------------------------------------------------------------------
//  Ensure some numbers were read and, if so,
//		sort data, get stats, and display results.

	if (len <= 2) {
		cout << "Error, not enough numbers entered." << endl;
		cout << "Program terminated." << endl;
	} else {
		cout << bars << endl;
		cout << endl << "Program Results" << endl << endl;

		gnomeSort(xList, len);
		gnomeSort(yList, len);
		basicStats(xList, len, &xMin, &xMed, &xMax, &xSum, &xAve);
		basicStats(yList, len, &yMin, &yMed, &yMax, &ySum, &yAve);
		corCof = corrCoefficient(xList, yList, len);

		cout << "Sorted X List: " << endl;
		for ( i = 0; i < len; i++) {
			cout << xList[i] << "  ";
			if ( (i%10)==9 || i==(len-1) ) cout << endl;
		}
		cout << endl;
		cout << "   X Minimum =  " << setw(12) << xMin << endl;
		cout << "    X Median =  " << setw(12) << xMed << endl;
		cout << "   X Maximum =  " << setw(12) << xMax << endl;
		cout << "       X Sum =  " << setw(12) << xSum << endl;
		cout << "   X Average =  " << setw(12) << xAve << endl;

		cout << endl << "Sorted Y List: " << endl;
		for ( i = 0; i < len; i++) {
			cout << yList[i] << "  ";
			if ( (i%10)==9 || i==(len-1) ) cout << endl;
		}
		cout << endl;
		cout << "   Y Minimum =  " << setw(12) << yMin << endl;
		cout << "    Y Median =  " << setw(12) << yMed << endl;
		cout << "   Y Maximum =  " << setw(12) << yMax << endl;
		cout << "       Y Sum =  " << setw(12) << ySum << endl;
		cout << "   Y Average =  " << setw(12) << yAve << endl;

		cout << endl;
		cout << "Correlation " <<
			" Coefficient =  " << setprecision(15) << fixed
			<< corCof << endl;
		cout << endl;
	}

// --------------------------------------------------------------------
//  All done...

	return	EXIT_SUCCESS;
}
