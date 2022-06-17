#include "record.h"
#include <iomanip>

struct searchListEl {
    record *addrBookElem;
    searchListEl *link;
};

class searchList {
    searchListEl *head;
    searchListEl *last;
    public:
    searchList();
    ~searchList();
    void add(record*);
    void display();
};

/**searchList - constructor 
     * Algo - set all pointer to null
    */
searchList::searchList() {
    head = NULL;
    last = NULL;
}

/**searchList - destructor to set title
     * Algo - like what in the funct say
    */
searchList::~searchList() {
    searchListEl* current = NULL;
    current = head;//set current = head
    while(current != NULL){ //loop until null
        head = head->link; //head is next node
        delete current; //delete current
        current = head;//update current
    }
    head = NULL; //avoid dangling pointer
}

/**add - add to the end of the list
     * record* element - elemnt to add
     * return void
     * Algo - like what in the funct says
    */
void searchList::add(record *element) {
    if(element != NULL){ //if elem is not null
        searchListEl* newNode = NULL; 
        newNode = new searchListEl;//create new node
        newNode->addrBookElem = element; //add data
        newNode->link = NULL; //set link to null for next node

        if(head == NULL){ //list is empty case
            head = newNode; //new node is noth 1st and last node
            last = newNode;
        }
        else{ //list is not empty case
            last->link = newNode; //insert new node to the last
            last = newNode; //make last point to actual last node in the list
        }

    }else{
        return;
    }
}

/**display() - display in the compact form
     * return void;
     * Algo - display the record in compact form with setw()
    */
void searchList::display() {
    searchListEl *current = NULL;;
    current = head; //to transverse;

    std::cout << std::endl << "RECORDS MATCHING" << std::endl;
    while(current != NULL){
        std::cout << current->addrBookElem->first_name << " " <<  current->addrBookElem->last_name << std::setw(22)
            << current->addrBookElem->address_street << std::setw(22) << current->addrBookElem->address_city << std::setw(22)
            <<  current->addrBookElem->address_state << std::setw(22) << current->addrBookElem->address_city << std::setw(22)
            <<  current->addrBookElem->address_zip << std::setw(22) << "phone=" << current->addrBookElem->mobile_no << std::setw(25)
            <<  current->addrBookElem->notes << std::endl;
        current = current->link; //update curr
    }
}

