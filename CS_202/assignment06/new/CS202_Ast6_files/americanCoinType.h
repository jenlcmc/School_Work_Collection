
//Definition of the class coinsBox
//The increment, decrement, arithmetic, and relational
//operator functions are members of the class.

#include <iostream>

#define LEN 50
using namespace std;

class coinsBox
{
  //Overload the stream insertion and extraction operators
  friend ostream &operator<<(ostream &, const coinsBox &);
  friend istream &operator>>(istream &, coinsBox &);

public:
  int getPennyCount() const;
  int getNickelCount() const;
  int getDimeCount() const;
  int getQuarterCount() const;
  int getFiftycentpieceCount() const;
  double getTotalAmountinCent() const;
  double getTotalAmountinDollars() const;

  void setPennyCount(int);
  void setNickelCount(int);
  void setDimeCount(int);
  void setQuarterCount(int);
  void setFiftycentpieceCount(int);
  void setName(string);

  //Overload the arithmetic operators
  coinsBox operator+(const coinsBox &) const;
  coinsBox operator-(const coinsBox &) const;
  coinsBox operator*(const coinsBox &) const;

  // assignment operator
  coinsBox &operator-=(const coinsBox &);

  //Overload the increment and decrement operators
  coinsBox operator++();    //pre-increment
  coinsBox operator++(int); //post-increment
  coinsBox operator--();    //pre-decrement
  coinsBox operator--(int); //post-decrement

  //Overload the default assignment operator
  coinsBox &operator=(const coinsBox &);

  //Overload the relational operators
  bool operator==(const coinsBox &) const;
  bool operator!=(const coinsBox &) const;
  bool operator<=(const coinsBox &) const;
  bool operator<(const coinsBox &) const;
  bool operator>=(const coinsBox &) const;
  bool operator>(const coinsBox &) const;

  //Constructors
  coinsBox();
  coinsBox(int _penny, int _nickel, int _dime, int _quater, int _fifty_centpiece, char _name[LEN]);
  ~coinsBox();
  // Copy Constructor
  // coinsBox(coinsBox const &_coinsBox);

private:
  int penny;
  int nickel;
  int dime;
  int quarter;
  int fifty_centpiece;
  char *name;
};
