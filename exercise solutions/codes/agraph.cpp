
// exercise 12.11


#include <iostream.h>
#include "xcept.h"
#include "make2db.h"


void Store(int **a, int n, int i, int j, int v)
{// Set A(i,j) equal to v.  v must be 0 or 1.
 // Diagonal of A is not stored in a.  A is
 // n x n and a is [0:n-2,0:n-1].
 // Throw OutOfBounds exception if i or j invalid.
 // Throw BadInput exception if is not 0 or 1.
 // Throw MustBeZero if v not zero but should be.
   if (i < 1 || i > n || j < 1 || j > n)
      throw OutOfBounds();
   if (v < 0 || v > 1)
      throw BadInput();

   if (i < j) // upper triangle
      a[i-1][j-1] = v;
   else if (i > j) // lower triangle
           a[i-2][j-1] = v;
        else // diagonal entry
           if (v) throw MustBeZero();
}

int Retrieve(int ** a, int n, int i, int j)
{// Return value of A(i,j).
 // Throw OutOfBounds exception if i or j invalid.
   if (i < 1 || i > n || j < 1 || j > n)
      throw OutOfBounds();

   // diagonal entry is always zero
   if (i == j) return 0;

   // not a diagonal entry
   if (i < j) // upper triangle
      return a[i-1][j-1];
   // lower triangle
   return a[i-2][j-1];
}


void main(void)
{// Test with n = 5.
   int **a;
   int n = 5;
   Make2DArray(a,n-1,n);

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
