
//Class FileClass 

#ifndef H_fileInfo
#define H_fileInfo

#include <iostream>
#include <iomanip>
#include <fstream>
//#include <vector> //extra

#include "savingsAccount.h"
#include "checkingAccount.h"


using namespace std;

/**
 * @brief FileClass is a separate base class and deals with file INput/Output data- Constructors opens input file, savings output file, checkings output file 
 * 
 */
class FileClass
{

public:
    ifstream inFile;
    ofstream outSavingFile;
    ofstream outCheckingFile;
    bool fileError;

    /**
     * @brief Construct a new File Class:: File Class object
     * 
     */
    FileClass()
    {
        char file_name[100];
        char saving_file[] = "saving_account.csv";
        char checking_file[] = "checking_account.csv";
        
        fileError = false;
        
        cout << "Enter input File Name: " << endl;
        cin >> file_name;

        inFile.open(file_name, ios::in);

        while(inFile.fail()){
            inFile.clear();
            inFile.ignore(100, '\n');
            cout << "###########################################################" << endl;
            cout << "Error : Input file not present : " << file_name << endl;
            cout << "###########################################################" << endl;
            cout << "Enter input File Name: " << endl;
            cin >> file_name;
            inFile.open(file_name, ios::in);
        }
        

        outSavingFile.open(saving_file, ios::out);
        if (!outSavingFile.good())
        {
            fileError = true;
            cout << "Error : outSavingFile file not opening : " << saving_file << endl;
        }

        outCheckingFile.open(checking_file, ios::out);
        if (!outCheckingFile.good())
        {
            fileError = true;
            cout << "Error : outCheckingFile file not opening : " << checking_file << endl;
        }    
    }
    /**
     * @brief Destroy the File Class:: File Class object
     * 
     */
    ~FileClass()
    {
        inFile.close();
        outSavingFile.close();
        outCheckingFile.close();
    }

};

    //check documentation for each function description

    string makeStringUpper(string s);
    void readFile(ifstream &inFile, vector<checkingAccount> &Caccount, vector<savingsAccount> &Saccount, int &count);
    void writeFile(ofstream &savingFile, ofstream &checkingFile, vector<checkingAccount> &Caccount, vector<savingsAccount> &Saccount, int &count);
    bool openInputFile(ifstream &inFile);
    bool getNextField(string &line, int &index, string &subString);
    void saveFieldSavingAccount(int fieldNumber, string subString, savingsAccount &tempItem);
    void saveFieldCheckingAccount(int fieldNumber, string subString, checkingAccount &tempItem);
    double stringConvertDouble(string s);
    long int stringConvertInt(string s); //special
    int processMoney(vector<checkingAccount> &Caccount, vector<savingsAccount> &Saccount, bool deposit_f, bool withdraw_f);



#endif 