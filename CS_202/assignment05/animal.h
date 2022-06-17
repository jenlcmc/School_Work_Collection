#include "organism.h"

class animal : public organism
{
public:
	animal(double = 1, double = 0, double = 0);
	void assignNeed(double);
	void eat(double);
	void simulateWeek();
	double stillNeed() const;
	double totalNeed() const;
	~animal();
private:
	double needThisWeek;
	double eatenThisWeek;
};