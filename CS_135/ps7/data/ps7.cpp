/* ,
   Assignment Number: Problem Set 7,
   Description: Calculating Distance From Airplanes To Multiple Airports.
   Need to have 3 functions,  srtring getFilePath(string) = if argc == 1;
   double manhhattanDist(int, int, int, int), double euclideanDistance(int, int, int, int). 
   Either choose output function getfilepath ./a.out or using command line arguments
   Output will be 14 different files based on Plane Numbers
*/  

#include <iostream>
#include <string> 
#include <iomanip> // to customize output
#include <cmath> //to calculate Dist
#include <fstream> //to open and close file
using namespace std;

//protypes of functions
string getFilePath(string); 
double manhattanDist(int, int, int, int);
double euclideanDIst(int, int, int, int);

//declar variables for using and modifiy files
string datafile, queryfile, filename;
string outfile, countPlane;
string file1, file2;

//declar vars to use for calculation
int x, y, x2, y2;
double manResult, eucResult;
string planeNum, destination;

int main(int argc, char* argv[]){
    if(argc == 1){ //if argc == 1 then call getFilePath function to get file path
        getFilePath(filename);
        datafile = file1;
        queryfile = file2;
        
    }
    else if(argc == 3){
        datafile = argv[1];
        queryfile = argv[2];
    }
    else if(argc != 3 || argc != 1){
        cout << "Error: Incorrect amount of command line arguments" << endl;
        return 0;
    }
    
    //open input files
    ifstream data;
    data.open(datafile);
    ifstream query; 
    query.open(queryfile);
    
    //output error if can't open input file
    if(!data.is_open()){
        cout << "Error: Unable to open the data file" << endl;
        return 0;
    }
    if(!query.is_open()){
        cout << "Error: Unable to open the query file" << endl;
        return 0;
    }

    if(data.is_open()){
        if(query.is_open()){
             while(!query.eof()){ //if not end of file then get data from query file Airplane
                query >> x >> y >> planeNum;
                if(query.fail() == true){
                    if(query.eof() == false){ //check for error
                        query.clear();
                        query.ignore(100 , '\n');
                        cout << "Error: Invalid point in query file" << endl;
                    }
                }
                // modify output file and open 
                countPlane = planeNum;
                if(datafile == "ErrorData.txt" && queryfile == "ErrorQuery.txt"){
                    outfile = "Distance_error_check.txt";
                }
                else{
                outfile = "Distance_" +  countPlane;
                }
                ofstream out;
                out.open(outfile);
                
                //customize the output file
                out << left << setw(10) << "x1" << left << setw(10) << "y1"
                    << left << setw(10) << "label" << endl;
                out << left << setw(10) << x << left << setw(10) << y
                    << left << setw(10) << planeNum << endl;
                out << left << setw(10) << "x2" << left << setw(10) << "y2"
                    << left << setw(10) << "manDist" << left << setw(10) << "eucDist"
                    << left << setw(10) << "label" << endl;

                while(data >> x2 >> y2 >> destination){ //get data from data file Airport
                    if(data.fail()){
                        if(data.eof() == false){ //check error
                            data.clear();
                            data.ignore(100, '\n');
                            cout << "Error: Invalid point in data file" << endl;
                        }
                    }

                    //call function to calculate Dist
                    manResult = manhattanDist(x, y, x2, y2);
                    eucResult = euclideanDIst(x, y, x2, y2);

                    //customize out for calculation
                    out << left << setw(10) << x2 << left << setw(10) << y2
                        << left << setw(10) << setprecision(4) << manResult 
                        << left << setw(10) << setprecision(4) << eucResult
                        << left << setw(10) << destination << endl;
                        
                } // clear and read again from beginning
                data.clear();
                data.seekg(0, ios::beg); 
            }
        }
    } 
    data.close();
    query.close();
}

/* 
Function Identifier: string getFilePath(string filename)
desctiption: prompt and get the file path from the user
parameter: pass string name of file
return value: return the name of file for data file and query file
*/
string getFilePath(string fileName){
    cout << "Enter a data file path" << endl;
    cout << "**";
    cin >> filename;
    file1 = filename;
    cout << "Enter a query file path" << endl;
    cout << "**";
    cin >> filename;
    file2 = filename;
    

    return file1;
    return file2;
    
} 

/* 
Function Identifier: double manhattanDist(int x, int y, int x2, int y2)
desctiption: get data from data and query file under x1, y1, x2, y2 and calculate
parameter: pass int value of x1, y1, x2, y2
return value: return the result of manDist calculation
*/
double manhattanDist(int x, int y, int x2, int y2){
    double manDist = abs(x2 - x) + abs(y2 - y);
    return manDist;
}

/* 
Function Identifier: double euclideanDIst(int x, int y, int x2, int y2)
desctiption: get data from data and query file under x1, y1, x2, y2 and calculate
parameter: pass int value of x1, y1, x2, y2
return value: return the result of eucDist calculation
*/
double euclideanDIst(int x, int y, int x2, int y2){
    double eucDist = sqrt((pow((x2 - x), 2)) + (pow((y2 - y), 2)));
    return eucDist; 
}

