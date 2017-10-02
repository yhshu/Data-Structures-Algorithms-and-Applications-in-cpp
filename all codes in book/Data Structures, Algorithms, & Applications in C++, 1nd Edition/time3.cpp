
// overhead time for insertion sort timing

#include <iostream.h>
#include <time.h>
#include "insort.h"

void main(void)
{
   int a[1000], n, i, step = 10;
   long counter;
   float seconds;
   clock_t start, finish;
   for (n = 0; n <= 1000; n += step) {
      // get time for size n
      start = clock( ); counter = 0;
      while (clock( ) - start < 10) {
         counter++;
         for (i = 0; i < n; i++)
            a[i] = n - i; // initialize
         // InsertionSort(a, n);
         }
      finish = clock( );
      seconds = (finish - start) / float(CLK_TCK);
      cout << n << ' ' << counter << ' ' << seconds << ' '
           << seconds / counter << endl;
      if (n == 100) step = 100;}
}
