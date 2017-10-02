// test currency class with three data members sign,
// dollars, and cents

#include <iostream>
#include "currency.h"

using namespace std;

int main()
{
   currency g, h(plus, 3, 50), i, j;

   // try out both forms of setValue
   g.setValue(minus, 2, 25);
   i.setValue(-6.45);

   // do an add and output
   j = h.add(g);
   h.output();
   cout << " + ";
   g.output();
   cout << " = ";
   j.output(); cout << endl;

   // do an increment and output
   i.output();
   cout << " incremented by ";
   h.output();
   cout << " is ";
   i.increment(h);
   i.output(); cout << endl;

   // do two adds in a sequence
   j = i.add(g).add(h);
   i.output();
   cout << " + ";
   g.output();
   cout << " + ";
   h.output();
   cout << " = ";
   j.output(); cout << endl;

   // do an increment and add
   cout << "Increment ";
   i.output();
   cout << " by ";
   g.output();
   cout << " and then add ";
   h.output();
   cout << endl << "Result is ";
   j = i.increment(g).add(h);
   j.output(); cout << endl;
   cout << "Incremented object is ";
   i.output(); cout << endl;

   // test the exception
   cout << "Attempting to initialize with cents = 152" << endl;
   try {i.setValue(plus, 3, 152);}
   catch (illegalParameterValue e)
   {
       cout << "Caught thrown exception" << endl;
       e.outputMessage();
   }
   return 0;
}
