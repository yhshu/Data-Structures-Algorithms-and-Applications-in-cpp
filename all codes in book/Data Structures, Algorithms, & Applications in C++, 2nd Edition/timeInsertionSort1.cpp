// simple way to measure worst-case insertion sort times
// bad when times to be measured are small

#include <iostream>
#include <time.h>   // has clock stuff
#include "insertionSort.h"

using namespace std;

int main()
{
   int a[1000], step = 10;
   double clocksPerMillis = double(CLOCKS_PER_SEC) / 1000;
                      // clock ticks per millisecond

   cout << "The worst-case time, in milliseconds, are" << endl;
   cout << "n \t Time" << endl;

   // times for n = 0, 10, 20, ..., 100, 200, 300, ..., 1000
   for (int n = 0; n <= 1000; n += step) 
   {
      // initialize with worst-case data
      for (int i = 0; i < n; i++)
         a[i] = n - i;

      clock_t startTime = clock( );
      insertionSort(a, n);
      double elapsedMillis = (clock( ) - startTime) / clocksPerMillis;

      cout << n << '\t' << elapsedMillis << endl;

      if (n == 100) step = 100;
   }
   return 0;
}
