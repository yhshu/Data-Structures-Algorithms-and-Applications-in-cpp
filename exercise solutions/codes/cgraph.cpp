
// exercise 12.13


#include <iostream.h>
#include "xcept.h"
#include "swap.h"


void Store(int *a, int n, int i, int j, int v)
{// Set A(i,j) equal to v.  v must be 0 or 1.
 // Only lower triangle of A excluding diagonal
 // is stored in a. A is n x n.
 // a is [0:n(n-1)/2-1].
 // Throw OutOfBounds exception if i or j invalid.
 // Throw BadInput exception if is not 0 or 1.
 // Throw MustBeZero if v not zero but should be.
   if (i < 1 || i > n || j < 1 || j > n)
      throw OutOfBounds();

   if (v < 0 || v > 1) throw BadInput();

   // convert to lower triangle entry
   // if necessary
   if (i < j) // upper triangle
      Swap(i,j);
   if (i > j) // below diagonal
      a[(i-2)*(i-1)/2 + j - 1] = v;
   else // diagonal
      if (v) throw MustBeZero();
}

int Retrieve(int * a, int n, int i, int j)
{// Return value of A(i,j).
 // Throw OutOfBounds exception if i or j invalid.
   if (i < 1 || i > n || j < 1 || j > n)
      throw OutOfBounds();

   // convert to lower triangle entry
   // if necessary
   if (i < j) // upper triangle
      Swap(i,j);
   if (i > j) // below diagonal
      return a[(i-2)*(i-1)/2 + j - 1];
   else // diagonal
      return 0;
}


void main(void)
{// Test with n = 5.
   int *a;
   int n = 5;
   a = new int[n*(n-1)/2];

   // initialize all entries
   for (int i = 1; i <= n; i++)
      for (int j = 1; j <= n; j++)
         Store(a,n,i,j,0);

   // change some to 1
   Store(a,n,1,3,1);
   Store(a,n,3,4,1);
   Store(a,n,5,2,1);
   Store(a,n,2,1,1);

   // output all
   for (i = 1; i <= n; i++) {
      for (int j = 1; j <= n; j++)
         cout << Retrieve(a,n,i,j) << "  ";
      cout << endl;
      }
}
