
// reverse the circular list

#include <iostream.h>
#include "bcircle.h"

void main(void)
{
   int n = 11;
   Circular<int> C;
   for (int i = 0; i < n; i++)
      C.Insert(0,i);
   cout << "The list is" << endl;
   cout << C << endl;

   C.Reverse();
   cout << "After reversal, the list is" << endl;
   cout << C << endl;
}
