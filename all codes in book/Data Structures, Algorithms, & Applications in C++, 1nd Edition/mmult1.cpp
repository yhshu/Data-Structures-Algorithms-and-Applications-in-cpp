// multipy square matrices

#include <iostream.h>
#include "make2db.h"

template<class T>
void Mult(T **a, T **b, T **c, int n)
{// Multiply the n x n matrices a and b to get c.
   for (int i = 0; i < n; i++)
      for (int j = 0; j < n; j++) {
         T sum = 0;
         for (int k = 0; k < n; k++)
            sum += a[i][k] * b[k][j];
         c[i][j] = sum;
         }
}

void main(void)
{
   int **a, **b, **c;
   Make2DArray(a,2,2);
   Make2DArray(b,2,2);
   Make2DArray(c,2,2);
   a[0][0] = 1; a[0][1] = 2; a[1][0] = 3; a[1][1] = 4;
   b[0][0] = 1; b[0][1] = 2; b[1][0] = 3; b[1][1] = 4;
   Mult(a,b,c,2);
   cout << c[0][0] << ' ' << c[0][1] << endl;
   cout << c[1][0] << ' ' << c[1][1] << endl;
}
