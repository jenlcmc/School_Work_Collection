/*
    * Name: Uyen Tran, 2001803775, CS302-1001
    * Descriptions: Implement of bubble sort using doubly linked list
    * Input: File contains list of numbers
    * Output: Sort list of numbers from the file

*/

#include "LL.h"
#include <fstream>
#include <string>

using namespace std;

int main(){
    // variables needed for program
    string file;
    int num;
    ifstream inputFile;

    LL<int>::iterator i, j, k;
    LL<int> theList;
    LL<int>:: iterator it;
    LL<int>:: iterator nul(NULL);

    //ask user for the file
    cout << "Enter file with list: ";
    cin >> file;

    //open the file and test whether if it can be open or not
    inputFile.open(file);

    if(inputFile.is_open() == false){
        cout << "Can't open " << file << ". Check file name again\n";
        return 0;
    }

    //read in numbers and using tailInsert to insert number to the list
    while(inputFile >> num){
        theList.tailInsert(num);
    }   

    //output the original list before swap
    cout << "Original List\n";
    it = theList.begin();
    while (it != nul)
    {
        cout << *it << " ";
        it++;
    }

    cout << '\n' << '\n';

        //Bubble sort using swap function
    i = theList.end();
    // i use to indicate whether done sorting or not
    while(i != theList.begin() && i != NULL){
        j = theList.begin();
        k = j;
        k++;
        //k = is it end of list or not
        while(k != NULL){
            if(*j > *k){
                theList.swapNodes(j, k);
                std::cout << *j << " " << *k << std::endl;
            }
            j++;
            k++;
        }
        i--;
    }

    //output the list after sorting
    cout << "Sorted List\n";
    it = theList.begin();
    while (it != nul)
    {
        cout << *it << " ";
        it++;
    }
    cout << '\n';

    return 0;
}
