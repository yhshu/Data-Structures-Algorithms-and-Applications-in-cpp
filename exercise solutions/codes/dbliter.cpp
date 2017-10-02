

// test doubly-linked circular list iterator class

#include <iostream.h>
#include "dblcirc.h"
#include "dbliter.h"

void main(void)
{
   DoubleCircular<int> L;
   L.Insert(0,2);
   L.Insert(1,6);
   L.Insert(2,8);
   L.Insert(1,4);
   cout << "List is " << L << endl;
   DoubleCircularIterator<int> p;
   int *q = p.Initialize(L);
   cout << "List in sequence is ";
   while (q) {
     cout << *q << ' '; 
     q = p.Next();
     }
   cout << endl;
}
