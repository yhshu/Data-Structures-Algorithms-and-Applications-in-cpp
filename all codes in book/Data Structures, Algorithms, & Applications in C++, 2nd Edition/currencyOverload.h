// currency class with operator overloading

#ifndef currency_
#define currency_

#include <iostream>
#include "myExceptions.h"

using namespace std;

enum signType {plus, minus};

class currency 
{
   public:
      // constructor
      currency(signType theSign = plus,
               unsigned long theDollars = 0,
               unsigned int theCents = 0);
      // destructor
      ~currency() {}
      void setValue(signType, unsigned long, unsigned int);
      void setValue(double);
      signType getSign() const
        {if (amount < 0) return minus;
         else return plus;}
      unsigned long getDollars() const
        {if (amount < 0) return (-amount) / 100;
         else return amount / 100;}
      unsigned int getCents() const
        {if (amount < 0) return -amount - getDollars() * 100;
         else return amount - getDollars() * 100;}
      currency operator+(const currency&) const;
      currency& operator+=(const currency& x)
        {amount += x.amount; return *this;}
      void output(ostream&) const;
   private:
      long amount;
};

currency::currency(signType theSign, unsigned long theDollars,
                                     unsigned int theCents)
{// Create a currency object.
   setValue(theSign, theDollars, theCents);
}

void currency::setValue(signType theSign, unsigned long theDollars,
                                          unsigned int theCents)
{// Set currency value.
   if (theCents > 99)
       // too many cents
       throw illegalParameterValue("Cents should be < 100");
   
   amount = theDollars * 100 + theCents;
   if (theSign == minus) amount = -amount;
}
   
void currency::setValue(double theAmount)
{// Set currency value.
   if (theAmount < 0)
      amount = (long) ((theAmount - 0.001) * 100);
   else
      amount = (long) ((theAmount + 0.001) * 100);
            // 2 decimal digits only
}

currency currency::operator+(const currency& x) const
{// Add x and *this.
   currency result;
   result.amount = amount + x.amount;
   return result;
}

void currency::output(ostream& out) const
{// Insert currency value into stream out.
   long theAmount = amount;
   if (theAmount < 0) {out << '-';
                       theAmount = -theAmount;}
   long dollars = theAmount / 100; // dollars
   out << '$' << dollars << '.';
   int cents = theAmount - dollars * 100; // cents
   if (cents < 10) out << '0';
   out << cents;
}

// overload <<
ostream& operator<<(ostream& out, const currency& x)
   {x.output(out); return out;}

#endif
