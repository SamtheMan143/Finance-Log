#include "Date.h"

Date::Date()
{
  month = 0;
  day = 0;
  year = 0;
}

Date::Date(int month, int day, int year)
{
  this->month = month;
  this->day = day;
  this->year = year;
}

bool Date::valiDate()
{

    bool good = true;

    if
     (
        (month == 1) || (month == 3) ||
        (month == 5) || (month == 7) ||
        (month == 8) || (month == 10) ||
        (month == 12) 
     )
    {

        if ( (date < 1) || (date > 31) )
        {
            good = false;
        }

    }

    else if
     (
        (month == 4) || (month == 6) ||
        (month == 9) || (month == 11)
     )
    {

        if ( (date < 1) || (date > 30) )
        {
            good = false;
        }

    }

    else if (month == 2)
    {

        if ( (date < 1) || (date > 29) )
        {
            good = false;
        }

    }

    else
    {
        good = false;
    }



    if ( (year < 23) || (year > 100) )
    {
        good = false;
    }


    if ( !good )
    {
        cout << "Invalid date." << endl;
        cout << "Please use the format MM/DD/YY" << endl;
    }


    return good;


}

string Date::getDayOfWeek()
{

  int mon;
  if(month > 2)
    mon = month; //for march to december month code is same as month
  else{
    mon = (12+month); //for Jan and Feb, month code will be 13 and 14
    year--; //decrease year for month Jan and Feb
  }
  int y = year % 100; //last two digit
  int c = year / 100; //first two digit
  int w = (date + floor((13*(mon+1))/5) + y + floor(y/4) + floor(c/4) + (5*c));
  w = w % 7;

  switch(w)
  {
    case 0:
      return "Saturday";
    case 1:
      return "Sunday";
    case 2:
      return "Monday";
    case 3:
      return "Tuesday";
    case 4:
      return "Wednesday";
    case 5:
      return "Thursday";
    case 6:
      return "Friday";
    case 7:
      return "Saturday";
    default:
      cout << "Error calculating day" << endl;
      return "Unknown day";
  }
}

string Date::toString(int month)
{

  switch (month)
    {
      case 1:
        return "January";
      case 2:
        return "February";
      case 3:
        return "March";
      case 4:
        return "April";
      case 5:
        return "May";
      case 6:
        return "June";
      case 7:
        return "July";
      case 8:
        return "August";
      case 9:
        return "September";
      case 10:
        return "October";
      case 11:
        return "November";
      case 12:
        return "December";
      default:
        return "Unknown month";
    }

}

string Date::toString()
{ 
  return
    to_string(month) + '/' +
    to_string(day) + '/' +
    to_string(year);
}