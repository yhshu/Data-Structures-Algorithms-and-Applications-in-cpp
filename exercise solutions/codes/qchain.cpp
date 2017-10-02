

// test sorted chain search

#include <iostream.h>
#include "qchain.h"

void main(void)
{
   Chain<int> L;
   L.Insert(0,9).Insert(0,8).Insert(0,7).Insert(0,6);
   L.Insert(0,5).Insert(0,4).Insert(0,3).Insert(0,2);
   L.Insert(0,1);
   cout << "List is " << L << endl;
   cout << "1 is in position " << L.SortedSearch(1) << endl;
   cout << "2 is in position " << L.SortedSearch(2) << endl;
   cout << "6 is in position " << L.SortedSearch(6) << endl;
   cout << "8 is in position " << L.SortedSearch(8) << endl;
   cout << "9 is in position " << L.SortedSearch(9) << endl;
   cout << "0 is in position " << L.SortedSearch(0) << endl;
}
