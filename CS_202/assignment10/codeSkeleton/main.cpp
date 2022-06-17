#include <iostream>
#include "addressBook.h"
#include "menu.h"

using namespace std;

int main() {
    addressBook *myBook = NULL;
    char UserChoice;
    bool done = false;

    //try and test to see if it read the file or not
    try {
        // create / allocate myBook object here
        string filename;
        myBook = new addressBook(filename);
    } catch (...) {
        cout << "FATAL ERROR: failed to read file, terminating." << endl;
        return 0;
    }
    // create menu
    Menu makeMenu("MAIN MENU");
    makeMenu.add("Next", 's');
    makeMenu.add("Previous", 'w');
    makeMenu.add("Go to first", 'f');
    makeMenu.add("Display all", 'd');
    makeMenu.add("Display tree", 't');
    makeMenu.add("Search", 'j');
    makeMenu.add("Quit", 'q');
    
    // default action is to display 3 records
    cout << endl << "YOUR CONTACTS" << endl;
    myBook->goToFirst();
    // display main menu and take actions related to options
    do{
        UserChoice = makeMenu.displayAndRead();
        switch(UserChoice)
        {
        case 's':
            cout << "YOUR CONTACTS" << endl;
            ++(*myBook);
            break;
        
        case 'w':
            cout << "YOUR CONTACTS" << endl;
            --(*myBook);
            break;
        
        case 'f':
            cout << "YOUR CONTACTS" << endl;
            myBook->goToFirst();
            break;
    
        case 'd':
            myBook->display(0);
            break;
    
        case 't':
            cout << "TREE" << endl;
            myBook->display(1);
            break;
    
        case 'j':
            myBook->search();
            break;
    
        case 'q':
            done = true;
            break;
        
        default:
            break;
        }
    }while(!done);
    //clean up
    delete myBook;
}
