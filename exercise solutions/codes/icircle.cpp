

// reverse a circular list with a head nod

#include <iostream.h>
#include "icircle.h"

void main(void)
{
   int n = 11;
   HCircular<int> C;
   for (int i = 0; i < n; i++)
      C.Insert(0,i);
   cout << "The list is" << endl;
   cout << C << endl;

   C.Reverse();
   cout << "After reversal, the list is" << endl;
   cout << C << endl;
}
