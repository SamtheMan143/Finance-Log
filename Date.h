#include "Headers.h"

//enum Day {Saturday, Sunday, Monday, Tuesday, Wednesday, Thursday, Friday, unknownDay};

class Date
{

  private:
    int month;
    int day;
    int year;
  public:
    Date();
    Date(int month, int day, int year);
    bool valiDate(); // Pun intended :)
    string getDayOfWeek();
    string toString(int month);
    string toString();
};