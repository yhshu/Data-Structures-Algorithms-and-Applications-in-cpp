// includes >>, -, /, *, %
// and overloading of =


#ifndef Currency_
#define Currency_

#include <iostream.h>
#include <stdlib.h>

enum sign {plus, minus};

class Currency {
   friend istream& operator>>(istream& in, Currency& x);
   public:
      // constructor
      Currency(sign s = plus, unsigned long d = 0,
                              unsigned int c = 0);
      // destructor
      ~Currency() {}
      Currency operator=(int x)
         {amount = x;
          return *this;}
      Currency operator=(float x)
         {amount = (x + 0.001) * 100;
          return *this;}
      sign Sign() const
        {if (amount < 0) return minus;
         else return plus;}
      unsigned long Dollars() const
        {if (amount < 0) return (-amount) / 100;
         else return amount / 100;}
      unsigned int Cents() const
        {if (amount < 0)
            return -amount - Dollars() * 100;
         else return amount - Dollars() * 100;}
      Currency operator+(const Currency& x) const;
      Currency operator-(const Currency& x) const;
      Currency operator%(float x) const;
      Currency operator*(float x) const;
      Currency operator/(float x) const;
      Currency& operator+=(const Currency& x)
        {amount += x.amount; return *this;}
      void Output(ostream& out) const;
   private:
      long amount;
};

Currency::Currency(sign s, unsigned long d,
                           unsigned int c)
{// Create a Currency object.
   if (c > 99)
      {// too many cents
       cerr << "Cents should be < 100" << endl;
       exit(1);}
   
   amount = d * 100 + c;
   if (s == minus) amount = -amount;
}

   
Currency Currency::operator+(const Currency& x) const
{// Add x and *this.
   Currency y;
   y.amount = amount + x.amount;
   return y;
}

Currency Currency::operator-(const Currency& x) const
{// Subtract x from *this.
   Currency y;
   y.amount = amount - x.amount;
   return y;
}

Currency Currency::operator%(float x) const
{// Return x% of *this.
   Currency y;
   y.amount = (amount * x) / 100;
   return y;
}

Currency Currency::operator*(float x) const
{// Return x * (*this).
   Currency y;
   y.amount = amount * x;
   return y;
}

Currency Currency::operator/(float x) const
{// Return (*this) / x.
   Currency y;
   y.amount = amount / x;
   return y;
}

void Currency::Output(ostream& out) const
{// Insert currency value into stream out.
   long a = amount;
   if (a < 0) {out << '-';
               a = -a;}
   long d = a / 100; // dollars
   out << '$' << d << '.';
   int c = a - d * 100; // cents
   if (c < 10) out << "0";
   out << c;
}

// overload <<
ostream& operator<<(ostream& out, const Currency& x)
   {x.Output(out); return out;}

// overload >>
istream& operator>>(istream& in, Currency& x)
{// Input a currency amount.

   float y;
   cout << "Enter the currency amount as "
        << "a floating point number as in dd.cc or -dd.cc"
        << endl;

   in >> y;
   x.amount = (y + 0.001) * 100;
   return in;
}

#endif
