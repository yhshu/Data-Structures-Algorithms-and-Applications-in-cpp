

#include<iostream.h>
#include "nmatrix.h"

void main(void)
{
   const int n = 6;
   NMatrix<int> X(n);

   for (int i = 1; i <= n; i++) {
      X.Store(i,i,1);       // first column
      X.Store(n+i,i,n);     // last column
      X.Store(2*n+i+1,i,i); // diagonal
      }

   for (i = 1; i <= n; i++) {
      for (int j = 1; j <= n; j++)
         cout << X.Retrieve(i,j) << ' ';
      cout << endl;
      }
}
