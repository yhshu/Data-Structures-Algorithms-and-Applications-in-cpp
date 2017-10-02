// bad way to time insertion sort

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
      // determine worst-case time to sort size n numbers
      long numberOfRepetitions = 0;
      clock_t elapsedTime = 0;
      do
      {
         numberOfRepetitions++;

         // initialize with worst-case data
         for (int i = 0; i < n; i++)
            a[i] = n - i;

         clock_t startTime = clock( );
         insertionSort(a, n);
         elapsedTime += clock( ) - startTime;
      } while (elapsedTime < 1000);
           // repeat until enough time has elapsed

      double elapsedMillis = elapsedTime / clocksPerMillis;
      cout << n << '\t' << numberOfRepetitions << '\t' << elapsedMillis
           << '\t' << elapsedMillis / numberOfRepetitions
           << endl;

      if (n == 100) step = 100;
   }
   return 0;
}
