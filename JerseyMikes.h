#include "Transaction.h"
#include "Time.h"

class JerseyMikes
: public Transaction
{

  private:
    Time clockIn;
    Time clockOut;
    shared_ptr<Paycheck> wherePaid;
    const double WAGE = 15.5;
    const double TIP = 4;

  public:
    JerseyMikes();
    JerseyMikes(int month, int day, int year, string description, 
      locationType location, double amount, int hours, int min, bool afterNoon, shared_ptr<Paycheck> wherePaid);
    int getTime();
    string getDescription();
    locationType getLocation();
    double getAmount();
    bool isReal();
    bool income();
    string getCategory();
    bool tithe();

};
