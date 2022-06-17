#ifndef H_RECORD
#define H_RECORD

#include <string>

struct record {
    int id;
    std::string first_name;
    std::string last_name;
    std::string address_street;
    std::string address_city;
    std::string address_state;
    std::string address_zip;
    std::string mobile_no;
    std::string notes;
    record *child;
    record *prev;
    record *next;
};

#endif
