// run time for fast square matrix multiply
// ikj order

#include <iostream>
#include<time.h>
#include "make2dArrayNoCatch.h"

using namespace std;

#pragma optimize("t", on)
void fastSquareMatrixMultiply(int ** a, int ** b, int ** c, int n)
{
   for (int i = 0; i < n; i++)
      for (int j = 0; j < n; j++)
         c[i][j] = 0;

   for (int i = 0; i < n; i++)
      for (int k = 0; k < n; k++)
         for (int j = 0; j < n; j++)
            c[i][j] += a[i][k] * b[k][j];
}

int main()
{
   int **a, **b, **c;
   int n = 2000;  // matrix size
   make2dArray(a,n,n);
   make2dArray(b,n,n);
   make2dArray(c,n,n);

   // initialize the matrices a and b
   for (int i = 0; i < n; i++)
      for (int j = 0; j < n; j++)
      {
         a[i][j] = 2;
         b[i][j] = 3;
      }

   long startTime = clock();
   fastSquareMatrixMultiply(a,b,c,n);
   double elapsedTimeSec = ((double) (clock() - startTime)) / CLOCKS_PER_SEC;
   cout << "Multiply time for n = " << n << " is "
        << elapsedTimeSec << " seconds" << endl;

   return 0;
}
