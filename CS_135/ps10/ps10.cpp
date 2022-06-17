/*
	* Description: Sort the data based on eucDistance and manDistance
    introduce you to File I/O, functions(pass by value and reference), 
    structures, arrays of structure, sorting(bubble sort).
	* Input: based on pdf file (will have 14 files to read data)
	* Output: based on pdf file (will output 28 output files)
*/
/*
    In order to organize, I put all data files in data folder and output files in output folder
    So you might want to create these 2 folder "input" and "output" 
*/
#include <iostream>
#include <iomanip> // to manipulate output file
#include <string> // to use string function
#include <fstream> // to open and close file
using namespace std;

//structure for data record
//include data of x2, y2, manDist, eucDist, and label
struct Record{
    int x2;
    int y2;
    int manDist;
    double eucDist;
    string label;
};

//prototypes for the assignment
int openFile(ifstream&, string);
int readFile(ifstream&, Record data_array[25], string&, string&, string&);
void bubbleSorteucDist(Record data_array[], int);
void bubbleSortmanDist(Record data_array[], int);
void swap(Record&, Record&);

int main(){
    //declar variables to use in main function
    string DataFile, line1, line2, line3, eucFile, eucPrint, manFile, manPrint;
    int count;
    Record array[25];
    
    for(int i = 1; i < 15; i++){
        //because files have 2 different type so use if-else to format
        //eucPrint + manPrint to print it to the terminal
        //eucFile + manFile to output the files in the folder
        if(i <= 9){
            DataFile = string("input/Distances_Plane_00") + to_string(i) + string(".txt");
            eucFile = string("output/Sorted_eucDist_Plane_00") + to_string(i) + string(".txt");
            eucPrint = string("Sorted_eucDist_Plane_00") + to_string(i) + string(".txt");
            manFile = string("output/Sorted_manDist_Plane_00") + to_string(i) + string(".txt");
            manPrint = string("Sorted_manDist_Plane_00") + to_string(i) + string(".txt");
        }
        else{
            DataFile = string("input/Distances_Plane_0") + to_string(i) + string(".txt");
            eucFile = string("output/Sorted_eucDist_Plane_0") + to_string(i) + string(".txt");
            eucPrint = string("Sorted_eucDist_Plane_00") + to_string(i) + string(".txt");
            manFile = string("output/Sorted_manDist_Plane_0") + to_string(i) + string(".txt");
            manPrint = string("Sorted_manDist_Plane_00") + to_string(i) + string(".txt");
        }

        //open data file (14 files)
        ifstream input;
        openFile(input, DataFile);
        
        if(input.is_open()){
            //read data files
            count = readFile(input, array, line1, line2, line3);
            // because the function return total count

            //open and output eucDist files (14 files)
            ofstream eucOut;
            eucOut.open(eucFile);
            eucOut << line1 << endl;
            eucOut << line2 << endl;
            eucOut << line3 << endl;
            bubbleSorteucDist(array, count);
            for(int a = 0; a < count; a++){
                eucOut << left << setw(10) << array[a].x2 << left << setw(10) << array[a].y2
                       << left << setw(10) << array[a].manDist << left << setw(10) << array[a].eucDist
                       << left << setw(10) << array[a].label << endl;
            }
            //print to console after open and write all files
            cout << eucPrint + " by eucDist" << endl;

            eucOut.close();

            //open and output manDist files (14 files)
            ofstream manOut;
            manOut.open(manFile);

            manOut << line1 << endl;
            manOut << line2 << endl; 
            manOut << line3 << endl;
            bubbleSortmanDist(array, count);
            for(int a = 0; a < count; a++){
                manOut << left << setw(10) << array[a].x2 << left << setw(10) << array[a].y2
                       << left << setw(10) << array[a].manDist << left << setw(10) << array[a].eucDist
                       << left << setw(10) << array[a].label << endl;
            }
            //print to console after open and write all files
            cout << manPrint + " by manDist" << endl;

            manOut.close();
        }
    }

    return 0;
}

/*
	* openFile to open the file
	* parameters: ifstream of input and string name of input file
	* return value: -1 for true and 0 for fail
*/
int openFile(ifstream& inFile, string fileName){
    inFile.open(fileName);
    if(!inFile.is_open()){
        cout << "Error: File not found" << endl;
        return 0;
    }
    else{
        return -1;
    }
}

/*
	* readFile: read data from the file and put it into each type
	* parameters: ifstream input, Record struct data[25], string for line1, 2, 3
	* return value: return the total count of the file
*/
int readFile(ifstream& inFile, Record data_array[25], string& line1, string& line2, string& line3){
    int count = 0;
    Record value;

    if(inFile.is_open()){
        getline(inFile, line1);
        getline(inFile, line2);
        getline(inFile, line3);

        while(inFile.eof() == false){
            inFile >> value.x2 >> value.y2 >> value.manDist >> value.eucDist >> value.label;

            if(inFile.fail()){
                inFile.clear();
                inFile.ignore(100, '\n');
                break;
            }
            data_array[count] = value;
            count++;
        }
    }
    inFile.close();

    return count;
}

/*
	* BubbleSorteucDist: sort the euc Distance of the file from lowest to highest
	* parameters: Structure Record array name, int size
	* return value: void
*/
void bubbleSorteucDist(Record data_array[], int count){
    int i, j, temp = 0; 

	for (i = 0; i < count - 1; i++) {
		for (j = 0; j < count - i - 1; j++) {
			if (data_array[j].eucDist > data_array[j + 1].eucDist) {
				swap(data_array[j], data_array[j+1]);
			}
		}
	}
}

/*
	* BubbleSortmanDist: sort the man Distance of the file from lowest to highest
	* parameters: Structure Record array name, int size
	* return value: void
*/
void bubbleSortmanDist(Record data_array[], int count){
    int i, j, temp = 0; 

	for (i = 0; i < count - 1; i++) {
		for (j = 0; j < count - i - 1; j++) {
			if (data_array[j].manDist > data_array[j + 1].manDist) {
				swap(data_array[j], data_array[j+1]);
			}
		}
	}
}

/*
	* swap : swap the data from the file
	* parameters: Structure old Record , Structure new record
	* return value: void
*/
void swap(Record& oldStruct, Record& newStruct){
    Record temp;

    temp = oldStruct;
    oldStruct = newStruct;
    newStruct = temp;
}