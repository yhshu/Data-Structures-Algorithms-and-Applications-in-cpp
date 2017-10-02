
#include <iostream.h>
#include "ccircle.h"
#include "circiter.h"

template<class T>
void Merge(const Circular<T>& A,
          const Circular<T>& B, Circular<T>& C)
{// Merge from A and B to get C.
   CircularIterator<T> a,  // iterator for A
                       b;  // iterator for B
   T *DataA = a.Initialize(A);
                    // pointer to an element of A
   T *DataB = b.Initialize(B);
                    // pointer to an element of B
   C.Erase(); // empty out C

   // merge until one of A and B is empty
   while (DataA && DataB) {
      if (*DataA <= *DataB) {// A goes next
         C.Append(*DataA);
         DataA = a.Next();}
      else {// B is smaller
         C.Append(*DataB);
         DataB = b.Next();}
      }

   // append the rest
   // at most one of A and B is nonempty now
   if (DataA) while(DataA) {// A is not empty
                 C.Append(*DataA);
                 DataA = a.Next();
                 }
   else while(DataB) {// B is not empty
           C.Append(*DataB);
           DataB = b.Next();
           }
}

void main()
{
   int n = 10, m = 5;
   Circular<int> A, B, C;

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

   Merge(A,B,C);

   cout << "Merged list is" << endl;
   cout << C << endl;
}
