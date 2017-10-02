
// test indirect list binary search

#include <iostream.h>
#include "indlist1.h"

void main(void)
{
   IndirectList<int> L(9);
   L.Insert(0,9).Insert(0,8).Insert(0,7).Insert(0,6);
   L.Insert(0,5).Insert(0,4).Insert(0,3).Insert(0,2);
   L.Insert(0,1);
   cout << "List is " << L << endl;
   cout << "1 is in position " << L.BinarySearch(1) << endl;
   cout << "2 is in position " << L.BinarySearch(2) << endl;
   cout << "6 is in position " << L.BinarySearch(6) << endl;
   cout << "8 is in position " << L.BinarySearch(8) << endl;
   cout << "9 is in position " << L.BinarySearch(9) << endl;
   cout << "0 is in position " << L.BinarySearch(0) << endl;
}
