
// alternating meld of two doubly-linked circular lists

#include <iostream.h>
#include "dblcirc2.h"
#include "dbliter.h"

template<class T>
void Alternate(const DoubleCircular<T>& A,
          const DoubleCircular<T>& B, DoubleCircular<T>& C)
{// Meld alternately from A and B to get C.
   // initialize
   DoubleCircularIterator<T> a,  // iterator for A
                             b;  // iterator for B
   T *DataA = a.Initialize(A);   // first element of A
   T *DataB = b.Initialize(B);   // first of B
   C.Erase(); // empty C

   // create result
   while (DataA && DataB) {
      C.Append(*DataA);
      C.Append(*DataB);
      DataA = a.Next();
      DataB = b.Next();
      }

   // append the rest
   // at most one of A and B can be nonempty now
   while(DataA) {
      C.Append(*DataA);
      DataA = a.Next();
      }

   while(DataB) {
      C.Append(*DataB);
      DataB = b.Next();
      }
}

void main()
{
   int n = 10, m = 5;
   DoubleCircular<int> A, B, C;

   // create A
   for (int i = 0; i < n; i++)
      A.Insert(0, 2*(n - i));
   
   // create B
   for (i = 0; i < m; i++)
      B.Insert(0,2*(n - i) + 1);
   
   cout << "First list is" << endl;
   cout << A << endl;
   cout << "Second list is" << endl;
   cout << B << endl;

   Alternate(A,B,C);

   cout << "Melded list is" << endl;
   cout << C << endl;
}
