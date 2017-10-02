// bad way to time insertion sort

#include <iostream.h>
#include <time.h>
#include <math.h>
#include "insort.h"

void main(void)
{
 int a[1000], step = 10;
 clock_t start, finish;
 for (int n = 0; n <= 1000; n += step)
 {// get time for size n
   for (int i = 0; i < n; i++)
         a[i] = n - i; // initialize
   start = clock( );
   InsertionSort(a, n);
   finish = clock( );
   cout << n << ' ' << (finish - start) / CLK_TCK << endl;
   if (n == 100) step = 100;}
}
