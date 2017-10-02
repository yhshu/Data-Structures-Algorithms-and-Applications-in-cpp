
#include <iostream.h>
#include "minpq.h"

void main(void)
{
   MinPQ<int> H(4);
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
   cout << "The min element is " << H.Min() << endl;
   H.DeleteMin(x);
   cout << "Deleted min element " << x << endl;
   H.DeleteMin(x);
   cout << "Deleted min element " << x << endl;
   cout << "Elements in linear list order "
        << H << endl;
}
