

// test circular list with head node iterator class

#include <iostream.h>
#include "hcircle.h"
#include "hciter.h"

void main(void)
{
   HCircular<int> L;
   L.Insert(0,2);
   L.Insert(1,6);
   L.Insert(2,8);
   L.Insert(1,4);
   cout << "List is " << L << endl;
   HCircularIterator<int> p;
   int *q = p.Initialize(L);
   cout << "List in sequence is ";
   while (q) {
     cout << *q << ' '; 
     q = p.Next();
     }
   cout << endl;
}
