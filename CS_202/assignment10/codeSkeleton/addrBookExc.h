#ifndef H_ADDRBOOK_EXC
#define H_ADDRBOOK_EXC

#include <stdexcept>

// define exception class 
class addrBookExc : public std::runtime_error{
    public:
        addrBookExc(const std::string& data) : std::runtime_error(data){}
};

#endif
