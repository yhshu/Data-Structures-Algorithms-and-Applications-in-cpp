// test currency class

#include <iostream.h>
#include "curr1.h"

void main(void)
{
   Currency g, h, i, j;
   g.Input();
   h.Input();


   i = g.Subtract(h);
   g.Output();
   cout << " minus ";
   h.Output();
   cout << " = ";
   i.Output();
   cout << endl;

   cout << "10% of ";
   g.Output();
   cout << " is ";
   g.Percent(10).Output();
   cout << endl;

   cout << "3 times ";
   g.Output();
   cout << " is ";
   g.Multiply(3).Output();
   cout << endl;

   cout << "Half of ";
   g.Output();
   cout << " is ";
   g.Divide(2).Output();
   cout << endl;
}
