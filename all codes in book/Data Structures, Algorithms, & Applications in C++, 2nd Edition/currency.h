// currency class using three data members
// (sign, dollars, and cents) to
// represent an instance/object

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
      signType getSign() const {return sign;}
      unsigned long getDollars() const {return dollars;}
      unsigned int getCents() const {return cents;}
      currency add(const currency&) const;
      currency& increment(const currency&);
      void output() const;
   private:
      signType sign;           // sign of object
      unsigned long dollars;   // number of dollars
      unsigned int cents;      // number of cents
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

   sign = theSign;
   dollars = theDollars;
   cents = theCents;
}
   
void currency::setValue(double theAmount)
{// Set currency value.
   if (theAmount < 0) {sign = minus;
                       theAmount = -theAmount;}
   else sign = plus;

   dollars = (unsigned long) theAmount;
             // extract integer part
   cents = (unsigned int) ((theAmount + 0.001 - dollars) * 100);
             // get two decimal digits
}

currency currency::add(const currency& x) const
{// Add x and *this.
   long a1, a2, a3;
   currency result;
   // convert invoking object to signed integers
   a1 = dollars * 100 + cents;
   if (sign == minus) a1 = -a1;
   
   // convert x to signed integer
   a2 = x.dollars * 100 + x.cents;
   if (x.sign == minus) a2 = -a2;
   
   a3 = a1 + a2;
    
   // convert to currency representation
   if (a3 < 0) {result.sign = minus; a3 = -a3;}
   else result.sign = plus;
   result.dollars = a3 / 100;
   result.cents = a3 - result.dollars * 100;
   
   return result;
}

currency& currency::increment(const currency& x)
{// Increment by x.
   *this = add(x);
   return *this;
}

void currency::output() const
{// Output currency value.
   if (sign == minus) cout << '-';
   cout << '$' << dollars << '.';
   if (cents < 10) cout << '0';
   cout << cents;
}

#endif

