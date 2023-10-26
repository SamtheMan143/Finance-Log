#include "Transaction.h"
#include <iostream>
#include <string>
#include <cstring>
#include <vector>
#include <fstream>

struct Money
{
  double cash;
  double bank;
  double check;
  double payPal;
  double Venmo;
};

class TransactionHistory
{

  private:
    vector<shared_ptr<Transaction>> list;
    Money balance;
    double titheDue;

    void sort();
    void swap(Transaction& t1, Transaction& t2);
    void inputDate(Transaction& newTransaction);
    bool valiDate(int month, int date, int year); // Pun intended
    void inputType(Transaction& newTransaction);
    void inputLocation(Transaction& newTransaction);
    void inputAmount(Transaction& newTransaction);
    void inputDescription(Transaction& newTransaction);
    void inputCategory(Transaction& newTransaction);
    void updateBalance(Transaction newTransaction);
    void allocateSerialNumber(Transaction& newTransaction);
    void printOptions(vector<Transaction>& expectedTransactions);
    void checkForDollarSign(char useless);
    string toString(int month);


  public:
    TransactionHistory();
    void addTransaction();
    void confirmProjected();
    void updateBalance();
    void upload();
    void save();
    double getBalance();
    double getExpectedBalance();
    void printReport();

};