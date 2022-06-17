#include "organism.h"
#pragma once

class plant : public organism
{
public:
	plant(double = 1, double = 0);
  	void nibbledOn(double);
	  ~plant();
};