#include "Transaction.h"
    
class Gas
: public Transaction
{

  private:
    double gal;

  public:
    Gas();
    Gas(int month, int date, int year, string description, 
      locationType location, double amount, double gal);
    double getPrice();
    // Accessors
    string getDescription();
    locationType getLocation() {return location;}
    bool getIsReal(); 
    bool income();
    string getCategory();
    bool tithe();
    // Mutators
    void setGal(double gal);

};
