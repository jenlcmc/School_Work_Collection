/* 
   Description: Read 2 input file and determine amount of time to arrive destination.
   Required series of nested loop. Each type of plane have different speed. 
*/  
//NOTES: For the JAC, because airport file have 2 JAC so my code calculate the second one. 
//So JAC output not same. But other calculations and destinations are all same
#include <iostream>
#include <cmath> //to calculate
#include <string> // to use string 
#include <iomanip> //customize output
#include <fstream> // open and close file
using namespace std;

int main(){
    string choice;
    ifstream airplane;
    string Planefile, Portfile;
    ifstream airport;
    
    ofstream out;
    string outFile;
    
    int iterationCounter = 1, seconds;
    double x1, y1, x2, y2;
    string planeType, planeNum, destination, source;
    double eucDist, planeSpeed, days, hours, minutes;
    
    // using do, while loop to start again if choice is y/Y
    do{
        cout << "Please enter airplanes file: ";
        cin >> Planefile; //take input from the user 
    
        airplane.open(Planefile);
        // prompt again if file can't open
        //second condition to prevent type airport into airplane string
        while(!airplane.is_open() || Planefile == "AirportLocations.txt"){
            cin.clear();
            cin.ignore(100,'\n');
            cout << "Please enter airplanes file: ";
            cin >> Planefile;
            airplane.open(Planefile);
        }
        cout << endl;
    
        cout << "Please enter airport file: ";
        cin >> Portfile;
        // open and check file if it's open or not
        airport.open(Portfile);
        while (!airport.is_open() || Portfile != "AirportLocations.txt"){ 
            cin.clear();
            cin.ignore(100,'\n');
            cout << "Please enter airport file: ";
            cin >> Portfile;
            airport.open(Portfile);
        }
        cout << endl;
        //construct output file
        outFile = "output_" + to_string(iterationCounter) + ".txt";
        out.open(outFile);
        iterationCounter++; //add 1 = file num will be up 1 when choice = y/Y

        cout << endl;
        cout << "Ok, results are written into " << outFile << endl;
        cout << endl;

        //ask user if want to continue or not
        cout << endl;
        cout << "Do you wish to continue? (Y/N): ";
        cin >> choice;
        cout << endl;

        //if all files can open = get data + calculate
        if(airplane.is_open()){
            if(airport.is_open()){
                if(out.is_open()){
                    while(airplane >> x1 >> y1 >> planeNum >> planeType >> destination){
                        while(airport >> x2 >> y2 >> source){
                            
                            // if desti = source then calculate dist
                            if( destination == source){
                
                                //calculate based on plane type and speed
                                if( planeType == "A"){ 
                                    planeSpeed = 575;
                                }
                                if( planeType == "L"){
                                    planeSpeed = 90;
                                }
                                if( planeType == "P"){
                                    planeSpeed = 35;
                                }
                                if( planeType == "R"){ 
                                    planeSpeed = 200;
                                }
                                if( planeType == "W"){
                                    planeSpeed = 75;
                                }

                                eucDist = sqrt((pow((x1 - x2), 2)) + (pow((y1 - y2), 2)));
                                seconds = (eucDist / planeSpeed) * 3600;
                                days = seconds / (24 * 3600);
                                seconds = seconds % (24 * 3600);
                                hours = seconds /3600;
                                seconds = seconds % 3600;
                                minutes = seconds / 60;
                                seconds = seconds % 60;
                            }
                        } 
                        //clear and start read/get data again
                        airport.clear();
                        airport.seekg(ios::beg);
                        
                        // output based on condition 
                        if(days >= 1){
                            if(seconds <= 0){
                                out << planeNum << " arrives at " << destination << " in " 
                                << days << " day(s) " << hours << " hour(s) " 
                                << minutes << " minute(s) " << endl;
                            }
                            else if(hours <= 0){
                                out << planeNum << " arrives at " << destination << " in " 
                                << days << " day(s) " << minutes << " minute(s) " 
                                << seconds << " second(s) " << endl;
                            }
                            else{
                            out << planeNum << " arrives at " << destination << " in " 
                                << days << " day(s) " << hours << " hour(s) " 
                                << minutes << " minute(s) " << seconds << " second(s) " << endl;
                            }
                            
                        }
                        if(days <= 0){
                            if(hours <= 0){
                                out << planeNum << " arrives at "
                                    << destination << " in " << minutes << " minute(s) " 
                                    << seconds << " second(s) " << endl;
                            }
                            else if(minutes <= 0){
                                out << planeNum << " arrives at "
                                    << destination << " in " << seconds << " second(s) " << endl;
                            }
                            else{
                                out << planeNum << " arrives at " << destination 
                                    << " in " << hours << " hour(s) "
                                    << minutes << " minute(s) " << seconds << " second(s) " << endl;
                            }
                        }
                    }
                }
            }
        } 
        airport.close();
        airplane.close();
        out.close();

    }while(choice == "y" || choice == "Y");
    
    //if choice = n/N then output message and end program
    if(choice == "n" || choice == "N"){
    cout << endl;
    cout << "Great, all flight times are scheduled! Good day!\n" << endl;
    return 0;
    }
    return 0;
}