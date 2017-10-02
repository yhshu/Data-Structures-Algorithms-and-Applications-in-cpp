// average sort times 

#include <iostream>
#include <time.h>
#include <math.h>
#include "insertionSort.h"
#include "heapSort.h"
#include "mergeSort.h"
#include "quickSort.h"

using namespace std;

void main(void)
{
   double clocksPerMillis = double(CLOCKS_PER_SEC) / 1000;
                      // clock ticks per millisecond
   double clocksPerSec = double(CLOCKS_PER_SEC);
   int theN [] = {0, 50, 100, 200, 300, 400, 500, 1000, 2000, 3000, 4000, 5000};
   int numPoints = 12;
   int step = 10;

   cout << "The average-case times, in milliseconds, are" << endl;
   cout << "n \trepetitions \ttime/sort" << endl;
   for (int i = 0; i < numPoints; i++)
   {
      int n = theN[i];
      // create element arrays
      int *a = new int [n + 1];

      long startTime = clock();
      long counter = 0;
      while (counter < 200 ||
             clock( ) - startTime < clocksPerSec)
      {
         counter++;
         // create random data
         // for (int i = 0; i < n; i++)
         for (int i = 1; i <= n; i++)
            a[i] = rand();

         // sort the elements
         // mergeSort(a, n);
         // quickSort(a,n);
         // insertionSort(a,n);
          heapSort(a,n);
      }

      double elapsedTime = ((double) (clock() - startTime)) / counter;
      elapsedTime /= clocksPerMillis;
      cout << n << "\t" << counter << "\t\t" 
           << elapsedTime << endl;
   }
}
