// test sorted chain class

#include <iostream.h>
#include "sochain.h"

void main(void)
{
   SortedChain<int, int> Z;
   int x;
   Z.Insert(2).Insert(6).Insert(4);
   cout << "The chain is " << Z << endl;
   cout << "Its length is " << Z.Length() << endl;
   Z.Delete(2,x);
   cout << "Deleted " << x << endl;
   cout << Z << endl;
   Z.Insert(1).Delete(6,x);
   cout << Z << endl;
   Z.Insert(8).Insert(9).Search(8,x);
   cout << "Found " << x << endl;
   Z.Insert(7).Delete(9,x);
   cout << Z << endl;
   try {Z.DistinctInsert(7);}
   catch (BadInput)
      {cout << "Attempt to insert duplicate element" << endl;}
   cout << Z << endl;
   Z.DistinctInsert(10);
   cout << Z << endl;
}
