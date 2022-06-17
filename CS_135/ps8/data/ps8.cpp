/* 
   Assignment Number: Problem set 8,
   Description: Flight Fuel Usage. Introduce to 1D arrays and linear dearches of 1D arrays
   Learn how to use arrays (store data in multiple arrays, performing computation, searching infos)
   Will have 9 functions
*/
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <cmath>
using namespace std;

//part 1 functions prototype
void openFile(ifstream&, string);
void readFile(ifstream&, double[], double[]);

//part 2 functions prototype
double mySum(double[], int);
double mySum(double[], double[], int);
double average(double[], int);
double min(double[], int);
double max(double[], int);

//part 3 functions prototype
double slope(int, long, long, long, long);
double intercept(int, long, long, long, long);

//declar global var
string filename, outfile, header, sum;
ifstream datafile;
// declar var for problem set 4
double fuel, Miles, fuelAndMiles, fuelAndFuel;
double slopeAns, interceptAns;
int size, total;

int main(int argc, char* argv[]){
    //output message based on argc
    if(argc == 1){
        cout << "Usage: ./a.out FILENAME.txt" << endl;
        return 0;
    }
    else if(argc == 2){
        filename = argv[1];

        //if argc == 1 then use openFile function to open file and get data
        openFile(datafile, filename);
        datafile >> total;
        int Size = total;
        double gallon[Size], mile[Size];
        readFile(datafile, gallon, mile);

        //store 4 data into 2 arrays
        fuel = mySum(gallon,Size);
        Miles = mySum(mile, Size);
        fuelAndMiles = mySum(gallon, mile, Size);
        fuelAndFuel = mySum(gallon, gallon, Size);

        //store values of slope and intercept
        slopeAns = slope(Size, fuel, Miles, fuelAndMiles, fuelAndFuel);
        interceptAns = intercept(Size, fuel, Miles, fuelAndMiles, fuelAndFuel);
        
        // output the file 
        ofstream output;
        outfile = "output/Results.txt";
        output.open(outfile);
        output << "slope: " << setprecision(2) << slopeAns << '\n'
               << "intercept: " << setprecision(6) << interceptAns << '\n'
               << "average col 1: " << setprecision(6) << average(gallon, Size) << '\n'
               << "average col 2: " << setprecision(6) << average(mile, Size) << '\n'
               << "minX -> maxX: " << setprecision(5) << min(gallon, Size) 
               << " -> " << setprecision(5) << max(gallon,Size) << '\n'
               << "minY -> maxY: " << setprecision(5) << min(mile, Size) 
               << " -> " << setprecision(5) << max(mile,Size) << '\n';
    }
    else if(argc > 2){
        cout << "Error: Too many command line arguments" << endl;
        return 0;
    }

}

/*
** FUNCTION_IDENTIFIER: open the passed file name. If file is unable to open = error + terminated
* parameters: passed string filename
* return value: return void = none
*/
void openFile(ifstream& datafile, string fileName){
    datafile.open(fileName);
    if(!datafile.is_open()){
        cout << "Error: Invalid file extension" << endl;
        return;
    }
    else{}
}

/*
** FUNCTION_IDENTIFIER: read file inserting each column into each array.
if bad data, skip and overide with next row
* parameters: passed filename, array of gallon, array of mile
* return value: return void = none
*/
void readFile(ifstream& datafile, double gallons[], double miles[]){
    int size, count;
    string header, total;
    double col1, col2;
    int i = 0;
    //get total good count from 1st line
    datafile >> count;
    size = count;
    datafile >> header >> total;
    while(!datafile.eof()){
        datafile >>gallons[i];
        if(datafile.fail()){
            datafile.clear();
            datafile.ignore(100, '\n');
            cout << "Error: Invalid entry" << endl;
        }
        else{
            datafile >> miles[i];
            if(datafile.fail()){
                datafile.clear();
                datafile.ignore(100, '\n');
                cout << "Error: Invalid entry" << endl;
                continue;
            }
            else{
                i++;
            }
        }
    }
}

/*
** FUNCTION_IDENTIFIER: calculate the sum of the array
* parameters: passed name of the array and size of the array
* return value: return sum of the array
*/
double mySum(double value[], int size){
    double sum = 0;
    int i = 0;

    for(i = 0; i < size; i ++){
        sum += value[i];
    }
    return sum;
}

/*
** FUNCTION_IDENTIFIER: calculate sum that multiply each element of 1st to each element of 2nd
the sum the array.
* parameters: passed name array 1, name array 2, size of the array;
* return value: return sum of the calculation
*/
double mySum(double gallons[], double miles[], int size){
    int i;
    double sumMul[size];
    double final = 0;
    for(i = 0; i < size; i++){
        for(i = 0; i < size; i++){
            sumMul[i] = gallons[i] * miles[i];
            final += sumMul[i];
        }
    }
    return final;
}

/*
** FUNCTION_IDENTIFIER: calculate average of the array
* parameters: passed name of array, and size
* return value: return the average of the array
*/
double average(double value[], int size){
    int i;
    double sum = 0, average = 0;

    for(i = 0; i < size; i++){
        sum += value[i];
    }
    average = sum / size;
    return average;
}

/*
** FUNCTION_IDENTIFIER: sort the array and find the min of the array
* parameters: name of the array and size
* return value: the minimum value of the array
*/
double min(double value[], int size){
    int i;
    double firstValue = value[0];
    for(i = 0; i < size; i++){
        if(value[i] < firstValue){
            firstValue = value[i];
        }
    }
    return firstValue;
}   

/*
** FUNCTION_IDENTIFIER: sort and find max value of the array
* parameters: name of the array and size of the array
* return value: maximum value of the array
*/
double max(double value[], int size){
    int i, firstValue = value[0];
    for(i = 0; i < size; i++){
        if(value[i] > firstValue){
            firstValue = value[i];
        }
    }
    return firstValue;
}   

/*
** FUNCTION_IDENTIFIER: use equation to calculate slope based on char
x = fuel sum, y = mile sum, xy = fuel and mile sum, x2 = fuel and fuel sum
* parameters: count = size of the array, long type of x, y, xy, x2
use char to make the equation short
* return value: the value of the calculation slope
*/
double slope(int count, long x, long y, long xy, long x2){
    double slope = 0;
    // need to do this before put in equation
    long  secondX2 = x * x; // or pow(x,2)
    double numerator = (count * xy) - (x * y);
    double Denominator = (count * x2) - secondX2; 
    slope = numerator / Denominator;
    return slope;
}

/*
** FUNCTION_IDENTIFIER: use equation to calculate intercept based on char
x = fuel sum, y = mile sum, xy = fuel and mile sum, x2 = fuel and fuel sum
* parameters: count = size of the array, long type of x, y, xy, x2
use char to make the equation short
* return value: the value of the calculation intercept
*/
double intercept(int count, long x, long y, long xy, long x2){
    double intercept = 0;
    long  secondX2 = x * x; // need to do this before put in equation
    double numerator = (y * x2) - (x * xy);
    double denominator = ((count * x2) - secondX2); 
    intercept = numerator / denominator;
    return intercept;
}