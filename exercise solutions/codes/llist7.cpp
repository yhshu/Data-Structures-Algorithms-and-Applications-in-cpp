

#include<iostream.h>
#include "llist7.h"
void main(void)
{
   int x, n = 15;
   LinearList<int> L(20);
   for (int i = 0; i < n; i++)
      L.Insert(i,i);
   cout << "The list is " << endl;
   cout << L << endl;
   cout << "After reversal, the list is " << endl;
   cout << L.Reverse() << endl;
   L.Delete(n,x).Reverse();
   cout << "After deleting the last element and reversing," << endl;
   cout << "the list is " << endl;
   cout << L << endl;
}
