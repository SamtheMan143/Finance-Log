#include "Gas.h:
    
Gas()
: Transaction()
{
  gal = 0;
}

Gas(int month, int date, int year, string description, locationType location, double amount, double gal)
: Transaction(int month, int date, int year, string description, locationType location, double amount)
{
  this->gal = gal;
}

double getPrice()
{
  return amount / gal;
}

// Accessors
string getDescription()
{
  return to_string(gal) + " gal gas";
}

locationType getLocation()
{
  return location;
}

bool getIsReal()
{
  return true;
}

bool income()
{
  return false;
}

Category getCategory()
{
  return gas;
}

bool tithe()
{
  return false;
}

// Mutators
void setGal(double gal)
{
  this->gal = gal;
}