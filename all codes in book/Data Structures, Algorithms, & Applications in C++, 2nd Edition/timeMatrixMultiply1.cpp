// run time for simple square matrix multiply

#include <iostream>
#include<time.h>
#include "make2dArrayNoCatch.h"

using namespace std;

#pragma optimize("t", on)
template<class T>
void squareMatrixMultiply(T **a, T **b, T **c, int n)
{// Multiply the n x n matrices a and b to get c.
   for (int i = 0; i < n; i++)
      for (int j = 0; j < n; j++) {
         T sum = 0;
         for (int k = 0; k < n; k++)
            sum += a[i][k] * b[k][j];
         c[i][j] = sum;
         }
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
   squareMatrixMultiply(a,b,c,n);
   double elapsedTimeSec = ((double) (clock() - startTime)) / CLOCKS_PER_SEC;
   cout << "Multiply time for n = " << n << " is "
        << elapsedTimeSec << " seconds" << endl;

   return 0;
}
