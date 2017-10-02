
// reverse a doubly linked circular list
// with head node

#include <iostream.h>
#include "dblcirc7.h"

void main(void)
{
   int n = 11;
   HDoubleCircular<int> C;
   for (int i = 0; i < n; i++)
      C.Insert(0,i);
   cout << "The list is" << endl;
   cout << C << endl;

   C.Reverse();
   cout << "After reversal, the list is" << endl;
   cout << C << endl;
}
