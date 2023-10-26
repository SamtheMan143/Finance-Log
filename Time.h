#include <iostream>
#include <iomanip>
#include <vector>
#include <memory>
#include <string>
using std::cout;
using std::cin;
using std::ifstream;
using std::ofstream;
using std::vector;
using std::string;
using std::istringstream;
using std::to_string;
using std::shared_ptr;
using std::endl;
using std::fixed;
using std::setprecision;
using std::make_shared;


class Time
{

  private:
    int hours;
    int min;
    bool afterNoon;

  public:
    Time(int hours, int min);
    int getHours() {return hours;}
    int getMin() {return min;}
    int getTotalMin();
    bool getAfterNoon();
    void initiate(int hours, int min);

};