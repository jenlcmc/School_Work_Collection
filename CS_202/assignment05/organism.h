#pragma once

class organism
{
public:
	organism(double = 1, double = 0);
	virtual void simulateWeek();
	void assignRate(double);
	void alterSize(double);
	void death();
	double getSize() const;
	double getRate() const;
	bool isAlive() const;
	virtual ~organism();
protected:
	double growthRate;
private:
	double size;
};
