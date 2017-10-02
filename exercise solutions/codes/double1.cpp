
// test iterators for doubly-linked list

#include <iostream.h>
#include "double1.h"

void main(void)
{
   Double<int> L;
   L.Insert(0,2);
   L.Insert(1,6);
   L.Insert(2,8);
   L.Insert(1,4);
   cout << "List is " << L << endl;
   L.ResetLeft();
   if (L.Front())
      cout << "Positioned at front of list ";
   if (!L.End())
      cout << "but not at the end" << endl;
   cout << "List in sequence is ";
   int x;
   while (L.Current(x)) {
     cout << x << ' '; 
     L.Next();
     }
   cout << endl;

   L.ResetRight();
   if (L.End())
      cout << "Positioned at end of list ";
   if (!L.Front())
      cout << "but not at the front" << endl;

   cout << "List in reverse order is ";
   while (L.Current(x)) {
     cout << x << ' '; 
     L.Previous();
     }
   cout << endl;
}
