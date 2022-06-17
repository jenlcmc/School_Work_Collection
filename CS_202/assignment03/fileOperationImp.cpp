

// include library and header file for implement file
#include <sstream>
#include <vector>
#include "fileOperation.h"

/* makeStringUpper - convert the passed string to upper case and returns it. Use toupper() to do
    string s - string to be converted into double
    return value - double converted from the string

    Algorithm
        Use for loop to loop through the string and then convert it into upper using toupper()
        function.
*/
string makeStringUpper(string s)
{
    string value;
    for (unsigned int i = 0; i < s.length(); i++)
    {
        value += toupper(s[i]);
    }
    return value;
}

/* readFile - uses the previously opened filestram to read in the data from the file. USe getline() to read
    data and use '\n' as terminating character. Use saveField() to set the corresponding value in tge temporary
    record as the line ead and field are parsed. ONce parsing line done, temporary records is filled, use push_back()
    to add temporary objects to vectors depend on account types . Then reset
    all values in temporary to 0 before reusing.
    Use counter of the number of records read to outputting.
    ifstream inFile - already open file to be read
    vector<checkingAccount> &Caccount, - vector to hold pass checking accounts
    vector<savingsAccount> &Saccount - vector to hold pass saving accounts
    int& count - the number of records read
    return void

    ALgorithms
        use getline() to read the line into a string. Use boolean and find function to
        determine if the line is saving or checking account. Then check for eof() use while loop.
        Set index and fieldNunmber to 0. Then call getNextField() depend on the account types
        and on the string read in 1st step,
        passing index, a string to receive the field. Then use saveField() to store the data in
        temporary struct of type AISType(use fieldNumber to determince which field gets the data).
        Increment fieldNUmber and loop back to getNextField() using for loop until entire string has
        been processed. Add the temporary class object depend on account type holding data to vector using push_back().
        Then reset fieldNumber and index to 0 and loop back to first until eof()
*/
void readFile(ifstream &inFile, vector<checkingAccount> &Caccount, vector<savingsAccount> &Saccount, int &count)
{
    string line;
    string nextStr;
    string fileName;
    checkingAccount temporaryChecking;
    savingsAccount tempSaving;
    int index, fieldNumber;

    while (!inFile.eof())
    {
        getline(inFile, line, '\n');
        index = 0, fieldNumber = 0;
        count++;
        bool saving = false;
        bool checking = false;

        if (line.find("Saving"))
        {
            saving = true;
        }
        if (line.find("Checking"))
        {
            checking = true;
        }

        for (int i = 0; i < 10; ++i)
        { // fix
            getNextField(line, index, nextStr);
            if (saving == false)
            {
                saveFieldSavingAccount(fieldNumber, nextStr, tempSaving);
            }
            if (checking == false)
            {
                saveFieldCheckingAccount(fieldNumber, nextStr, temporaryChecking);
            }
            fieldNumber++;
        }

        if (checking == false)
        {
            Caccount.push_back(temporaryChecking);
        }
        if (saving == false)
        {
            Saccount.push_back(tempSaving);
        }
        index = 0, fieldNumber = 0;

        char eraseLine[] = {'\r', 27, '[', '1', 'K'};

        if ((count % 100000) == 0)
        {
            cout << eraseLine << count;
            cout.flush();
        }
    }
}

/*void writeFile- write all the data read into new csv files. One for saving and one for checking accounts
    ofstream &savingFile - output file stream variable for the file to be opened
    ofstream &checkingFile -output file stream variable for the file to be opened
    vector<checkingAccount> &Caccount - vector type is used to save all fields of checking accountdata
    vector<savingsAccount> &Saccount- vector type is used to save all fields of saving accountdata
    int &count - This count is the number of accounts in the bankData.csv

    Algorithm- check if the file is open or not. If open, then use for loop to loop through the vector and then
    write all result into new csv file.
*/
void writeFile(ofstream &savingFile, ofstream &checkingFile, vector<checkingAccount> &Caccount, vector<savingsAccount> &Saccount, int &count)
{
    count = 0;
    if (checkingFile.is_open())
    {
        for (unsigned int i = 0; i < Caccount.size(); i++)
        {
            checkingFile << Caccount[i].getAccountType() << "," << Caccount[i].getAccountNumber() << "," << Caccount[i].getFirstName() << ","
                         << Caccount[i].getLastName() << "," << Caccount[i].getCompanyName() << "," << Caccount[i].getAddress() << ","
                         << Caccount[i].getCity() << "," << Caccount[i].getPhone1() << "," << Caccount[i].getPhone2() << "," << Caccount[i].getBalance() << "\n";
        }
    }

    if (savingFile.is_open())
    {
        for (unsigned int i = 0; i < Saccount.size(); i++)
        {
            savingFile << Saccount[i].getAccountType() << "," << Saccount[i].getAccountNumber() << "," << Saccount[i].getFirstName() << ","
                       << Saccount[i].getLastName() << "," << Saccount[i].getCompanyName() << "," << Saccount[i].getAddress() << ","
                       << Saccount[i].getCity() << "," << Saccount[i].getPhone1() << "," << Saccount[i].getPhone2() << "," << Saccount[i].getBalance() << "\n";
        }
    }
}

/* openInputFile - Function prompt the user for the name of the csv file to open. IF user enter (q/Q)
    function should return false. For any other, ir will return true. Function will verify that the file
    is opened correctly. If not, output the error and re=prompt the user. If file open correctly, return true
    ifstream& infile - file stream for the file to be opened

    Algorithm
        prompt the user to enter the file name by using cin. Then check user's choice. If (q/Q), return false
        if not, recheck it again and re-prompt the user by using while loop. Inside the loop, it will clear
        and ignore previous characters. If the user choices (q/Q) the stop. Else, it will open the file
*/
bool openInputFile(ifstream &inFile)
{
    // prompt the user and take the file name
    string fileName;
    cout << "Enter input File Name / (q-quit) : ";
    cin >> fileName;

    // if q/Q then terminate program
    if (fileName == "q" || fileName == "Q")
    {
        return false;
    }
    else
    { // if else then open
        inFile.open(fileName);

        // verify that the file opened correctly
        while (inFile.fail())
        {
            inFile.clear();
            inFile.ignore(100, '\n');
            cout << "File name incorrect. Please enter file name again. (q/Q) to quit: ";
            cin >> fileName;
            if (fileName == "q" || fileName == "Q")
                return false;
            else
                inFile.open(fileName);
        }
        return true;
    }
}

/* getNextField - bool function uses previously opened filestream to read data starting from the index.
    Then find next string which is upto comma or newline. Fields are seperate by commas. If found,
    save to subString. Comma s will be skipped. Index value will be update as line is processed.
    When function returns, index point to next character to be processed, and will be used as starting point
    for next call function.Can't use .find()
    string &line - line of data read from the file that needs to be parsed
    int &index - current starting position of the aprsing. 1st time, index = 0.
        Will update before returning
    string &subString - the parsed string
    return true or false depend on if there is still have data or not

    Algorithm
        clear the substring before using while loop to run with condition (if it's not the
        end of string and line position not equal comma). Inside while loop, save the read line to the
        subString. Then increment index to pass the next comma and getting ready for next call.
        test length to index to see if there is more data in the string or not
*/
bool getNextField(string &line, int &index, string &subString)
{
    subString.clear(); // clear string before call it again
    // while not the end of the string length and not have comma or new line
    while (static_cast<int>(line.length()) != index && line[index] != ',')
    {
        subString += line[index]; // add data
        index++;
    }
    index++;

    if (static_cast<int>(line.length()) <= index)
        return false;
    else
        return true;
}

/* saveField - save subString into fieldNumber in the record passed tempItem. SubString will be converted
    to a double depending on fieldNumber. Function will use stringConvert() to perform conversion
    from string to double. Error will be ouput if unknown field number
    int fieldNumber - the number of the field, start at 0
    string subString - value to be saved in the field, may require converse to double
    savingsAccount &tempItem - the record(savings account) to which the field will be added
    return number match with conditions by switch statement

    Algorithm
        using fieldNumber and switch statement to consider which field to save subString into
        If subString is string then use stringConvertDouble() to convert into double for
        account balance and stringConvertInt() for account number and phone numbers
        Default use to ouput error
*/
void saveFieldSavingAccount(int fieldNumber, string subString, savingsAccount &tempItem)
{

    switch (fieldNumber)
    {
    case 0:
        tempItem.setAccountType(subString);
        break;
    case 1:
        tempItem.setAccountNumber(stringConvertInt(subString));
        break;
    case 2:
        tempItem.setFirstName(subString);
        break;
    case 3:
        tempItem.setLastName(subString);
        break;
    case 4:
        tempItem.setCompanyName(subString);
        break;
    case 5:
        tempItem.setAddress(subString);
        break;
    case 6:
        tempItem.setCity(subString);
        break;
    case 7:
        tempItem.setPhone1(stringConvertInt(subString));
        break;
    case 8:
        tempItem.setPhone2(stringConvertInt(subString));
        break;
    case 9:
        tempItem.setBalance(stringConvertDouble(subString));
        break;
    default:
        cout << "Error: Unknow field number" << endl;
        break;
    }
}

/* saveField - save subString into fieldNumber in the record passed tempItem. SubString will be converted
    to a double depending on fieldNumber. Function will use stringConvert() to perform conversion
    from string to double. Error will be ouput if unknown field number
    int fieldNumber - the number of the field, start at 0
    string subString - value to be saved in the field, may require converse to double
    checkingAccount &tempItem- the record(checking account) to which the field will be added
    return number match with conditions by switch statement

    Algorithm
        using fieldNumber and switch statement to consider which field to save subString into
        If subString is string then use stringConvertDouble() to convert into double for
        account balance and stringConvertInt() for account number and phone numbers
        Default use to ouput error
*/
void saveFieldCheckingAccount(int fieldNumber, string subString, checkingAccount &tempItem)
{

    switch (fieldNumber)
    {
    case 0:
        tempItem.setAccountType(subString);
        break;
    case 1:
        tempItem.setAccountNumber(stringConvertInt(subString));
        break;
    case 2:
        tempItem.setFirstName(subString);
        break;
    case 3:
        tempItem.setLastName(subString);
        break;
    case 4:
        tempItem.setCompanyName(subString);
        break;
    case 5:
        tempItem.setAddress(subString);
        break;
    case 6:
        tempItem.setCity(subString);
        break;
    case 7:
        tempItem.setPhone1(stringConvertInt(subString));
        break;
    case 8:
        tempItem.setPhone2(stringConvertInt(subString));
        break;
    case 9:
        tempItem.setBalance(stringConvertDouble(subString));
        break;
    default:
        cout << "Error: Unknow field number" << endl;
        break;
    }
}

/* stringConvert - converts a string to it's corresponding double value. Must use stringstream.
    string s - the string to be converted into double
    return value - the double converted from the string

    Algorithm
        set up the stringstream variable to take value from the string and extract it into double value.
*/
double stringConvertDouble(string s)
{
    stringstream convert2x;
    double value;

    convert2x << s;
    convert2x >> value;
    return value;
}

/* stringConvert - converts a string to it's corresponding long int value. Must use stringstream.
    string s - the string to be converted into double
    return value - the long int converted from the string

    Algorithm
        set up the stringstream variable to take value from the string and extract it into long int value.
*/
long int stringConvertInt(string s)
{
    stringstream convert2x;
    long int value;

    convert2x << s;
    convert2x >> value;
    return value;
}

/*int processMoney- prompt the menu for the user to choice. To deposit or withdraw money through
    saving or checking account by search through vector database.
    vector<checkingAccount> &Caccount- vector holds all checking accounts
    vector<savingsAccount> &Saccount- vector holds all saving accounts
    bool deposit_f - to determine if the user want to deposit or not
    bool withdraw_f - to determine if the user want to withdraw or not

    Alogrithm- Initially, prompt a message to enter the account Checking or Saving-
    use makeStringUpper for the entered account and compare.
    If the account does not match with SAVING or CHECKING, then output an error message “Error : Entered Account type wrong, Account type should be saving or checking”
    - prompt a message to enter the account number- Read the entered number as a string
    - if deposit_f=true, then display a message “Enter the Deposit Amount” - if withdraw_f=true, then display a message “Enter Withdraw Amount”
    -Read the entered amount as a string- if accountType is SAVING, then use stringConvertDouble(strings) to convert entered amount to double
    and stringConvertInt(strings) to convert entered account number to int- Loop through the database vector,
    if the account number matches with any saving account numberin database, then display a message “**Account Information before transaction **”
    - Use print() for saving account- use getters for accountType, accountNumber, firstName,lastName, balance,
    balance()*interestRate*1/100 for Year 1, balance()*interestRate*2/100 for Year2, balance()*interestRate*3/100 for Year 3
    - if deposit_f=true, then update the balance using the function deposit(amount)- if withdraw_f=true,
    then update the balance using the function withdraw(amount)- Display a message “**Account Information after transaction **”
    -Again use print() to check the updated balance and other functions as above print()
    -if the account number is not found in the database, then display a message “Error: Given Accountnumber not present in Saving Account Type”
    - else if ,accountType is Checking, then repeat the steps as continued for SAVINGS account above.
*/
int processMoney(vector<checkingAccount> &Caccount, vector<savingsAccount> &Saccount, bool deposit_f, bool withdraw_f)
{
    string ans;
    string AcctNum;
    string Amount;

    cout << "Enter Account Type name: Saving or Checking" << endl;
    cin >> ans;
    string answerConvert = makeStringUpper(ans);

    if (answerConvert == "SAVING" || answerConvert == "CHECKING")
    {
        cout << "Enter Account Number:" << endl;
        cin >> AcctNum;

        if (deposit_f == true)
        {
            cout << "Enter the Deposit Amount" << endl;
        }
        if (withdraw_f == true)
        {
            cout << "Enter Withdraw Amount" << endl;
        }
        cin >> Amount;

        if (answerConvert == "SAVING")
        {
            double totalAmount = stringConvertDouble(Amount);
            int AccountNums = stringConvertInt(AcctNum);
            bool haveSaving = false;

            for (unsigned int i = 0; i < Saccount.size(); i++)
            {

                if (AccountNums == Saccount[i].getAccountNumber())
                {
                    haveSaving = true;
                    cout << "check" << endl;
                    cout << "**********Account Information before transaction***********" << endl;
                    Saccount[i].print();

                    if (deposit_f == true)
                    {
                        Saccount[i].deposit(totalAmount);
                    }
                    if (withdraw_f == true)
                    {
                        Saccount[i].withdraw(totalAmount);
                    }
                    cout << "**********Account Information after transaction**********" << endl;
                    Saccount[i].print();
                    return 0;
                }
                if (AccountNums != Saccount[i].getAccountNumber())
                {
                    haveSaving = false;
                }
            }
            if (haveSaving == false)
            {
                cout << "Error: Given Account number not present in Saving Account Type" << endl;
                return -1;
            }
        }

        if (answerConvert == "CHECKING")
        {
            double totalAmount2 = stringConvertDouble(Amount);
            int AccountNums2 = stringConvertInt(AcctNum);
            bool haveChecking = false;

            for (unsigned int i = 0; i < Caccount.size(); i++)
            {
                if (AccountNums2 == Caccount[i].getAccountNumber())
                {
                    haveChecking = true;
                    cout << "**********Account Information before transaction**********" << endl;
                    Caccount[i].print();

                    if (deposit_f == true)
                    {
                        Caccount[i].deposit(totalAmount2);
                    }
                    if (withdraw_f == true)
                    {
                        Caccount[i].withdraw(totalAmount2);
                    }
                    cout << "**********Account Information after transaction**********" << endl;
                    Caccount[i].print();
                    return 0;
                }
                if (AccountNums2 != Caccount[i].getAccountNumber())
                {
                    haveChecking = false;
                }
            }
            if (haveChecking == false)
            {
                cout << "Error: Given Account number not present in Checking Account Type" << endl;
                return -1;
            }
        }
    }
    else
    {
        cout << "##########################################################################" << endl;
        cout << "Error: Entered Acccount type wrong, Account type should be saving or checking" << endl;
        cout << "##########################################################################" << endl;
        return -1;
    }
    return 0;
}
