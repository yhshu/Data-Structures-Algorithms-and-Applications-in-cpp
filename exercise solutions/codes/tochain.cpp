

#include<iostream.h>
#include "llist.h"
#include "echain.h"

template<class T>
void ArrayToChain(const LinearList<T>& L, Chain<T>& C)
{// Convert L to a chain C.
 // Do not catch exceptions that might be thrown.
   T x;
   C.Erase(); // empty the chain
   for (int i = L.Length(); i > 0; i--) {
      // copy i'th element of L
      L.Find(i,x);
      C.Insert(0,x);
      }
}

void main(void)
{
   int n = 15;
   LinearList<int> L(20);
   Chain<int> C;
   for (int i = 0; i < n; i++)
      L.Insert(0,i);
   cout << "The formula-based list is" << endl;
   cout << L << endl;

   ArrayToChain(L,C);
   cout << "The chain is" << endl;
   cout << C << endl;
}
