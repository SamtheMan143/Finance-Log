Paycheck::Paycheck()
: Transaction()
{
  daysIWorked = {};
}

Paycheck::Paycheck(int month, int day, int year, string description, 
locationType location, double amount, vector<shared_ptr<JerseyMikes>> daysIWorked)
: Transaction(month, day, year, description, location, amount)
{
  this->daysIWorked = daysIWorked;
}

double Paycheck::getDiscrepancy()
{
    vector<shared_ptr<JerseyMikes>>::iterator iter = daysWorked.begin();
    double predictedAmount = 0;
    for (iter; iter < daysWorked.end(); iter++)
    {
        predictedAmount += (*iter)->getAmount();
    }
    return getAmount() - predictedAmount;
}

// Accessors

vector<shared_ptr<JerseyMikes>> Paycheck::getVector()
{
  return daysIWorked;
}

string Paycheck::getDescription()
{
  return getDate().toString() + " JM paycheck";
}

locationType Paycheck::getLocation()
{
  return Bank;
}

bool Paycheck::getIsReal()
{
  return true;
}

bool Paycheck::income()
{
  return true;
}

string Paycheck::getCategory()
{
  return Paycheck;
}

bool Paycheck::tithe()
{
  return true;
}

// Mutators
void Paycheck::setVector(vector<shared_ptr<JerseyMikes>> daysIWorked)
{
  this->daysIWorked = daysIWorked;
}