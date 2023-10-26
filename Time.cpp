#include "Time.h"


Time::Time(int hours, int min)
{
  initiate(hours, min);
}

void Time::initiate(int hours, int min)
{

  this->hours = hours;
  this->min = min;

  if (getAfterNoon())
  {
    afterNoon = true;
  }

  if (!validTime())
  {
    int newHours, newMin;
    char useless; //':'
    cout << "Invalid time. Input the time again:\n";
    cin >> newHours >> useless >> newMin;
    initiate(newHours, newMin);
  }

}

int Time::getTotalMin()
{

  int totalMin = 0;

  if (getAfterNoon())
  {
    totalMin += 12*60;
  }

  totalMin += (hours%12);
  totalMin += min;

}


bool Time::getAfterNoon()
{
  return
    hours > 12 ||
    afterNoon;
}