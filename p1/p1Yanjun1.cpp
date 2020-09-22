#include <iostream>
using namespace std;
//an example of implementing a calculation of the balance ammount  
//of a bank account with compound interest accrual.
//Yanjun Lyu
//09/20/20

const int NUM_MONTH_MIN = 1;
const double BALANCE_AMT_MIN = 0;
const double LOWER_BOUND = 1000.00;
const double UPPER_BOUND =  15000.00;
const double LOWER_INTEREST_RATE = 0.0015;
const double MID_INTEREST_RATE = 0.00225;
const double UPPER_INTEREST_RATE = 0.004;

bool accrueInterest(
     double &balanceAmt,
     const int numMonths,
     const bool doPrintEachMonth
     );

bool accrueOneMonthsInterest(
     double &balanceAmt,
     const bool doPrintInfo
     );

#ifdef ANDREW_TEST
#include "andrewTest.h"
#else

int main()
{
  double balanceAmt;
  int numMonths;
  char doPrintInput;
  bool doPrint;

  cout << "Enter the initial balance of the account: ";
  cin >> balanceAmt;
    
  cout << "Enter the number of months to accrue interest: ";
  cin >> numMonths;

  cout << "Show month-by-month results - 'y' for yes, any other for no: ";
  cin >> doPrintInput;


  if (doPrintInput == 'y')
  {
    doPrint = true;
  }
  else
  {
    doPrint = false;
  }
  accrueInterest(balanceAmt,numMonths,doPrint);
  return 0;
}

#endif

bool accrueOneMonthsInterest(
     double &balanceAmt,
     const bool doPrintInfo
     )
{
  double interestAccrued;
  bool isOneMonthValid = false; //for checking if balanceAmt is valid.

  if(balanceAmt < BALANCE_AMT_MIN)
  {
      cout << "ERROR in accrueOneMonthsInterest: balanceAmt must be >= 0, "
      "but the value " << balanceAmt << " was provided!" << endl;
      cout << "Sorry, an error was detected.  Unable to provide results!" 
      << endl;
  }
  else if(doPrintInfo)     
  {
    cout << "Accruing interest for 1 month:" << endl;
    cout << "  Initial balance: " << balanceAmt << endl;

    if(balanceAmt < LOWER_BOUND)
    {
      cout << "  Initial rate: " << LOWER_INTEREST_RATE << endl; 
      interestAccrued = balanceAmt * LOWER_INTEREST_RATE;
      balanceAmt *= (1 + LOWER_INTEREST_RATE);
      cout << "  Interest accrued: " << interestAccrued << endl;
      cout << "  New balance: " << balanceAmt << endl;
    }
    else if(balanceAmt < UPPER_BOUND)
    {
      cout << "  Initial rate: " << MID_INTEREST_RATE << endl; 
      interestAccrued = balanceAmt * MID_INTEREST_RATE;
      balanceAmt *= (1 + MID_INTEREST_RATE);
      cout << "  Interest accrued: " << interestAccrued << endl;
      cout << "  New balance: " << balanceAmt << endl;
    }
    else
    {
      cout << "  Initial rate: " << UPPER_INTEREST_RATE << endl; 
      interestAccrued = balanceAmt * UPPER_INTEREST_RATE;
      balanceAmt *= (1 + UPPER_INTEREST_RATE);
      cout << "  Interest accrued: " << interestAccrued << endl;
      cout << "  New balance: " << balanceAmt << endl;
    }
    isOneMonthValid = true;
  }
  else
  {
    if(balanceAmt < LOWER_BOUND)
    {
      balanceAmt *= (1 + LOWER_INTEREST_RATE);
    }
    else if(balanceAmt < UPPER_BOUND)
    {
      balanceAmt *= (1 + MID_INTEREST_RATE);
    }
    else
    {
      balanceAmt *= (1 + UPPER_INTEREST_RATE);
    }
    isOneMonthValid = true;
  }
  return(isOneMonthValid);
}

bool accrueInterest(
     double &balanceAmt,
     const int numMonths,
     const bool doPrintEachMonth
     )
{
  double iniBalance = balanceAmt;
  double totalInterestAccrued;
  bool isValid = false; //for checking if numMonth is valid.

  if(numMonths < NUM_MONTH_MIN)
  {
    cout << "ERROR in accrueInterest: numMonths must be > 0, but the "
    "value " << numMonths << " was provided!" << endl;
    cout << "Sorry, an error was detected.  Unable to provide results!"
    << endl;  
  }
  else if(accrueOneMonthsInterest(balanceAmt,doPrintEachMonth)) 
  //check if numMonth is valid. 
  {
    for(int i = 0; i < numMonths - 1; i++) 
    //loop should be reduced once since interest 
    //has been accumulated once when checking numMonth.
    {
      accrueOneMonthsInterest(balanceAmt,doPrintEachMonth);
    }
    totalInterestAccrued = balanceAmt - iniBalance;
    cout << "Interest accrued for " << numMonths << " months!" << endl;
    cout << endl;
    cout << "Initial balance: " << iniBalance << endl;
    cout << "Total interest accrued: " << totalInterestAccrued << endl;
    cout << "Final balance: " << balanceAmt << endl;
    isValid = true;
  }

  return(isValid);
}   