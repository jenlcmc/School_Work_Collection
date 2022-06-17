#include "animal.h"
#include "plant.h"

class herbivore : public animal
{
public:
	static const double PORTION;  
	static const double MAX_FRACTION;
	herbivore(double = 1, double = 0, double = 0);
	void nibble(plant&);
	~herbivore();
};