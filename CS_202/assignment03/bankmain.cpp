
#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
#include <vector>

#include "savingsAccount.h"
#include "checkingAccount.h"
#include "fileOperation.h"

using namespace std;

int main()
{
    int count = 0;
    vector<checkingAccount> Caccounts;
    vector<savingsAccount> Saccounts;
    FileClass fd;
    char input;
   

    if(fd.fileError == true)
    {
        return -1;
    }

    readFile(fd.inFile, Caccounts, Saccounts, count);
    // fileobj.readFile(fd.inFile, Caccounts, Saccounts, count);


    do
    {
        cout << "Main Menu\n";
        cout << "Please make your selection\n";
        cout << "D - Deposit money\n";
        cout << "W - Withdraw money\n";
        cout << "Q - Quit\n";
        cout << "Selection: " << endl;;
        cin >> input;


        switch (input)
        {
        case 'd':
        case 'D':
            processMoney(Caccounts, Saccounts, true, false);
        // fileobj.processMoney(Caccounts, Saccounts, true, false);
            
            break;
        case 'w':
        case 'W':
            processMoney(Caccounts, Saccounts, false, true);
        // fileobj.processMoney(Caccounts, Saccounts, false, true);
            break;
        case 'q':
        case 'Q':
            writeFile(fd.outSavingFile, fd.outCheckingFile, Caccounts, Saccounts, count);
        // fileobj.writeFile(fd.outSavingFile, fd.outCheckingFile, Caccounts, Saccounts, count);
            cout << "Goodbye!"<<endl;
            break;
        default:

            cout << "Main Menu\n";
            cout << "Please make your selection\n";
            cout << "D - Deposit money\n";
            cout << "W - Withdraw money\n";
            cout << "Q - Quit\n";
            cout << "\nSelection: " << endl;
            cin >> input;
            
            break;

        }
    } while (input != 'q' && input != 'Q');

    return 0;
}