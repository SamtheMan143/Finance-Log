#include "Transaction.h"
#include <cmath>

Transaction::Transaction()
: Date()
{
  description = "";
  location = Cash;
  amount = 0;

}

Transaction::Transaction(int month, int day, int year, string description, locationType location, double amount)
: Date(month, day, year)
{
  this->description = description;
  this->location = location;
  this->amount = amount;
}

// Accessors

Date Transaction::getDate()
{
  return date;
}

string Transaction::getDescription()
{
  return description;
}

locationType Transaction::getLocation()
{
  return location;
}

double Transaction::getAmount()
{
  return amount;
}

bool Transaction::getIsReal()
{
  return false;
}

bool Transaction::income()
{
  return true;
}

string Transaction::getCategory()
{
  return unknownCategory;
}

bool Transaction::tithe()
{
  return false;
}

// Mutators

void Transaction::setDate(Date date)
{
  this->date = date;
}

void Transaction::setDescription (string description)
{
  this->description = description;
}

void Transaction::setLocation(locationType location)
{
  this->location = location;
}

void Transaction::setAmount(double amount)
{
  this->amount = amount;
}

    
    
void Transaction::setDate()
{
    
  int month,
      day,
      year;
  char useless;
    
  cout << "Date?\n"
  cin >> month >> useless >> day >> useless >> year;
  date.setMonth(month);
  date.setDay(day);
  date.setYear(year);
    
}

void Transaction::inputAmount()
{

  double amount;
  char dollarSign;

  cout << "Input amount:" << endl;
  cin >> dollarSign;
  cin >> amount;

  if ( dollarSign != '$' )
  {
    cout << "Please begin amount with a $ sign." << endl << endl;
    inputAmount();
  }

}
