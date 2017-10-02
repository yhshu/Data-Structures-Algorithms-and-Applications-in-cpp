// run time for add, multiply and transpose using class matrix

#include <iostream>
#include<time.h>
#include "matrix.h"

using namespace std;

#pragma optimize("t", on)
int main()
{
   int n = 500;  // matrix size
   matrix<int> a(n,n), b(n,n), c(n,n);
   int m = 500;  // number of repetitions

   // initialize the matrices a and b
   for (int i = 1; i <= n; i++)
      for (int j = 1; j <= n; j++)
      {
         if (i >= j && i - j < 4)
            a(i, j) = 3;
         else
            a(i, j) = 0;
         if (i <= j && j - i < 2)
            b(i, j) = 5;
         else
            b(i, j) = 0;
      }

   long startTime = clock();
   for (int i = 1; i <= m; i++)
      c = a + b;
   double elapsedTime = ((double) (clock() - startTime)) / m;
   cout << "Add time for n = " << n << " is "
        << elapsedTime << " milliseconds" << endl;

   return 0;
}
