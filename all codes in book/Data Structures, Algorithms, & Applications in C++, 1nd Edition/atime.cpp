// time heap sort

#include <iostream.h>
#include <time.h>
#include <stdlib.h>
#include <limits.h>
#include <math.h>
#include "hsort.h"

void main(void)
{
   int a[1001], n, i, step = 10;
   long counter;
   float seconds;
   clock_t start, finish;
   randomize();
   for (n = 10; n <= 1000; n += step)
   {// get time for size n
     start = clock( ); counter = 0;
     while (clock( ) - start < 10 || counter < 100) {
       counter++;
       for (i = 1; i <= n; i++)
          a[i] = rand(); // initialize 
       a[n] = INT_MAX;
       HeapSort(a, n);
     }
     finish = clock( );
     seconds = (finish - start) / CLK_TCK;
     cout << n << ' ' 
          << seconds / counter << endl;
     if (n == 100) step = 100;}
}
