// test currency class with friend

#include <iostream>
#include "currencyFriend.h"

using namespace std;

int main()
{
   currency g, h(plus, 3, 50), i, j;

   // try out both forms of setValue
   g.setValue(minus, 2, 25);
   i.setValue(-6.45);

   // do an add and output
   j = h + g;
   cout << h << " + " << g << " = " << j << endl;

   // do an increment and output
   cout << i << " incremented by " << h
        << " is " << (i += h) << endl;

   // do two adds in a sequence
   j = i + g + h;
   cout << i << " + " << g << " + " 
        << h << " = " << j << endl;

   // do an increment and add
   cout << "Increment " << i << " by " << g
        << " and then add " << h << endl;
   j = (i += g) + h;
   cout << "Result is " << j << endl;
   cout << "Incremented object is " << i << endl;

   // test the exception
   cout << "Attempting to initialize with cents = 152" << endl;
   try {i.setValue(plus, 3, 152);}
   catch (illegalParameterValue e) {
      cout << "Caught thrown exception" << endl;
      e.outputMessage();
       }
   return 0;
}
