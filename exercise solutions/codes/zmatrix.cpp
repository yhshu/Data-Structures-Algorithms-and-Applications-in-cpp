
#include<iostream.h>
#include "zmatrix.h"

void main(void)
{
   const int n = 6;
   ZMatrix<int> X(n);

   for (int j = 1; j <= n; j++) {
      X.Store(j,1,j);       // first row
      X.Store(n+j,n,j);     // last row
      X.Store(2*n+j+1,n+1-j,j); // cross diagonal
      }

   for (int i = 1; i <= n; i++) {
      for (int j = 1; j <= n; j++)
         cout << X.Retrieve(i,j) << ' ';
      cout << endl;
      }
}
