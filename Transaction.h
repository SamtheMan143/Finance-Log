#include "Date.h"
#include "Time.h"

//enum transactionType {Income, Expense, Tithe, UnknownType};
enum locationType {Bank, Cash, Check, UnknownLocation};
enum Category {Landscape, JerseyMikes, tutoring, compensation, gift, // Income
                gas, groceries, unknownCategory}; // Expenses


class Transaction
{

  private:
    Date date;
    string description;
    locationType location; // Bank or Cash
    double amount;
    //int serialNumber;


  public:

    Transaction();
    Transaction(int month, int date, int year, string description, locationType location, double amount);

    // Accessors

    Date getDate();
    string getDescription();
    locationType getLocation();
    double getAmount();
    bool getIsReal(); 
    bool income();
    string getCategory();
    bool tithe();

    // Mutators

    void setDate(Date date);
    void setDescription (string description);
    void setLocation(locationType location);
    void setAmount(double amount);
    private: void setDate();


};    


class Compensation
: public Transaction
{
  public:
    bool tithe() {return false;}
};

class Gift
: public Transaction
{
}

class Groceries
: public Transaction
{
  private:
    string store;
    vector<shared_ptr<Food>> whatIBought;
    double tax;
  public:
    double getAmount();
};
    
double Groceries::getAmount()
{
  double count = 0;
  vector<shared_ptr<Food>>::iterator iter = whatIBought.begin();
  for (iter; iter < whatIBought.end; iter++)
  {
    count += *iter->getAmount();
  }
  return count;
}

class Food
: public Transaction
{
  private:
    string name;
    double qty;
    string servingSize;
  public:
    double pricePerServing() {return amount / qty;}
};

class Tithe
: public Transaction
{
  public:
    bool tithe() {return false;}
}

class General
: public Transaction
{
  bool isReal;
  bool tithe;
  bool income;
};