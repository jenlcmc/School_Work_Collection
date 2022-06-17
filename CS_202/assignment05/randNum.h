#include <fstream>
using namespace std;

class randNum
{
public:
    randNum(string);
    int getNextRand();
private:
    ifstream infile;
};