/* 
   Description: 
   This problem set will introduce you to 2D arrays, how to iterate through them, 
   and how to search for information stored within them. 
   In this problem set, you will read data from a file into main memory, 
   write the data in main memory to a file, and learn how to process data contained within a 2D array.
*/

#include <iomanip> // to manipulate the output
#include <fstream> // to get data and output file
#include <cmath> // to calculate
#include <iostream>
#include <string>
using namespace std;

//global const
const int rows = 22;
const int cols = 6;

//part 1 prototypes of functions
void openFile(ifstream&, string);
void openFile(ofstream&, string);
void readFile(ifstream&, string[], double[][cols]);
void print(ofstream&, string[]);
void print(ofstream&, double[][cols], int);
void print(ofstream&, double [][rows], int);

//part 2 prototypes of functions
void transpose(double[][cols], double[][rows]);
void transpose(double[][rows], double[][cols]);
void add(double[][cols], double[][cols], double[][cols]);
void add(double[][rows], double[][rows], double[][rows]);
void subtract(double[][cols], double[][cols], double[][cols]);
void subtract(double[][rows], double[][rows], double[][rows]);
void multiply(double[][cols], double[][rows], double[][rows]);
void multiply(double[][rows], double[][cols], double[][cols]);

int main(int argc, char* argv[]){
    // declar var to use inside main
    ifstream datafile;
    ofstream outfile;
    string filename, outname, header[cols];
    //declar array for get data and transpose
    double array[rows][cols], resultArray[rows][cols];
    double trans[cols][rows], resultTrans[cols][rows];
    double trans2[rows][cols];

    //declare array for calculation
    double multi1[rows][rows], multi2[cols][cols];
    double firstFirst[rows][rows], secondSecond[cols][cols];
    double plusSubtract1[rows][cols], plusSubtract2[cols][rows];
    double plusSubtractMul1[rows][rows], plusSubtractMul2[cols][cols];
    
    if(argc == 1){ // prompt if argc == 1
        cout << "Usage: ./a.out dataFile" << endl;
    }
    else if( argc == 2){ //call all funtions if argc = 2
        filename = argv[1];

        openFile(datafile, filename);
        openFile(outfile, outname);
        readFile(datafile, header, array);
        print(outfile, header);
        outfile << endl;

        outfile << "Original File (X)" << endl;
        print(outfile, array, rows);
        outfile << endl;

        outfile << "Transpose of File (X')" << endl;
        transpose(array, trans);
        print(outfile, trans, cols);
        outfile << endl;

        outfile << "Transpose of X' (X'')" << endl;
        transpose(trans, trans2);
        print(outfile, trans2, rows);
        outfile << endl;

        outfile << "Product of XX'" << endl;
        multiply(array, trans, multi1);
        print(outfile, multi1, rows);
        outfile << endl;

        outfile << "Product of X'X" << endl;
        multiply(trans, array, multi2);
        print(outfile, multi2, cols);
        outfile << endl;

        outfile << "Result of X + X" << endl;
        add(array, array, resultArray);
        print(outfile, resultArray, rows);
        outfile << endl;

        outfile << "Result of X' + X'" << endl;
        add(trans, trans, resultTrans);
        print(outfile, resultTrans, cols);
        outfile << endl;

        // dont need these anymore
        //outfile << "Result of Mult1 + Mult1" << endl;
        //add(rows, multi1, multi1, firstFirst);
        //print(outfile, firstFirst, rows);
        //outfile << endl;

        // dont need these anymore
        //outfile << "Result of Mult2 + Mult2" << endl;
        //add(cols, multi2, multi2, secondSecond);
        //print(outfile, secondSecond, cols);
        //outfile << endl;

        outfile << "Result of (X + X) - X" << endl;
        subtract(resultArray, array, plusSubtract1);
        print(outfile, plusSubtract1, rows);
        outfile << endl;

        outfile << "Result of (X' + X') - X'" << endl;
        subtract(resultTrans, trans, plusSubtract2);
        print(outfile, plusSubtract2, cols);
        outfile << endl;

        // dont need these anymore
        //outfile << "Result of (Mult1 + Mult1) - Mult1" << endl;
        //subtract(rows, firstFirst, multi1, plusSubtractMul1);
        //print(outfile, plusSubtractMul1, rows);
        //outfile << endl;

        // do not need these anymore
        //outfile << "Result of (Mult2 + Mult2) - Mult2" << endl;
        //subtract(cols, secondSecond, multi2, plusSubtractMul2);
        //print(outfile, plusSubtractMul2, cols);
        //outfile << endl;

    }
    else if(argc > 2){
        cout << "Error: Too many command line arguments" << endl;
    }
    return 0;
}

/*
** FUNCTION_IDENTIFIER: open file from command line argument
* parameters: ifstream datafile, string name of file
* return value: return none (void)
*/
void openFile(ifstream& inFile, string inFileName){
    inFile.open(inFileName);
    if(inFile.is_open() == false){
        cout << "Error: Invalid file extension" << endl;
        return;
    }
}

/*
** FUNCTION_IDENTIFIER: open  output file to put all data and calculations in
* parameters: ofstream output, string name of output file
* return value: return none (void)
*/
void openFile(ofstream& outputFile, string outName){
    outName = "output/Output.txt";
    outputFile.open(outName);
    if(outputFile.is_open() == false){
        cout << "Error: Can't open. Create folder name output first" << endl;
        return;
    }
}

/*
** FUNCTION_IDENTIFIER: read all data from the file and put it into 2 arrays
* parameters: ifstream datafile, string array for the header, double array for data
* return value: return none (void)
*/
void readFile(ifstream& inFile, string header[], double data[][cols]){
    int i = 0, j = 0, a = 0;
    //for header
    for(a = 0; a < cols; a++){
        inFile >> header[a];
    }
    //for data
    for(i = 0; i < rows; i++){
        for(j = 0; j < cols; j++){
            inFile >> data[i][j];   
        }
    }
}

/*
** FUNCTION_IDENTIFIER: print the header array to output file
* parameters: ofstream output, string array of the header
* return value: return none (void)
*/
void print(ofstream& output, string header[]){
    int i = 0;
    if(output.is_open()){
        output << "Headers" << endl;
        for(i = 0; i < cols; i++ ){
            output <<  header[i] << ", ";
        }
        output << endl;
    }
}

/*
** FUNCTION_IDENTIFIER: output passed 2d array of doubles with cols amount of cols of data
and any amount of rows of data to the passed output file
* parameters: ofstream output, double pass data 2d array, int size of rows
* return value: return none (void)
*/
void print(ofstream& output, double data[][cols], int size){
    if(output.is_open()){
        for(int i = 0; i < size; i++){
            for(int j = 0; j < cols; j++){
                output << left << setw(13) << data[i][j];
            }
            output << endl;
        }
    }
}

/*
** FUNCTION_IDENTIFIER: output passed 2d array of doubles with rows amount of columns of data
and any amount of rows of data to the passed output file
* parameters: ofstream output, double pass data 2d array, int size of rows
* return value: return none (void)
*/
void print(ofstream& output, double data[][rows], int size){
    if(output.is_open()){
        for(int i = 0; i < size; i++){
            for(int j = 0; j < rows; j++){
                output << left << setw(13) << data[i][j];
            }
            output << endl;
        }
    }
}

/*
** FUNCTION_IDENTIFIER: transpose m x 22 to 22 x m matrix
* parameters: double 2d data array , double 2d transpose array
* return value: return none (void)
*/
void transpose(double data[][cols], double trans[][rows]){
    for(int i = 0; i < rows; i++){
        for(int j = 0; j < cols; j++){
            trans[j][i] = data[i][j];
        }
    }
}

/*
** FUNCTION_IDENTIFIER: transpose m x 6 to 6 x m matrix
* parameters: double 2d data array , double 2d transpose array
* return value: return none (void)
*/
void transpose(double data[][rows], double trans[][cols]){
    for(int i = 0; i < cols; i++){
        for(int j = 0; j < rows; j++){
            trans[j][i] = data[i][j];
        }
    }
}

/*
** FUNCTION_IDENTIFIER: add m x 22 to m x 22 matrix
* parameters: int size of rows, double 2d data array , double 2d 2d data2 array, double results 2d array
* return value: return none (void)
*/
void add(double data1[][cols], double data2[][cols], double resultsAdd1[][cols]){
    for(int i = 0; i < rows; i++){
        for(int j = 0; j < cols; j++){
            resultsAdd1[i][j] = data1[i][j] + data2[i][j];
        }
    }
}

/*
** FUNCTION_IDENTIFIER: add m x 6 to m x 6 matrix
* parameters: int size of rows, double 2d data array , double 2d 2d data2 array, double results 2d array
* return value: return none (void)
*/
void add(double data1[][rows], double data2[][rows], double resultsAdd2[][rows]){
    for(int i = 0; i < cols; i++){
        for(int j = 0; j < rows; j++){
            resultsAdd2[i][j] = data1[i][j] + data2[i][j];
        }
    }
}

/*
** FUNCTION_IDENTIFIER: subtract m x 6 to m x 6 matrix
* parameters: int size of rows, double 2d data array , double 2d 2d data2 array, double results 2d array
* return value: return none (void)
*/
void subtract(double data1[][cols], double data2[][cols], double resultsSub1[][cols]){
    for(int i = 0; i < rows; i++){
        for(int j = 0; j < cols; j++){
            resultsSub1[i][j] = data1[i][j] - data2[i][j];
        }
    }
}

/*
** FUNCTION_IDENTIFIER: subtract m x 6 to m x 6 matrix
* parameters: int size of rows, double 2d data array , double 2d 2d data2 array, double results 2d array
* return value: return none (void)
*/
void subtract(double data1[][rows], double data2[][rows], double resultsSub2[][rows]){
    for(int i = 0; i < cols; i++){
        for(int j = 0; j < rows; j++){
            resultsSub2[i][j] = data1[i][j] - data2[i][j];
        }
    }
}

/*
** FUNCTION_IDENTIFIER: multiply m x 22 to 22 x n matrix
* parameters: int size of rows, double 2d data array , double 2d 2d data2 array, double results 2d array
* return value: return none (void)
*/
void multiply(double data1[][cols], double data2[][rows], double resultsMul1[][rows]){
    for(int i = 0; i < rows; i++){
        for(int j = 0; j < rows; j++){
            resultsMul1[i][j] = 0;
            for(int a = 0; a < cols; a++){
                resultsMul1[i][j] += data1[i][a] * data2[a][j];
            }
        }
    }
}

/*
** FUNCTION_IDENTIFIER: multiply m x 6 to 6 x n matrix
* parameters: int size of rows, double 2d data array , double 2d 2d data2 array, double results 2d array
* return value: return none (void)
*/
void multiply(double data1[][rows], double data2[][cols], double resultsMul2[][cols]){
    for(int i = 0; i < cols; i++){
        for(int j = 0; j < cols; j++){
            resultsMul2[i][j] = 0;
            for(int a = 0; a < rows; a++){
                resultsMul2[i][j] += data1[i][a] * data2[a][j];
            }
        }
    }
}
