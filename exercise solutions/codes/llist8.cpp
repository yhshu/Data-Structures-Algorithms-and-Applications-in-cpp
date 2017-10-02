

#include<iostream.h>
#include "hlist.h"

template <class T>
void Reverse(LinearList<T>& L)
{// In-place reversal of the list L.
   int l = L.Length();
   T x;
   for (int i = 0; i < l - 1; i++) {
      L.Delete(l,x);  // delete last element
      L.Insert(i,x);  // insert as i'th
      }
}

void main(void)
{
   int x, n = 15;
   LinearList<int> L(20);
   for (int i = 0; i < n; i++)
      L.Insert(i,i);
   cout << "The list is " << endl;
   cout << L << endl;
   cout << "After reversal, the list is " << endl;
   Reverse(L);
   cout << L << endl;
   L.Delete(n,x);
   Reverse(L);
   cout << "After deleting the last element and reversing," << endl;
   cout << "the list is " << endl;
   cout << L << endl;
}
