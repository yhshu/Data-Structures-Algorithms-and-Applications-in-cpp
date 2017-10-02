// determine the overhead time

#include <iostream>
#include <time.h>
#include "insertionSort.h"

using namespace std;

int main()
{
   int a[1000], step = 10;
   double clocksPerMillis = double(CLOCKS_PER_SEC) / 1000;
                      // clock ticks per millisecond

   cout << "The worst-case time, in milliseconds, are" << endl;
   cout << "n \tRepetitions \t Total Ticks \tTime per Sort" << endl;

   // times for n = 0, 10, 20, ..., 100, 200, 300, ..., 1000
   for (int n = 0; n <= 1000; n += step)
   {
      // get time for size n
      long numberOfRepetitions = 0;
      clock_t startTime = clock( );
      do 
      {
         numberOfRepetitions++;

         // initialize with worst-case data
         for (int i = 0; i < n; i++)
            a[i] = n - i;

         // insertionSort(a, n);
      } while (clock( ) - startTime < 1000);
           // repeat until enough time has elapsed

      double elapsedMillis = (clock( ) - startTime) / clocksPerMillis;
      cout << n << '\t' << numberOfRepetitions << '\t' << elapsedMillis
           << '\t' << elapsedMillis / numberOfRepetitions
           << endl;

      if (n == 100) step = 100;
   }
   return 0;
}
