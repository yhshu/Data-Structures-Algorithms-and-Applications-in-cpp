
#include <iostream.h>
#include "pqlist.h"

void main(void)
{
   MaxPQ<int> H(4);
   int x;
   H.Insert(10).Insert(20).Insert(5);
   cout << "Elements in linear list order " 
        << H << endl;
   try {H.Insert(15);
        cout << "Insert of 15  succeeded" << endl;
        H.Insert(30);
        cout << "Insert of 30  succeeded" << endl;}
   catch (NoMem)
      {cout << "An insert has failed"  << endl;}
   cout << "Elements in linear list order "
        << H << endl;
   cout << "The max element is " << H.Max() << endl;
   H.DeleteMax(x);
   cout << "Deleted max element " << x << endl;
   H.DeleteMax(x);
   cout << "Deleted max element " << x << endl;
   cout << "Elements in linear list order "
        << H << endl;
}
