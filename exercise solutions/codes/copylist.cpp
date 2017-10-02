

#include<iostream.h>
#include "copylist.h"

template <class type>
void Reverse(LinearList<type> L, LinearList<type>& R)
{// R is set to be the reverse of L.
 // If R doesn't have enough space, Insert throws
 // an exception which is not caught.
   int l = L.Length();
   int m = R.Length();
   type x;
   // empty out R
   for (int j = m; j > 0; j--)
      R.Delete(j, x);

   // insert from L
   for (int i = 0; i < l; i++) {
      L.Find(l-i, x); 
      R.Insert(i, x);
      }
}


void main(void)
{
   int x, n = 15;
   LinearList<int> L(20), M(20);
   for (int i = 0; i < n; i++)
      L.Insert(i,i);
   cout << "The list is " << endl;
   cout << L << endl;
   cout << "After reversal, the list is " << endl;
   Reverse(L, M);
   cout << M << endl;
   M.Delete(n,x);
   Reverse(M, L);
   cout << "After deleting the last element and reversing," << endl;
   cout << "the list is " << endl;
   cout << L << endl;
}
