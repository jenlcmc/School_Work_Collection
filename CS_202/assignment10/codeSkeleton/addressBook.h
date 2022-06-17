#include "record.h"

class addressBook {
    record *head;
    record *last;
    record *firstToDisplay;
    void loadFile(std::string); 
    record* parseAllocate(std::string); 
    void addRecord(std::string);
    void displayRecord(record*);
    void displayAll(record*);
    void displayTree(record*, int);
    public:
    addressBook(std::string);
    ~addressBook();
    void display3();
    void goToFirst();
    void display(const char);
    void search();
    void operator++();
    void operator--();
};
