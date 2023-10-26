#include "TransactionHistory.h"

TransactionHistory::TransactionHistory()
{

  list = {};
  balance.cash = 0;
  balance.bank = 0;
  balance.payPal = 0;
  balance.Venmo = 0;
  titheDue = 0;

}



void TransactionHistory::addTransaction()
{

  char choice;

  cout << "\nWhat type of transaction?\n"
       << "i - General income\n"
       << "e - General expense\n"
       << "j - Jersey Mike\'s\n"
       << "p - Paycheck\n"
       << "g - Gift\n"
       << "c - Compensation\n"
       << "a - Gas\n"
       << "r - Groceries\n"
       << "f - Food\n"
       << "t - Tithe\n\n";

  cin >> choice;

  switch(choice)
    {
  
      case 'i':
        jerseyMikes();
        break;
      case 'e':
        shared_ptr<genExpense> newTransaction = make_shared<genExpense>();
        list.push_back(newTransaction);        
        break;
      case 'j':
        shared_ptr<JerseyMikes> newTransaction = make_shared<JerseyMikes>();
        list.push_back(newTransaction);        
        break;
      case 'p':
        shared_ptr<Paycheck> newTransaction = make_shared<Paycheck>();
        transferWorkdays(newTransaction);
        list.push_back(newTransaction);        
        break;
      case 'g':
        shared_ptr<Gift> newTransaction = make_shared<Gift>();
        list.push_back(newTransaction);        
        break;
      case 'c':
        shared_ptr<Compensation> newTransaction = make_shared<Compensation>();
        list.push_back(newTransaction);        
        break;
      case 'a':
        shared_ptr<Gas> newTransaction = make_shared<Gas>();
        list.push_back(newTransaction);        
        break;
      case 'r':
        shared_ptr<Groceries> newTransaction = make_shared<Groceries>();
        list.push_back(newTransaction);        
        break;
      case 'f':
        shared_ptr<Food> newTransaction = make_shared<Food>();
        list.push_back(newTransaction);        
        break;
      case 't':
        shared_ptr<Tithe> newTransaction = make_shared<genIncome>();
        list.push_back(newTransaction);        
        break;
      default:
        cout << "Invalid choice.\n";
        addTransaction();
      
    }

}

void TransactionHistory::jerseyMikes()
{

  int hour,
      min;
  char useless;

  setDate();
  cout << "\n\nWhat time did you clock in? (24-hour time)\n";
  cin >> hour >> useless >> min;
  clockIn.initiate(hour, min);
  cout << "What time did you clock out?\n";
  cin >> hour >> useless >> min;
  clockOut.initiate(hour, min);

  cout << "Estimated $" << getAmount() << endl;
  cout << "$" << (hours-8)*WAGE*(1.5) << 
       " Paid overtime" << endl;
  
}

void TransactionHistory::transferWorkdays(vector<shared_ptr<Paycheck>>& newTransaction)
{
  
  for (iter; iter < list.back(); iter++)
  {
    
    if (*iter->getDate() < newTransaction.getDate() &&
        *iter->getCategory() == "JerseyMike\'s")
    {
      newTransaction.addToList(*iter);
      erase(iter);
    }
      
  }
    
}

void TransactionHistory::erase(vector<shared_ptr<Paycheck>>::iterator iter)
{
  swap(iter, list.back());
  list.pop_back();
}

void TransactionHistory::swap(vector<shared_ptr<Paycheck>>::iterator iter1, vector<shared_ptr<Paycheck>>::iterator iter2)
{
  vector<shared_ptr<Paycheck>>::iterator temp = iter1;
  iter1 = iter2;
  iter2 = temp;
}
























void TransactionHistory::addTransaction()
{

  Transaction newTransaction;

  inputDate(newTransaction);
  inputDescription(newTransaction);
  inputType(newTransaction);
  inputCategory(newTransaction);
  inputAmount(newTransaction);
  inputLocation(newTransaction);
  updateBalance(newTransaction);
  allocateSerialNumber(newTransaction);

  list.push_back(newTransaction);

  sort();
  save();

}

void TransactionHistory::upload()
{

  ifstream inFile;
  inFile.open("TransactionHistory.txt");

  if ( !inFile.is_open() )
  {
    cout << "Error opening TransactionHistory.txt for input" << endl;
    return;
  }

  string check = "Continue";
  int serialNumber;
  char useless;
  int month;
  int date;
  int year;
  string type;
  double amount;
  string nextWord;
  string description;
  string location;
  string isReal;
  string category;
  Transaction nextTransaction;


  while (check != "Stop")
  {

    inFile >> useless; // '#'
    inFile >> serialNumber;
    inFile >> month;
    inFile >> useless; // '-'
    inFile >> date;
    inFile >> useless; // '-'
    inFile >> year;
    inFile >> type;
    inFile >> useless; // '$'
    inFile >> amount;

    inFile.clear();
    inFile.ignore(100,'\n');
    getline(inFile, description);

    inFile >> location;
    inFile >> isReal;
    inFile >> category;

    nextTransaction.setSerialNumber(serialNumber);
    nextTransaction.setMonth(month);
    nextTransaction.setDate(date);
    nextTransaction.setYear(year);
    nextTransaction.setDescription(description);
    nextTransaction.setAmount(amount);

    if (location == "Bank")
    {
      nextTransaction.setLocation(Bank);
    }
    else if (location == "Cash")
    {
      nextTransaction.setLocation(Cash);
    }
    else
    {
      nextTransaction.setLocation(UnknownLocation);
    }

    if (isReal == "Real")
    {
      nextTransaction.setIsReal(true);
    }

    if (type == "Income")
    {
      nextTransaction.setType(Income);
    }
    else if (type == "Expense")
    {
      nextTransaction.setType(Expense);
    }
    else if (type == "Tithe")
    {
      nextTransaction.setType(Tithe);
    }
    else
    {
      nextTransaction.setType(UnknownType);
    }

    if (category == "Landscape")
    {
      nextTransaction.setCategory(Landscape);
    }
    else if (category == "JerseyMikes")
    {
      nextTransaction.setCategory(JerseyMikes);
    }
    else if (category == "tutoring")
    {
      nextTransaction.setCategory(tutoring);
    }
    else if (category == "gift")
    {
      nextTransaction.setCategory(gift);
    }
    else if (category == "gas")
    {
      nextTransaction.setCategory(gas);
    }
    else if (category == "groceries")
    {
      nextTransaction.setCategory(groceries);
    }
    else
    {
      nextTransaction.setCategory(unknownCategory);
    }

    list.push_back(nextTransaction);
    inFile >> check;

  }

  inFile >> balance.cash;
  inFile >> balance.bank;
  inFile >> balance.check;
  inFile >> titheDue;

}

void TransactionHistory::save()
{

  ofstream outFile;

  outFile.open("TransactionHistory.txt");

  if ( !outFile.is_open() )
  {
    cout << "Error opening TransactionHistory.txt for output" << endl;
    return;
  }

  Transaction currTransaction;

  for (int i = 0; i < list.size(); ++i)
    {

      currTransaction = list.at(i);

      outFile << '#' << currTransaction.getSerialNumber() << endl;

      outFile << currTransaction.getMonth() << '-';
      outFile << currTransaction.getDate() << '-';
      outFile << currTransaction.getYear() << endl;

      if (currTransaction.getType() == Income)
      {
        outFile << "Income" << endl;
      }
      else if (currTransaction.getType() == Expense)
      {
        outFile << "Expense" << endl;
      }
      else if (currTransaction.getType() == Tithe)
      {
        outFile << "Tithe" << endl;
      }
      else
      {
        outFile << "Type_unknown" << endl;
      }

      outFile << "$" << currTransaction.getAmount() << endl;

      outFile << currTransaction.getDescription() << endl;

      if (currTransaction.getLocation() == Bank)
      {
        outFile << "Bank" << endl;
      }
      else if (currTransaction.getLocation() == Cash)
      {
        outFile << "Cash" << endl;
      }
      else
      {
        outFile << "Location_unknown" << endl;
      }

      if (currTransaction.getIsReal())
      {
        outFile << "Real" << endl;
      }
      else
      {
        outFile << "Projected" << endl;
      }

      if (currTransaction.getCategory() == Landscape)
      {
        outFile << "Landscape" << endl;
      }
      else if (currTransaction.getCategory() == JerseyMikes)
      {
        outFile << "JerseyMikes" << endl;
      }
      else if (currTransaction.getCategory() == tutoring)
      {
        outFile << "tutoring" << endl;
      }
      else if (currTransaction.getCategory() == gas)
      {
        outFile << "gas" << endl;
      }
      else if (currTransaction.getCategory() == groceries)
      {
        outFile << "groceries" << endl;
      }
      else
      {
        outFile << "unknownCategory";
      }

      outFile << endl << endl;

      if (i + 1 != list.size())
      {
        outFile << "Continue" << endl << endl;
      }
      else
      {
        outFile << "Stop" << endl;
      }

    }

    outFile << balance.cash << endl;
    outFile << balance.bank << endl;
    outFile << balance.check << endl;
    outFile << titheDue << endl;

    outFile.close();

}

void TransactionHistory::edit()
{

  char choice;

  cout << "What do you want to edit?\n"
       << "c - Confirm projected transaction\n"
       << "p - Paycheck\n"
       << "o - Other\n";

  cin >> choice;

  switch(choice)
  {

      case 'c' :
        confirmProjected();
        break;
      case 'p' :
        paycheck();
        break;
      case 'o' :
          editAny();
      default:
        cout << "Invalid option. Please try again.\n\n";
        edit();

}

void TransactionHistory::paycheck()
{

  int month1,
      date1,
      year1,
      month2 = 0;
      date2,
      year2;
  char useless;

  cout << "Date?\n"
  cin >> month1 >> useless >> date1 >> useless >> year1;

  sort();
  vector<Transaction>::iterator iter = list.begin();

  for (iter; iter < list.end(); iter++)
  {

    if (iter->getCategory() = JerseyMikes)
    {
      month2 = iter->getMonth();
      date2 = iter->getDate();
      year2 = iter->getYear();
      break;
    }

  }

  if (month2 = 0)
  {
    month2 = 1;
    date2 = 1;
    year2 = 1900;
  }

  for (iter = list.begin(); iter < list.end(); iter++)
  {

    if (//between the two dates


/*

void TransactionHistory::confirmProjected()
{
  Transaction currTransaction;
  vector<Transaction> projectedList = {};
  int number;

  cout << endl << "Here are your options:" << endl << endl;

  for (int i = 0; i < list.size(); ++i)
    {
      currTransaction = list.at(i);

      if (!currTransaction.getIsReal())
      {
        projectedList.push_back(currTransaction);

        cout << '#' << currTransaction.getSerialNumber() << endl;

        cout << currTransaction.getMonth() << '-';
        cout << currTransaction.getDate() << '-';
        cout << currTransaction.getYear() << endl;

        if (currTransaction.getType() == Income)
        {
          cout << "+";
        }
        else
        {
          cout << "-";
        }

        cout << "$" << currTransaction.getAmount() << endl;

        cout << currTransaction.getDescription() << endl << endl;

      }  

    }

  cout << "Enter the serial number of your choice." << endl;
  cin >> number;

  for (int i = 0; i < projectedList.size(); ++i)
    {
      currTransaction = projectedList.at(i);

      if (number == currTransaction.getSerialNumber())
      {
        updateProjected
      }
    }


}

void TransactionHistory::confirmProjected()
{

  char answer;
  char useless;
  int month;
  int date;
  int year;
  char typeChar;
  transactionType type;
  Transaction* currTransaction;
  vector<Transaction*> options;


  cout << "Print available options? y/n" << endl;
  cin >> answer;

  if (answer == 'y')
  {
    printOptions(expectedList);
  }

  cout << "Please choose a transaction to confirm." << endl << endl;

  cout << "Date:" << endl;
  cin >> month;
  cin >> useless;
  cin >> date;
  cin >> useless;
  cin >> year;

  for (int i = 0; i < expectedList.size(); ++i)
  {

    currTransaction = &expectedList.at(i);

    if ( (currTransaction.getMonth() == month) && 
         (currTransaction.getDate() == date) && 
         (currTransaction.getYear() == year) )
    {
        options.push_back(currTransaction);   
    }

  }

  if (options.size() == 0)
  {
      cout << "No matching transactions." << endl;
      cout << "Please restart your search." << endl << endl;
      confirmProjected();
  }

  else if (option.size() == 1)
  {
      currTransaction = options.at(1);
      confirm(*currTransaction);
  }

  else
  {

    // check description next



}

void TransactionHistory::confirm(Transaction* currTransaction)
{

  char answer;

  cout << "Make any changes? y/n" << endl;
  cin >> answer;

  if (answer == 'y')
  {
  }

  // Move transaction from expectedList to list. Might need to do this in mian().

}

void TransacionHistory::printOptions(vector<Transaction>& expectedList)
{

    Transaction currTransaction;

    for (int i = 0; i < expectedList.size(); ++i)
    {

      currTransaction = expectedList.at(i);

        cout << currTransaction.getMonth() << '-';
        cout << currTransaction.getDate() << '-';
        cout << currTransaction.getYear() << endl;

        cout << "Description: ";
        cout << currTransaction.getDescription() << endl;

        cout << "$" << currTransaction.getAmount() << endl;

        if (currTransaction.getLocation() == Bank)
        {
          cout << "Bank" << endl;
        }
        else if (currTransaction.getLocation() == Cash)
        {
          cout << "Cash" << endl;
        }
        else
        {
          cout << "Location_unknown" << endl;
        }

        if (currTransaction.getIsReal())
        {
          cout << "Real" << endl;
        }
        else
        {
          cout << "Projected" << endl;
        }

        if (currTransaction.getType() == Income)
        {
          cout << "Income" << endl;
        }
        else if (currTransaction.getType() == Expense)
        {
          cout << "Expense" << endl;
        }
        else if (currTransaction.getType() == Tithe)
        {
          cout << "Tithe" << endl;
        }
        else
        {
          cout << "Type_unknown" << endl;
        }

        cout << endl;

    }

}

*/

void TransactionHistory::updateBalance()
{

  char useless;

  cout << "**Current Balance**" << endl;
    cout << "Cash: $" << balance.cash << endl;
    cout << "Bank: $" << balance.bank << endl;
    cout << "Checks: $" << balance.check << endl << endl;

  cout << "Input new balance." << endl;
    cout << "Cash: ";
    cin >> useless >> balance.cash;

  checkForDollarSign(useless);

    cout << "Bank: ";
    cin >> useless >> balance.bank;

  checkForDollarSign(useless);

    cout << "Checks: ";
    cin >> useless >> balance.check;

  checkForDollarSign(useless);

}

void TransactionHistory::sort()
{

  // Sorts by year, month, date, amount, description; respectively, latest to earliest

  if (list.size() <= 1)
  {
    return;
  }

  for (int i = 0; i < list.size(); ++i)
  {

    Transaction currTransaction = list.at(i);

    for (int j = i + 1; j < list.size(); ++j)
    {

      Transaction testTransaction = list.at(j);

      if ( testTransaction.getYear() > currTransaction.getYear() )
      {
        swap( list.at(i), list.at(j) );
      }

      else if ( testTransaction.getYear() == currTransaction.getYear() )
      {

        if ( testTransaction.getMonth() > currTransaction.getMonth() )
        {
          swap( list.at(i), list.at(j) );
        }

        else if ( testTransaction.getMonth() == currTransaction.getMonth() )
        {

          if ( testTransaction.getDate() > currTransaction.getDate() )
          {
              swap( list.at(i), list.at(j) );
          }

          else if ( testTransaction.getDate() == currTransaction.getDate() )
          {

            if ( testTransaction.getAmount() > currTransaction.getAmount() )
            {
              swap( list.at(i), list.at(j) );
            }

            else if ( testTransaction.getAmount() == currTransaction.getAmount() )
            {

              if ( testTransaction.getDescription() >= currTransaction.getDescription() )
              {
                swap( list.at(i), list.at(j) );
              }

            }

          }

        }

      }

    }

  }

}

void TransactionHistory::swap(Transaction& t1, Transaction& t2)
{
  Transaction temp = t1;
  t1 = t2;
  t2 = temp;
}


void TransactionHistory::inputDate(Transaction& newTransaction)
{

  int month;
  int date;
  int year;
  char useless;
  bool good = false;


  cout << "Date?" << endl;

  while ( !good )
  {
      cin >> month;
      cin >> useless;
      cin >> date;
      cin >> useless;
      cin >> year;

      good = valiDate(month, date, year);

  }

  newTransaction.setMonth(month);
  newTransaction.setDate(date);
  newTransaction.setYear(year);


}

bool TransactionHistory::valiDate(int month, int date, int year)
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

void TransactionHistory::inputType(Transaction& newTransaction)
{

  bool okay = false;
  char rp;

  while ( !okay )
    {
      cout << "Real or Projected? r/p" << endl;
      cin >> rp;

      if ( rp == 'r' )
      {
        newTransaction.setIsReal(true);
        okay = true;
      }
      else if ( rp == 'p' )
      {
        newTransaction.setIsReal(false);
        okay = true;
      }
      else
      {
        cout << "That didn't make sense." << endl;
      }

    }

  okay = false;

  while ( !okay )
    {

      okay = true;

      char type;
      cout << "What type of transaction?" << endl;
      cout << "i - Income" << endl;
      cout << "e - Expense" << endl;
      cout << "t - Tithe" << endl;

      cin >> type;

      switch (type)
        {

          case 'i' :
            newTransaction.setType(Income);
            break;

          case 'e' :
            newTransaction.setType(Expense);
            break;

          case 't' :
            newTransaction.setType(Tithe);
            break;

          default:
            okay = false;
            cout << "Invalid option." << endl;
            break;

        }
    }

}

void TransactionHistory::inputLocation(Transaction& newTransaction)
{

  char format;

  cout << "Format?" << endl;

  cout << "b - bank" << endl;
  cout << "c - cash" << endl;

  cin >> format;

  switch (format)
  {
    case 'b' :
      newTransaction.setLocation(Bank);
      break;

    case 'c' :
      newTransaction.setLocation(Cash);
      break;

    default:
      cout << "Invalid input." << endl;
      inputLocation(newTransaction);
      break;
  }

}

void TransactionHistory::inputAmount(Transaction& newTransaction)
{

  double amount;

  if (newTransaction.getCategory() == JerseyMikes)
  {
    double hours;

    cout << "How many hours?" << endl;
    cin >> hours;

    if (hours <= 8)
    {
      amount = hours * 19.5;
    }
    else
    {
      amount = (8 * 15.5) + (hours - 8)*(15.5)*(1.5) + 
        hours*4; // Standard wage + overtime + tips
    }

    cout << "Estimated $" << amount << endl;
    if (hours >= 8)
    {
      cout << "$" << (hours-8)*(15.5)*(1.5) << 
        " Paid overtime" << endl;
    }
    newTransaction.setAmount(amount);

    return;

  }

  char dollarSign;

  cout << "Input amount:" << endl;
  cin >> dollarSign;
  cin >> amount;

  if ( dollarSign != '$' )
  {

    cout << "Please begin amount with a $ sign." << endl << endl;
    inputAmount(newTransaction);

  }

  else
  {
  newTransaction.setAmount(amount);
  }

}

void TransactionHistory::inputDescription(Transaction& newTransaction)
{

  string description;
  cout << "Input description:\n";
  cin.clear();
  cin.ignore(100,'\n');
  getline(cin, description);

  newTransaction.setDescription(description);

}

void TransactionHistory::inputCategory(Transaction& newTransaction)
{

  cout << "Classify this transaction." << endl;

  if (newTransaction.getType() == Income)
  {
    char answer;

    cout << "j - Jersey Mike's" << endl;
    cout << "l - landscape" << endl;
    cout << "t - tutoring" << endl;
    cout << "c - compensation" << endl;
    cout << "g - gift" << endl;
    cout << "o - other" << endl;

    cin >> answer;

    switch(answer)
      {
        case 'l' :
          newTransaction.setCategory(Landscape);
          break;
        case 'j' :
          newTransaction.setCategory(JerseyMikes);
          break;
        case 't' :
          newTransaction.setCategory(tutoring);
          break;
        case 'c' :
          newTransaction.setCategory(compensation);
        case 'g' :
          newTransaction.setCategory(gift);
          break;
        case 'o' :
          newTransaction.setCategory(unknownCategory);
          break;
        default:
          cout << "Invalid answer." << endl << endl;
          inputCategory(newTransaction);
      }

  }

  else if (newTransaction.getType() == Expense)
  {
    char answer;

    cout << "g - gas" << endl;
    cout << "r - groceries" << endl;
    cout << "o - other" << endl;

    cin >> answer;

    switch(answer)
      {
        case 'g' :
          newTransaction.setCategory(gas);
          break;
        case 'r' :
          newTransaction.setCategory(groceries);
          break;
        case 'o' :
          newTransaction.setCategory(unknownCategory);
          break;
        default:
          cout << "Invalid answer." << endl << endl;
          inputCategory(newTransaction);
      }

  }


}

void TransactionHistory::updateBalance(Transaction newTransaction) // Implement Money struct
{

    double amount = newTransaction.getAmount();

    if (newTransaction.getType() != Income)
    {
        amount = -amount;
    }


    if (newTransaction.getLocation() == Cash)
    {
        balance.cash += amount;
    }
    else if (newTransaction.getLocation() == Check)
    {
        balance.check += amount;
    }
    else
    {
        balance.bank += amount;
    }

    if ((newTransaction.getType() == Income) && (newTransaction.getCategory() != compensation))
    {
      titheDue += amount / 10;
    }
    else if (newTransaction.getType() == Tithe)
    {
      titheDue -= amount;
    }

}

void TransactionHistory::allocateSerialNumber(Transaction& newTransaction)
{

  int number = rand() % 900000 + 100000;
  bool good = false;
  Transaction currTransaction;

  while (!good)
    {

      good = true;

      for (int i = 0; i < list.size(); ++i)
        {

          currTransaction = list.at(i);

          if (currTransaction.getSerialNumber() == number)
          {
            good = false;
            ++number;
            break;
          }

        }

    }


}

double TransactionHistory::getBalance()
{
  return balance.cash + balance.bank + balance.check;
}

double TransactionHistory::getExpectedBalance()
{

  vector<Transaction> expectedList;
  Transaction currTransaction;
  double expectedAmount;

  for (int i = 0; i < list.size(); ++i)
    {

      currTransaction = list.at(i);

      if (!currTransaction.getIsReal())
      {
        expectedList.push_back(currTransaction);
        expectedAmount += currTransaction.getAmount();
      }

    }

  return expectedAmount - titheDue;

}

void TransactionHistory::checkForDollarSign(char useless)
{

  if (isdigit(useless))
  {
    cout << "Please start with a dollar sign." << endl;
    updateBalance();
  }

}

/*

void TransactionHistory::printReport()
{

  int year;
  int month;
  string monthString = "";
  bool match = false;
  string filename = "";

  sort();

  cout << "What year?" << endl;
  cin >> year;

  cout << "What month?" << endl <<
    "0 - All" << endl <<
    "1 - January" << endl <<
    "2 - February" << endl <<
    "3 - March" << endl <<
    "4 - April" << endl <<
    "5 - May" << endl <<
    "6 - June" << endl <<
    "7 - July" << endl <<
    "8 - August" << endl <<
    "9 - September" << endl <<
    "10 - October" << endl <<
    "11 - November" << endl <<
    "12 - Decembeer" << endl;

  cin >> month;

  vector<Transaction> reportList;

  vector<Transaction>::iterator iter;

  for (iter; iter < list.end(); iter++)
    {

      // Will only print transactions whose year and month match. 
      // If month is <1 or >12, any month will match.
      if (iter->getYear() == year) 
      {
        if ( (month < 1) || (month > 12) )
        {
          match = true;
        }
        else
        {
          if (iter->getMonth() == month)
          {
            match = true;
          }
        }
      }

      if (match)
      {
        reportList.push_back(*iter);
      }

    }

  if ( (month >= 1) && (month <= 12) )
  {
    monthString = toString(month);
  }

  filename = monthString + year + "Report.txt";

  ofstream outFile;
  outFile.open(filename);

  outFile << year << " REPORT" << endl;
  outFile << "--------------------" << endl << endl;

  for (iter; iter < reportList.end(); iter++)
    {

      outFile << iter ->

    }

}

string TransactionHistory::toString(int month)
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
        return "";
    }

}
*/