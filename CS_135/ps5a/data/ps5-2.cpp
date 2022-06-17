/* 
   Assignment Number: Problem Set #5,
   Description: Calculating Distance from Airplanes to Multiple Airports */ 
#include <iostream>
#include <fstream> //to read and write file
#include <string> 
#include <cmath> //to calculate manDist and eucDist
#include <iomanip>
#include <stdlib.h>
using namespace std;

int main(int argc, char* argv[]){
    double x1, y1, x2 ,y2;
    double manDist, eucDist;
    string location, planenum;
    string file1, file2, out; 
//output messages based on number of arguments
    if(argc == 1){ 
        cout << "Usage: ./a.out dataFile queryFile outputFile" << endl;
        return 0;
    }
    else if(argc != 4){
        cout << "Error: Incorrect amount of command line arguments" << endl;
        return 0;
    }
    else if(argc == 4){
        file1 = argv[1];
        file2 = argv[2];
        out = argv[3];
    }
//using fstream to read/write file
    ifstream datafile;
    datafile.open(file1);
    ifstream queryfile;
    queryfile.open(file2);
    ofstream output;
    output.open(out);

//error if can't open file
    if(!datafile.is_open()){
        cout << "Error: Invalid data file extension" << endl;
        return 0;
    }
    if(!queryfile.is_open()){
        cout << "Error: Invalid query file extension" << endl;
        return 0;
    }
    if(!output.is_open()){
        cout << "Error: Can't open output file" << endl;
        return 0;
    }

   if(queryfile.is_open()){
        if(datafile.is_open()){
            while( !queryfile.eof()){ //read datafile and check error
                //take values from file1
                queryfile >> x1 >> y1 >> planenum;
                if(queryfile.fail() == true){
                    if(queryfile.eof() == false){
                        queryfile.clear();
                        queryfile.ignore(100 , '\n');
                        cout << "Error: Invalid x1 entry \n"
                             << "Error: Invalid y1 entry" << endl;
                    }
                }
                
                //output so that they wont be loop inside the second one
                output << left << setw(10) << "x1" << left << setw(10) << "y1" << left << setw(10) << "label" << endl;
                output << left << setw(10) << x1  << left << setw(10) << y1  << left << setw(10) << planenum  << endl;
                output << left << setw(10) << "manDist" << left << setw(10) << "eucDist" << left << setw(10) << "label" << endl; 
                
                while(datafile >> x2 >> y2 >> location){ //read queryfile and check error
                    //take values from file 2
                    if(datafile.fail()){
                        if(datafile.eof() == false){
                            datafile.clear();
                            datafile.ignore(100, '\n');
                            cout << "Error: Invalid x2 entry \n"
                                 << "Error: Invalid y2 entry" << endl;
                        }
                    }
                    // calculate manDist and eucDist
                    manDist = manDist = abs(x2 - x1) + abs(y2 - y1);
                    eucDist = eucDist = sqrt((pow((x2 - x1), 2)) + (pow((y2 - y1), 2)));
                    //write the results in output file
                    
                    output << left << setw(10) << setprecision(4) << manDist 
                           << left << setw(10) << setprecision(4) << eucDist << left << setw(10) << location << endl;
                    
                }
            
            datafile.clear(); //clear and start from begin to calculate again
            datafile.seekg(0, ios::beg);
            output << endl;  
   
        }     
        }
    }
    datafile.close();
    queryfile.close();
    output.close();
}
//./a.out data/AirportLocations.txt data/AirplaneLocations.txt output/Distances.txt