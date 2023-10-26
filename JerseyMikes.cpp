#include "JerseyMikes.h"

JerseyMikes::JerseyMikes()
: Transaction()
{
  
}

JerseyMikes::JerseyMikes(int month, int day, int year, string description, 
locationType location, double amount, int hours, int min, bool afterNoon, shared_ptr<Paycheck> wherePaid)
: Transaction(month, day, year, description, location, amount), Time(hours, min, afterNoon)
{
  this->wherePaid = wherePaid;
}

int getTime()
{
  return clockOut.getTotalMin() = clockIn.getTotalMin();
}

string JerseyMikes::getDescription()
{
  return to_string(getTime()/60) + " hours " + 
    to_string(getTime()%60) + " min JM";
}

locationType JerseyMikes::getLocation()
{
  return Bank;
}

double JerseyMikes::getAmount()
{
  double hours = getTime() / 60;
  if (hours <= 8;) // Didn't work overtime
    return WAGE * hours;
  else
    return WAGE*8 + WAGE*(hours-8)*1.5 + TIPS*hours; // Standard wage + overtime + tips
}

bool JerseyMikes::isReal()
{
  return false;
}

bool JerseyMikes::income()
{
  return true;
}

Category JerseyMikes::getCategory()
{
  return JerseyMikes;
}

bool JerseyMikes::tithe()
{
  return false;
}