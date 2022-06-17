#include <iostream>
#include "addressBook.h"
#include "addrBookExc.h"
#include "searchList.h"
#include "menu.h"
#include <fstream>
#include <vector>
//test
#include <sstream>

using namespace std;

addressBook::addressBook(string filename) {
    head = NULL;
    last = NULL;
    firstToDisplay = NULL;
    loadFile(filename); //to populate linked list
    firstToDisplay = NULL; //extra test
}

addressBook::~addressBook() {
    record* temp = NULL; 
    while(head != NULL){
        temp = head;
        head = head->next;
        delete temp;
    }
    last = NULL;
}

void addressBook::displayRecord(record *r) {
    cout << setw(10) << "Name: " << r->first_name << " " << r->last_name << endl;
    cout << setw(10) << "Street: " << r->address_street;
    cout << setw(10) << "City: " << r->address_city;
    cout << setw(10) << "State: " << r->address_state;
    cout << setw(10) << "Zip: " << r->address_zip << endl;
    cout << setw(10) << "Phone: " << r->mobile_no << endl;;
    cout << setw(10) << "Notes: " << r->address_city << endl;
    cout << endl;
}

void addressBook::display3() {
    record* curr = NULL;
    curr = head;
    int count = 0;

    while(curr != NULL){ 
        //count number of nodes in the list
        count++;
        curr = curr->next;
        //multiple eleement case
        if(count > 3 && firstToDisplay != NULL){
            count = 0;
            //loop from postion to 3 times 
            for(firstToDisplay; count < 3; firstToDisplay = firstToDisplay->next){
                displayRecord(firstToDisplay);
                count++;
            }
        }
        //scroll = last and prev of last case 
        if(firstToDisplay == last || firstToDisplay == last->prev){
            //loop from postition to null
            for(firstToDisplay; firstToDisplay != NULL; firstToDisplay = firstToDisplay->next){
                displayRecord(firstToDisplay);
            }
        }
        //case where count <= 3
        else{
            count = 0;
            //loop from postion to 3 times 
            for(firstToDisplay; count < 3 && firstToDisplay != NULL; firstToDisplay = firstToDisplay->next){
                displayRecord(firstToDisplay);
                count++;
            }
        }
    }
    return;
}

void addressBook::displayAll(record *current) {
    if(head == NULL || current == NULL){
        return;
    }else{
        displayRecord(current);
        displayAll(current->next);
    }
}

void addressBook::displayTree(record *current, int indent) {
    if(head == NULL || current == NULL || indent < 0){
        return;
    }else{
        cout << "id=" << current->id << '\t' << "name=" << current->first_name << " " << current->last_name << endl;
        for(int i = 0 ; i < indent; i ++){
            cout << '\t';
        }
        displayTree(current, indent + 1);
    }
}

void addressBook::display(const char option) {   // 0: all, full     1: tree
    int indent = 0;
    if(option == 0){
        displayAll(firstToDisplay); //ask
    }else if(option == 1){
        displayTree(firstToDisplay, indent);
    }else{
        return;
    }
}

void addressBook::goToFirst() {
    firstToDisplay = head;
    display3();
}

void addressBook::operator++() {
    if(firstToDisplay == last){
        return;
    }else{
        firstToDisplay = firstToDisplay->next;
        display3();
    }
}

void addressBook::operator--(){
    cout << "test" << endl;
    if(firstToDisplay == head){
        cout << "empty" << endl;
        return;
    }
    else{
        cout << "not empty" << endl;
        firstToDisplay = firstToDisplay->prev;
        display3();
    }
}

record* addressBook::parseAllocate(string line) { //fix
    string delim = ",";
    int parentID = 0;
	vector<string> parse;
    record* afterParse = new record;
    record* curr = head;
    //curr->child = NULL;
	size_t start = 0, end = 0; //size_t or unsigned long //ask

    //clear for new record
    parse.clear();

    //loop to find and parse string using vec and find()
	while ((end = line.find(delim, start)) != string::npos){
		parse.push_back(line.substr(start, end - start));
		start = end + 1;
	}
	parse.push_back(line.substr(start));

	//set value
    afterParse->id = stoi(parse[0]);
    afterParse->first_name = parse[2];
    afterParse->last_name = parse[3];
    afterParse->address_street = parse[4];
    afterParse->address_city = parse[5];
    afterParse->address_state = parse[6];
    afterParse->address_zip = parse[7];
    afterParse->mobile_no = parse[8];
    afterParse->notes = parse[9];

    //special one/ parent id 
    parentID = stoi(parse[1]);
    //loop from head until null and check to see for curr id, and incremtn node
    /*for(curr = head; curr->id != parentID && curr != NULL; curr = curr->next){
        afterParse->child = curr;
    }*/
    
    return afterParse;
}

void addressBook::addRecord(string line) {
    record* temp;
    temp = parseAllocate(line);
    temp->next = NULL;
    // 2. add element to the list
    if (head == NULL) {    // list is empty
        temp->prev=NULL;
        head = temp;
        last = temp;
    } else {    // list is not empty, add at the end
        temp->prev = last;
        last->next = temp;
        last = temp;
    }

}

void addressBook::loadFile(string filename) {
    string line;

    try
    {
        ifstream infile;
        infile.open(filename);

        if(!infile.is_open()){
            throw addrBookExc("error opening the file: records.csv \n ABORT");
        }else{
            while(!infile.eof()){
                getline(infile, line, '\n');
                addRecord(line);
                line.clear();
            }
        }
    }
    catch(addrBookExc &noFile)
    {
        cout << noFile.what() << endl;
        throw noFile;
    }
    
}

void addressBook::search() {
    Menu makeMenu("SEARCH MENU");
    makeMenu.add("First name", '1');
    makeMenu.add("Last name", '2');
    makeMenu.add("City ", '3');
    makeMenu.add("State", '4');
    makeMenu.add("Back to previous menu", 'q');

    char Userchoice; 
    searchList* searchListObj = NULL;
    record* temp = NULL;
    string keyword;
    Userchoice = makeMenu.displayAndRead();
    

    switch(Userchoice) //ask
    {

    case 'q':
        return;
        break;
    
    case 1:
        cout << "Enter keyword/string: ";
        cin >> keyword;
        cout << "searching against the keyword: " << keyword << endl;
        for(temp = head; temp != NULL; temp = temp->next){
            if(keyword == temp->first_name){
                searchListObj->add(temp);
            }
        }
        searchListObj->display();
        break;

    case 2:
        cout << "Enter keyword/string: ";
        cin >> keyword;
        cout << "searching against the keyword: " << keyword << endl;
        for(temp = head; temp != NULL; temp = temp->next){
            if(keyword == temp->last_name){
                searchListObj->add(temp);
            }
        }
        searchListObj->display();
        break;

    case 3:
        cout << "Enter keyword/string: ";
        cin >> keyword;
        cout << "searching against the keyword: " << keyword << endl;
        for(temp = head; temp != NULL; temp = temp->next){
            if(keyword == temp->address_city){
                searchListObj->add(temp);
            }
        }
        searchListObj->display();
        break;

    case 4:
        cout << "Enter keyword/string: ";
        cin >> keyword;
        cout << "searching against the keyword: " << keyword << endl;
        for(temp = head; temp != NULL; temp = temp->next){
            if(keyword == temp->address_state){
                searchListObj->add(temp);
            }
        }
        searchListObj->display();
        break;

    default:
        break;
    }
    
}
