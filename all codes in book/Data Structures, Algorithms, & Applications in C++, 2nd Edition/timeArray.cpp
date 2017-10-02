// run time for simple square matrix add

#include <iostream>
#include<time.h>
#include "make2dArrayNoCatch.h"

using namespace std;

#pragma optimize("t", on)

template<class T>
void matrixAdd( T **a, T **b, T **c, int numberOfRows,
                                     int numberOfColumns)
{// Add matrices a and b to obtain matrix c.
   for (int i = 0; i < numberOfRows; i++)
      for (int j = 0;  j < numberOfColumns; j++)
         c[i][j] = a[i][j] + b[i][j];
}
int main()
{
   int **a, **b, **c;
   int n = 500;  // matrix size
   int m = 500;  // number of repetitions
   make2dArray(a,n,n);
   make2dArray(b,n,n);
   make2dArray(c,n,n);

   // initialize the matrices a and b
   for (int i = 0; i < n; i++)
      for (int j = 0; j < n; j++)
      {
         if (i >= j && i - j < 4)
            a[i][j] = 3;
         else
            a[i][j] = 0;
         if (i <= j && j - i < 2)
            b[i][j] = 5;
         else
            b[i][j] = 0;
      }

   long startTime = clock();
   for (int i = 1; i <= m; i++)
      matrixAdd(a,b,c,n,n);
   double elapsedTime = ((double) (clock() - startTime)) / m;
   cout << "Add time for n = " << n << " is "
        << elapsedTime << " milliseconds" << endl;

   return 0;
}
