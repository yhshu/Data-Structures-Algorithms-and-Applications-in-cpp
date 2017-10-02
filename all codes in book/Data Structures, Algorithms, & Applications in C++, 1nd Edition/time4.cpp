// bad way to time insertion sort

#include <iostream.h>
#include <time.h>
#include "insort.h"

void main(void)
{
   int a[1000], n, i, step = 10;
   long counter;
   float seconds;
   clock_t start, elapsed;
   for (n = 0; n <= 1000; n += step) {
      // get time for size n
      elapsed = 0; counter = 0;
      while (elapsed < 10) {
         counter++;
         for (i = 0; i < n; i++)
            a[i] = n - i; // initialize
         start = clock( );
         InsertionSort(a, n);
         elapsed += clock( ) - start;
         }
      seconds = elapsed / float(CLK_TCK);
      cout << n << ' ' << counter << ' ' << seconds
           << ' ' << seconds / counter << endl;
      if (n == 100) step = 100;
      }
}
