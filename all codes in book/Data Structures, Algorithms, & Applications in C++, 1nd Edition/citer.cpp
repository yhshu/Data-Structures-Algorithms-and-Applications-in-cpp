// test chain iterator class

#include <iostream.h>
#include "chain.h"
#include "citer.h"

void main(void)
{
   Chain<int> L;
   L.Insert(0,2);
   L.Insert(1,6);
   L.Insert(2,8);
   L.Insert(1,4);
   cout << "List is " << L << endl;
   ChainIterator<int> p;
   int *q = p.Initialize(L);
   cout << "List in sequence is ";
   while (q) {
     cout << *q << ' '; 
     q = p.Next();
     }
   cout << endl;
}
