

#include<iostream.h>
#include "movelist.h"
void main(void)
{
   int x, n = 15;
   LinearList<int> L(20);
   for (int i = 0; i < n; i++)
      L.Insert(0,i);
   cout << "The list is" << endl;
   cout << L << endl;
   L.Reset();
   cout << "At front, should return true " << L.Front() << endl;
   L.Current(x);
   cout << "First element is " << x << endl;
   L.Next();
   L.Current(x);
   cout << "Second element is " << x << endl;
   L.Next();
   L.Next();
   L.Current(x);
   cout << "Fourth element is " << x << endl;
   L.Previous();
   L.Current(x);
   cout << "Third element is " << x << endl;
   cout << "Not at end, should return false " << L.End() << endl;
   cout << "Not at front, should return false " << L.Front() << endl;
}
