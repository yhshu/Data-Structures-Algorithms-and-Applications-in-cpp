


// test iterator for doubly-linked circular
// list with head node

#include <iostream.h>
#include "hdblcirc.h"
#include "hdbliter.h"

void main(void)
{
   HDoubleCircular<int> L;
   L.Insert(0,2);
   L.Insert(1,6);
   L.Insert(2,8);
   L.Insert(1,4);
   cout << "List is " << L << endl;
   HDoubleCircularIterator<int> p;
   int *q = p.Initialize(L);
   cout << "List in sequence is ";
   while (q) {
     cout << *q << ' '; 
     q = p.Next();
     }
   cout << endl;
}
