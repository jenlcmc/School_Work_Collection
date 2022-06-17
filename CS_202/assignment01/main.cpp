
// Include libraries
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <string>
#include <cmath>

using namespace std;

// Structure to hold item data
struct AISType
{
    string MMSI;             // 0
    string baseDateTime;     // 1
    double lattitude;        // 2
    double longitude;        // 3
    double sog;              // 4
    double cog;              // 5
    double heading;          // 6
    string vesselName;       // 7
    string imo;              // 8
    string callSign;         // 9
    string vesselType;       // 10
    string status;           // 11
    double length;           // 12
    double width;            // 13
    double draft;            // 14
    string cargo;            // 15
    string transceiverClass; // 16
};

// Prototypes for functions
void readFile(ifstream &inFile, vector<AISType> &item, int &count);
bool openInputFile(ifstream &inFile);
string makeStringUpper(string s);
int searchForVesselByName(vector<AISType> &dataBase, string vesselName,
                          vector<string> &s);
void printRecord(AISType &item);
bool getNextField(string &line, int &index, string &subString);
double stringConvert(string);
int findLastOccurrance(string mmsi, vector<AISType> &d);
int findFirstOccurrance(string mmsi, vector<AISType> &d);
void addUniqueString(vector<string> &s, string value);
void saveField(int fieldNumber, string subString, AISType &tempItem);
double distanceTraveled(vector<AISType> &dataBase, int first, int last);

int main()
{
    // number of records read into the dataBase
    int count = 0;

    // the dataBase
    // vector type is used because it's too big for an array.
    // (on my computer anyway)
    vector<AISType> dataBase;
    vector<string> mmsi;

    // input file
    ifstream inFile;

    // temporary strings
    string temp;
    string ansYN;

    int found = 0;
    string stars = "";
    int first = 0, last = 0;

    // open the input file
    if (openInputFile(inFile))
        cout << "File opened correctly " << endl;
    else
    {
        cout << "Error opening file" << endl
             << "Existing...." << endl;
        return 0;
    }

    // read the entire file into the dataBase
    readFile(inFile, dataBase, count);

    cout << count << " records read " << endl;

    cin.ignore(40, '\n');

    // user interaction loop
    do
    {

        // prompt the user for the input to search for.  q to quit
        temp.clear();
        mmsi.clear();

        cout << "Enter vessel name: ";

        // read the user input.  getline is used so that spaces may be included
        // in the input
        getline(cin, temp, '\n');

        // check to see if the user wants to exit the program.
        // If not exiting, output the search string.
        if (temp != "q" or temp == "Q")
        {
            cout << endl
                 << "Searching for records with names containing \""
                 << temp << "\"" << endl;
        }
        else
            return 0;

        // search for the number of items that contain the name/phrase
        // All names in the vessel dataBase are upper case, so make the search
        // string upper.  MMSI is built by the function and contains the vector
        // of unique vessels that contain the name searched for.
        found = searchForVesselByName(dataBase, makeStringUpper(temp), mmsi);

        // Let the user know if any ships were found with the name
        if (found <= 0)
        {
            cout << "Vessel \"" << temp << "\" not found" << endl;
            continue;
        }
        else
        {
            // output the results of the search
            cout << stars << endl;
            cout << found << " vessels found with name containing \"" << temp
                 << "\", ";
            cout << "Unique vessels: " << mmsi.size() << endl;
            cout << stars << endl;

            // ships were found, see if the user wants to display them
            cout << mmsi.size() << " vessels found. Would you like to see their"
                 << " first records? [y/n] ";
            cin >> ansYN;

            if (ansYN == "y" or ansYN == "Y")
            {

                // print all the first records for the ships found
                for (unsigned int i = 0; i < mmsi.size(); i++)
                {

                    // find the vessels using MMSI and print the records
                    int index = findFirstOccurrance(mmsi[i], dataBase);

                    // verify that a valid record was found, print the record
                    if (index != -1)
                        printRecord(dataBase[index]);
                }

                // Ask user if they want to calculate the distance traveled for
                // the vessel.
                cout << "Would you like to find the distance traveled for a vessel?"
                        " [y/n] ";
                cin >> ansYN;

                if (ansYN == "y" or ansYN == "Y")
                {
                    cout << "MMSI for vessel: ";
                    cin >> temp;
                    cout << stars << endl;

                    // locate the index value of the first and last record
                    first = findFirstOccurrance(temp, dataBase);
                    last = findLastOccurrance(temp, dataBase);

                    // output the sitances and miles traveled
                    cout << "Vessel: \"" << dataBase[first].vesselName;
                    cout << "\" MMSI: " << dataBase[first].MMSI;
                    cout << " Trip Starting time: " << dataBase[first].baseDateTime;
                    cout << endl;
                    cout << "Distance Traveled from (" << dataBase[first].lattitude;
                    cout << ", " << dataBase[first].longitude << ") to (";
                    cout << dataBase[last].lattitude << ", ";
                    cout << dataBase[last].longitude << ") ";
                    cout << distanceTraveled(dataBase, first, last);
                    cout << " Miles" << endl;
                    cout << endl;
                }
            }
        }
        cin.ignore(40, '\n');

    } while (true);
}

/* distanceTraveled - Use harversine formula to calculate the great circle distance between vessel location
in records first and last, using latitude and longitude.
    vector<AISType>& dataBase - vector containing the AIS data records
    int first - index of starting location record
    int last - index of ending location record
        return result - calculate distance, if bad then return 0.0

    Algorthims
        Set up radius and pi values to constant variable (can't change). Then calculate first and second
        latitude and change it into radian. Calculate both latitude and longitude change for the harversine formula
        and convert into radian.
        Then apply all calculated results to harversine formula which is double a,c and value; Divide it into
        smaller parts for readability.
*/
double distanceTraveled(vector<AISType> &dataBase, int first, int last)
{
    const double R = 3958.8; // const so it wont change
    const double PI = 3.14159;

    double First_Lat_Radian = (dataBase[first].lattitude * PI) / 180.0; // change degree into radian
    double Second_Lat_Radian = (dataBase[last].lattitude * PI) / 180.0;
    double LattitudeChange = (Second_Lat_Radian - First_Lat_Radian);

    double First_long_Radian = (dataBase[first].longitude * PI) / 180.0; // change degree into radian
    double Second_long_Radian = (dataBase[last].longitude * PI) / 180.0;
    double LongitudeChange = (Second_long_Radian - First_long_Radian);

    double a = pow(sin(LattitudeChange / 2), 2) + cos(First_Lat_Radian) *
                                                      cos(Second_Lat_Radian) * pow(sin(LongitudeChange / 2), 2);
    double c = 2 * atan2(sqrt(a), sqrt(1 - a));
    double value = R * c; // harvest equation
    // if bad result <= 0 then it will = 0.0
    if (value <= 0.0)
    {
        return 0.0;
    }
    else
    {
        return value;
    }
}

// Example function header comment.
/* findLastOccurrance - finds the last occurrance of an entry in the dataBase
using the MMSI as the matching criterion. The vector is search from the
last entry forward.  The vector  data is in time sequential order.
    string mmsi - the MMSI of the desired vessel.
    vector<AISType & d - the dataBase of vessels.  This is passed by reference
        for efficiency.

    return value - the index of the last record in the dataBase for the vessel
        with the matching MMSI.  If the MMSI is not found, return -1.

    Algorithm
        Use a for loop the to seach from the last element of the vector toward
        the first. Since the data is time ordered, oldest first, search the
        vector from the bottom towards the top. This is a linear search and
        returns as soon as a match is found.

*/
int findLastOccurrance(string mmsi, vector<AISType> &d)
{
    for (int i = (d.size() - 1); i >= 0; i--)
    { // reverse search for loop
        if (d[i].MMSI == mmsi)
        {
            return i;
        }
    }
    return -1;
}

/* findFirstOccurrance - finds the first occurrance of an entry in the dataBase
using the MMSI as the matching criterion. The vector is search from the
first entry backward.  The vector  data is in time sequential order.
string mmsi - the MMSI of the desired vessel.
    vector<AISType & d - the dataBase of vessels.  This is passed by reference
        for efficiency.

    return value - the index of the first record in the dataBase for the vessel
        with the matching MMSI.  If the MMSI is not found, return -1.

    Algorithm
        Use a for loop the to seach from the first element of the vector toward
        the last. Since the data is time ordered, newest first, search the
        vector from the top toward bottom. This is a linear search and
        returns as soon as a match is found.
*/
int findFirstOccurrance(string mmsi, vector<AISType> &d)
{
    for (unsigned int i = 0; i < d.size(); i++)
    {
        if (mmsi == d[i].MMSI)
        {
            return i;
        }
    }
    return -1;
}

/* searchForVesselByName - performs a linear search on all records in dataBase for records
    whose vesselName memebr contains the string passed in vesselName. The search should be done
    from 0 to maximum valid index. This function calls addUniqueString() to add the MMSI to the
    matchedAIS vector.
    vector<AISType> &dataBase - the database of AIS records read from the file
    string vesselName - string to be searched for in the vessel name
    vector<string> &s - matchesAIS - all vessel whose name contains the passed string, vesselName
        should have their MMSI string add to the passed vector matches AIS. The only one
        that contains the MMSI of vessels.
    return count - the number of records found that match the passed string - vesselName

    Algorithms
        Use for loop to loop through the database. Use find() function to find desired vesselName
        from dataBase vessel name. If it not same with string npos, then use addUniqueString()
        to add the MMSI into the s vector(matchesAIS). Then increment count. After loop through the
        database, return number of count


*/
int searchForVesselByName(vector<AISType> &dataBase, string vesselName, vector<string> &s)
{
    int count = 0;

    for (unsigned int i = 0; i < dataBase.size(); i++)
    {
        if (dataBase[i].vesselName.find(vesselName) != string::npos)
        {
            addUniqueString(s, dataBase[i].MMSI);
            count++;
        }
    }
    return count;
}

/* addUniqueString - first searches the vector to determine if the string is already present.
    If the string is already present, function will returns. If not, this will addded at the
    end of the vector. String will never appear twice in vector
    vector<string> &s - the vector that the string should be added to
    string value - the string to be added
    return none

    Algorithms
        use if- else statement to determine if the string is empty or not. If empty, push_back value into the
        vector of string. If not empty, loop through the string vector. If value is not the same with value
        in string vector, then push back that value into string vector. if value is the same, stop the function
*/
void addUniqueString(vector<string> &s, string value)
{

    for (unsigned int i = 0; i < s.size(); i++)
    {
        if (s[i] == value)
        {
            return;
        }
    }
    s.push_back(value);
}

/* stringConvert - converts a string to it's corresponding double value. Must use stringstream.
    string s - the string to be converted into double
    return value - the double converted from the string

    Algorithm
        set up the stringstream variable to take value from the string and extract it into double value.
*/
double stringConvert(string s)
{
    stringstream convert2x;
    double value;

    convert2x << s;
    convert2x >> value;
    return value;
}

/* printRecord - the function prints all fields for the record
    AISType& item - the record to print. Single item not the vector
    return void

    Algorithm
    output all the data from the database using string and item to access the values
    from the members of the AISType struct
*/
void printRecord(AISType &item)
{
    cout << "************************" << endl;
    cout << "MMSI: '\t" << item.MMSI << endl;
    cout << "Base Date Time: \t" << item.baseDateTime << endl;
    cout << "Lattitude: \t" << item.lattitude << "\t Longitude: \t" << item.longitude << endl;
    cout << "SOG: \t" << item.sog << endl;
    cout << "COG: \t" << item.cog << endl;
    cout << "Heading: \t" << item.heading << endl;
    cout << "Vessel Name: \t" << item.vesselName << endl;
    cout << "imo: \t" << item.imo << endl;
    cout << "Call Sign: \t" << item.callSign << endl;
    cout << "Vessel Type: \t" << item.vesselType << endl;
    cout << "Status: \t" << item.status << endl;
    cout << "Length: \t" << item.length << endl;
    cout << "Width: \t" << item.width << endl;
    cout << "Draft: \t" << item.draft << endl;
    cout << "Cargo: \t" << item.cargo << endl;
    cout << "Transceiver Class: \t" << item.transceiverClass << endl;
    cout << endl
         << endl
         << endl;
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

/* readFile - uses the previously opened filestram to read in the data from the file. USe getline() to read
    data and use '\n' as terminating character. Use saveField() to set the corresponding value in tge temporary
    record as the line ead and field are parsed. ONce parsing line done, temporary records is filled, use push_back()
    to ass temporary record to the AISType vector. Then reset all values in temporary to 0 before reusing.
    Use counter of the number of records read to outputting.
    ifstream inFile - already open file to be read
    vector<AISType> &item - vector to store data
    int& count - the number of records read
    return count - total count of the record read

    ALgorithms
        use getline() to read the line into a string. Then check for eof() use while loop.
        Set index and fieldNunmber to 0. Then call getNextField() on the string read in 1st step,
        passing index, a string to receive the field. Then use saveField() to store the data in
        temporary struct of type AISType(use fieldNumber to determince which field gets the data).
        Increment fieldNUmber and loop back to getNextField() using for loop until entire string has
        been processed. Add the temporary struct holding data to vector using push_back().
        Then reset fieldNumber and index to 0 and loop back to first until eof()
*/
void readFile(ifstream &inFile, vector<AISType> &item, int &count)
{
    string line;
    string nextStr;
    AISType temporary;
    int index, fieldNumber;

    cout << "----------------------" << endl;

    while (!inFile.eof())
    {
        getline(inFile, line, '\n');
        index = 0, fieldNumber = 0;
        count++;
        for (int i = 0; i < 17; ++i)
        { // 17 items so loop 17 times
            getNextField(line, index, nextStr);
            saveField(fieldNumber, nextStr, temporary);
            fieldNumber++;
        }

        item.push_back(temporary);
        index = 0, fieldNumber = 0;

        char eraseLine[] = {'\r', 27, '[', '1', 'K'};

        if ((count % 100000) == 0)
        {
            cout << eraseLine << count;
            cout.flush();
        }
    }
    cout << "--- End of file reached ---Items read: " << count << endl;
    cout << endl;
}

/* saveField - save subString into fieldNumber in the record passed tempItem. SubString will be converted
    to a double depending on fieldNumber. Function will use stringConvert() to perform conversion
    from string to double. Error will be ouput if unknown field number
    int fieldNumber - the number of the field, start at 0
    string subString - value to be saved in the field, may require converse to double
    AISType &tempItem - the record to which the field will be added
    return number match with conditions by switch statement

    Algorithm
        using fieldNumber and switch statement to consider which field to save subString into
        If subString is string then use stringConvert() to convert into double.
        Default use to ouput error
*/
void saveField(int fieldNumber, string subString, AISType &tempItem)
{

    switch (fieldNumber)
    {
    case 0:
        tempItem.MMSI = subString;
        break;
    case 1:
        tempItem.baseDateTime = subString;
        break;
    case 2:
        tempItem.lattitude = stringConvert(subString);
        break;
    case 3:
        tempItem.longitude = stringConvert(subString);
        break;
    case 4:
        tempItem.sog = stringConvert(subString);
        break;
    case 5:
        tempItem.cog = stringConvert(subString);
        break;
    case 6:
        tempItem.heading = stringConvert(subString);
        break;
    case 7:
        tempItem.vesselName = subString;
        break;
    case 8:
        tempItem.imo = subString;
        break;
    case 9:
        tempItem.callSign = subString;
        break;
    case 10:
        tempItem.vesselType = subString;
        break;
    case 11:
        tempItem.status = subString;
        break;
    case 12:
        tempItem.length = stringConvert(subString);
        break;
    case 13:
        tempItem.width = stringConvert(subString);
        break;
    case 14:
        tempItem.draft = stringConvert(subString);
        break;
    case 15:
        tempItem.cargo = subString;
        break;
    case 16:
        tempItem.transceiverClass = subString;
        break;

    default:
        cout << "Error: Unknow field number" << endl;
        break;
    }
}

/* getNextField - bool function uses previously opened filestream to read data starting from the index.
    Then find next string which is upto comma or newline. Fields are seperate by commas. If found,
    save to subString. Comma s will be skipped. Index value will be update as line is processed.
    When function returns, index point to next character to be processed, and will be used as starting point
    for nex tcall function.Can't use .find()
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
    // cout << subString << endl; //debug

    if (static_cast<int>(line.length()) <= index)
        return false;
    else
        return true;
}

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
