#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include "herbivore.h"
#include "plant.h"
#include "organism.h"
#include "randNum.h"

using namespace std;

const int ROWS = 5;
const int COLS = 5;
const int ACTIVITIES = 100;

void buildPondSimulator(ifstream&, organism***);
void simulateAWeek(organism***, randNum&);
void outputOrganism(organism*);
void clearSimulation(organism***);

double stringConvertDouble(string);
int stringConvertInt(string);

int main()
{
    organism *** pond;
    ifstream infile;
    string filename;
    randNum rN("RandomNums.txt");
    int weeks;

    //allocate the pond structure

    //allocate the amount of rows
    pond = new organism**[ROWS];

    //allocate the columns for each row
    for (int i = 0; i < ROWS; i++)
        pond[i] = new organism*[COLS];

    //This would be an empty pond initial so each cell is set to empty
    for (int i = 0; i < ROWS; i++)
        for (int j = 0; j < COLS; j++)
            pond[i][j] = NULL;

    //ask for pond file and re-prompt if not found
    do
    {
        cout << "Enter pond data file: ";
        cin >> filename;

        infile.open(filename.c_str());
    }
    while (!infile.is_open());
    
    //Time to build the simulation, reads the contents from the CSV file
    //and inserts objects into pond array
    buildPondSimulator(infile, pond);

    //Asks the user for the amount of weeks they wish to simulate
    //re-prompts if invalid input read
    cout << "Enter amount of weeks for the simulation: ";
    cin >> weeks;

    while (cin.fail() || weeks <= 0)
    {
        if (cin.fail())
        {
            cin.fail();
            cin.ignore(100, '\n');
        }
        cout << "Enter amount of weeks for the simulation: ";
        cin >> weeks;
    }

    //Simulates the amount of weeks, calls simulateAWeek function
    //weeks amount of times
    for (int i = 0; i < weeks; i++)
    {
        cout << "WEEK " << i + 1 << " RESULTS" << endl;
        simulateAWeek(pond, rN);
        cout << endl << endl;
    }

    cout << "Ending simulation" << endl;

    //destroy the simulation
    clearSimulation(pond);

    return 0;
}

/*buildPondSimulator- build a pond from the data file
ifstream infile - to open the input file
oragnism ***pond- array of pointer for the pond
return void
Algorithm- read all the data from the input file and parse them into each elements and convert them into desired values
then insert herbivore or plant object into pond based on if the organism type is fish or plant
by using new keyword and herbivore and plant constructors
Also, need to clean after each read in and new to prevent left over data

*/
void buildPondSimulator(ifstream& infile, organism *** pond)
{
    string line;
    string ORGANISM_TYPE;
    string SIZEstring, GROWTH_RATEstring;
    string X_COORDINATEstring, Y_COORDINATEstring;

    double SIZE, GROWTH_RATE;
    int X_COORDINATE, Y_COORDINATE;

    //read the file 
    while(!infile.eof()){
        getline(infile, line);
        stringstream s(line); //parse the line into different fields
        getline(s, ORGANISM_TYPE, ',');
        getline(s, SIZEstring, ',');
        getline(s, GROWTH_RATEstring, ',');
        getline(s, X_COORDINATEstring, ',');
        getline(s, Y_COORDINATEstring, ',');

        //convert fields into desire value
        SIZE = stringConvertDouble(SIZEstring);
        GROWTH_RATE = stringConvertDouble(GROWTH_RATEstring);
        X_COORDINATE = stringConvertInt(X_COORDINATEstring);
        Y_COORDINATE = stringConvertInt(Y_COORDINATEstring);

        if(ORGANISM_TYPE == "FISH"){
            // notes: it have x and y so when delete, need to delete both
            pond[X_COORDINATE][Y_COORDINATE] = new herbivore(SIZE, GROWTH_RATE, (SIZE * 0.1)); 
        }
        else if(ORGANISM_TYPE == "PLANT"){
            pond[X_COORDINATE][Y_COORDINATE] = new plant(SIZE, GROWTH_RATE);
        }
    }
    //clear all the stuff left over
    line.clear();
    SIZEstring.clear(), GROWTH_RATEstring.clear();
    X_COORDINATEstring.clear(), Y_COORDINATEstring.clear();
    SIZE = 0, GROWTH_RATE = 0;
    X_COORDINATE = 0, Y_COORDINATE = 0;

}

/*simulateAWeek - simulates 1 week of the pond simulator- simulate 100 activities
organism *** pond- array of pointer pond to assign activities into each objetc
randNum& rN - value to get random activities from rand function
return void
Algorithm- Get a random x1,y1,x2,y2 indices to investigates potential organism in the pond array
-use dyanmic cast to check for o1 and o2
-if they both NULL, then nothing happens
- if both point to plant then nothing
-if one of them is NULL and other is plant then nothing
if one is pointers is NULL and other points to herbivore, assign NULL to where herbivre object used to be and assign
herbivore object to where the NULL used to be
-if both point to herbivore onject then need to swap their positions in the pond array
-if one of pointers points to herbivore object and the other points to plant object, must calssed herbivore
object nivvle function and pass in plant object as the parameter (mayneed to deference, use arrow opertor or use dynamic cast)
then swap their positions in the pond array
-Once all 100 activities are simualted, call simulateWeek() function for each element. Check each obejct if it's still alvie and
not NULL. If no longer alive then allocate the object pond[][] and set it to NULL and call organism destructor
-Then call ouputOrganism() for each object in the pond

*/
void simulateAWeek(organism *** pond, randNum& rN)
{
    int X1 = 0, X2 = 0;
    int Y1 = 0, Y2 = 0;
    organism *o1, *o2;
    organism *temp; //temp

    for(int i = 0; i < ACTIVITIES; i++){
        X1 = (rN.getNextRand()) % 5; 
        Y1 = (rN.getNextRand()) % 5; 
        X2 = (rN.getNextRand()) % 5; 
        Y2 = (rN.getNextRand()) % 5; 

        o1 = pond[X1][Y1]; 
        o2 = pond[X2][Y2];
        
        if(o1 == NULL && o2 == NULL){
            continue;
        }
        if(dynamic_cast <plant *> (o1) && dynamic_cast <plant *> (o2)){
            continue;
        }
        if((o1 == NULL || o2 == NULL) && (dynamic_cast <plant *> (o1) || dynamic_cast <plant *>(o2))){
            continue;
        }
        if(o1 == NULL && dynamic_cast <herbivore *>(o2)){ //swap for step 7

            /*pond[X1][Y1] = pond[X2][Y2]; //method 1
            pond[X2][Y2] = NULL;*/

            pond[X1][Y1] = o2; 
            pond[X2][Y2] = NULL;
        }
        if(o2 == NULL && dynamic_cast <herbivore *>(o1)){ //swap for step 7

            pond[X2][Y2] = o1; 
            pond[X1][Y1] = NULL;
        }
        if(dynamic_cast <herbivore *> (o1) && dynamic_cast <herbivore *>(o2)){//step 8
            
            temp = o1; 
            pond[X1][Y1] = pond[X2][Y2]; 
            pond[X2][Y2] = temp;
        }
        if(dynamic_cast <herbivore *> (o1) && dynamic_cast <plant *>(o2)){//step 9
            
            dynamic_cast <herbivore *>(o1)->nibble(*dynamic_cast <plant *>(o2));
            temp = o1; 
            pond[X1][Y1] = pond[X2][Y2];
            pond[X2][Y2] = temp;
        }
        if(dynamic_cast <herbivore *> (o2) && dynamic_cast <plant *>(o1)){//step 9
            
            dynamic_cast <herbivore *>(o2)->nibble(*dynamic_cast <plant *>(o1));
            temp = o2;  
            pond[X2][Y2] = pond[X1][Y1];
            pond[X1][Y1] = temp; 
        }
    }
    
    for(int i = 0; i < ROWS; i++){ 
        for(int j = 0; j < COLS; j++){
            if(pond[i][j] !=  NULL){ //need to check for NULL
                pond[i][j]->simulateWeek(); 
                if(pond[i][j]->isAlive() == false){
                    pond[i][j]->~organism();
                    delete pond[i][j];
                    pond[i][j] = NULL; 
                }
                outputOrganism(pond[i][j]);
            }
        }
    }
}

/*outputOrganism - output the string/messages
organism *org- pass pointer by value
return void
Algorithm- output the string "fish with weight" or "plant with weight" depending on whether org points to an herbivore
or plant object and then output org-> getsize()

*/
void outputOrganism(organism * org)
{
    if(dynamic_cast <herbivore *> (org)){
        cout << "Fish With Weight " << org->getSize() << endl;
    }
    else if(dynamic_cast <plant *> (org)){
        cout << "Plant With Weight " << org->getSize() << endl;
    }
}

/*clearSimulation- dellocates all the objects in each pond[][] postition and deallocates the pointers as well
organism ***pond- array of pointer pond
return void
Algorithm- use nested loop to delete object and set pointer of object to NULL
-then delete cols of the array and set them to null
-then delete rows of the array  and set them to NULL

*/
void clearSimulation(organism *** pond)
{
    for(int i = 0; i < ROWS; i++){
        for(int j = 0; j < COLS; j++){
            delete pond[i][j]; //delete object
            pond[i][j] = NULL; //alway set them to NULL after delete to prevent dangling pointer
        }
        delete [] pond[i]; //need to do this here otherwise, dangling pointer
        //delete the row
        pond[i] = NULL;
    }
    delete [] pond; //delete the whole things
    pond = NULL; //extra
}

/* stringConvertDouble - converts a string to it's corresponding double value. Must use stringstream.
    string s - the string to be converted into double 
    return value - the double converted from the string

    Algorithm
        set up the stringstream variable to take value from the string and extract it into double value.
*/
double stringConvertDouble(string s){
    stringstream convert2x;
    double value;

    convert2x << s;
    convert2x >> value;
    return value;  
}

/* stringConvertInt - converts a string to it's corresponding int value. Must use stringstream.
    string s - the string to be converted into int 
    return value - the int converted from the string

    Algorithm
        set up the stringstream variable to take value from the string and extract it into int value.
*/
int stringConvertInt(string s){ 
    stringstream convert2x;
    int value;

    convert2x << s;
    convert2x >> value;
    return value;  
}