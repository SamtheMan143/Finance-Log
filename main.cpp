/******************************************************************************
Samuel van der Veen
8-1-23
Finance Log
Logs transactions of various types in a vector, keeping track of balance, projected balance, tithe due, etc.
******************************************************************************/

#include <iostream>
#include <memory>
#include <vector>
#include <string>
#include <iomanip>

#include "TransactionHistory.h"

void printBibleVerse();

void printMenu();

void executeMenu(TransactionHistory& transactions, char menuChoice, bool& quit);

void Prov_13_11();
void Prov_15_16();
void Prov_16_16();
void Psalm_19_10();
void Prov_23_v_4_5();
void Prov_22_9();
void Prov_22_7();
void Hebrews_13_v_5_6();
void FirstTimothy_6_10();

int main()
{

  cout << "Welcome, Samuel." << endl << endl;

  cout << fixed << setprecision(2);

  TransactionHistory transactions;
  transactions.upload();

  char menuChoice;
  bool quit = false;

  printBibleVerse();

  while ( !quit )
    {

      printMenu();
      cin >> menuChoice;

      executeMenu(transactions, menuChoice, quit);

    }

  transactions.save();

  cout << "Success!" << endl;

  return 0;
}


void printMenu()
{

  cout << "\nPlease choose an option:" << endl;
  cout << "t - Transaction" << endl;
  cout << "e - Edit transaction" << endl;
  cout << "r - Print report" << endl;
  cout << "b - Print balance" << endl;
  cout << "u - Update balance" << endl;
  cout << "q - Quit" << endl;

}

void executeMenu(TransactionHistory& transactions, char menuChoice, bool& quit)
{

  switch (menuChoice)
    {

      case 't' :
        transactions.addTransaction();
        break;

      case 'e' :
        //transactions.edit();
        break;

      case 'r' :
        //transactions.printReport();
        break;

      case 'b' :
        // TODO: Print balance
        break;

      case 'u' :
        transactions.updateBalance();
        break;

      case 'q' :
        quit = true;
        break;

      default:
        cout << "Invalid input." << endl;
        break;

    }


}

void printBibleVerse()
{

  srand( time(0) );

  int discriminant = rand() % 9;

  switch (discriminant)
    {

      case 0:
        Prov_13_11();
        break;
      case 1:
        Prov_15_16();
        break;
      case 2:
        Prov_16_16();
        break;
      case 3:
        Psalm_19_10();
        break;
      case 4:
        Prov_23_v_4_5();
        break;
      case 5:
        Prov_22_9();
        break;
      case 6:
        Prov_22_7();
        break;
      case 7:
        Hebrews_13_v_5_6();
        break;
      case 8:
        FirstTimothy_6_10();
        break;
      default:
        break;

    }

}

void Prov_13_11()
{
  cout << "Wealth gained hastily will dwindle," << endl;
  cout << "but whoever gathers little by little will increase it." << endl;
  cout << "Proverbs 13:11" << endl << endl;
}

void Prov_15_16()
{
  cout << "Better is a little with the fear of the Lord" << endl;
  cout << "than great treasure and trouble with it." << endl;
  cout << "Proverbs 15:16" << endl << endl;
}

void Prov_16_16()
{
  cout << "How much better to get wisdom than gold," << endl;
  cout << "to choose understanding rather than silver!" << endl;
  cout << "Proverbs 16:16" << endl << endl;
}

void Psalm_19_10()
{
  cout << "More to be desired are they than gold, than much fine gold;" << endl;
  cout << "and sweeter than honey, and the honeycomb." << endl;
  cout << "Psalm 19:10" << endl << endl;
}

void Prov_23_v_4_5()
{
  cout << "Do not wear yourself out to get rich;" << endl;
  cout << "have the wisdom to show restraint." << endl;
  cout << "Cast but a glance at riches, and they are gone," << endl;
  cout << "for they will surely sprout wings and" << endl;
  cout << "fly off to the sky like an eagle." << endl;
  cout << "Proverbs 23:4-5" << endl << endl;
}

void Prov_22_9()
{
  cout << "A generous man will himself be blessed," << endl;
  cout << "for he shares his food with the poor." << endl;
  cout << "Proverbs 22:9" << endl << endl;
}

void Prov_22_7()
{
  cout << "The borrower is the slave to the lender" << endl;
  cout << "Proverbs 22:7" << endl << endl;
}

void Hebrews_13_v_5_6()
{
  cout << "Keep your lives free from the love of money" << endl;
  cout << "and be content with what you have," << endl;
  cout << "because God has said," << endl;
  cout << "\tNever will I leave you;" << endl;
  cout << "\tNever will I forsake you." << endl;
  cout << "So we can say with confidence," << endl;
  cout << "\tThe Lord is my helper;" << endl;
  cout << "\tI will not be afraid." << endl;
  cout << "\tWhat can man do to me?" << endl << endl;
  cout << "Hebrews 13:5-6" << endl << endl << endl;
}

void FirstTimothy_6_10()
{
  cout << "For the love of money is a root of all kinds of evils.\n"
       << "It is through this craving that some have wandered away from the faith\n"
       << "and pierced themselves with many pangs.\n\n"
       << "1 Timothy 6:10\n\n\n";
}
