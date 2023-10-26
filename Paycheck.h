#include "Transaction.h"

class Paycheck
: public Transaction
{
  private:
    vector<shared_ptr<JerseyMikes>> daysWorked;

  public:
    Paycheck::Paycheck();
    Paycheck::Paycheck(int month, int day, int year, string description, 
      locationType location, double amount, vector<shared_ptr<JerseyMikes>> daysIWorked);
    double Paycheck::getDiscrepancy();
    // Accessors
    vector<shared_ptr<JerseyMikes>> Paycheck::getVector();
    string Paycheck::getDescription();
    locationType Paycheck::getLocation();
    bool Paycheck::getIsReal();
    bool Paycheck::income();
    string Paycheck::getCategory();
    bool Paycheck::tithe();
    // Mutators
    void Paycheck::setVector(vector<shared_ptr<JerseyMikes>> daysIWorked);
};