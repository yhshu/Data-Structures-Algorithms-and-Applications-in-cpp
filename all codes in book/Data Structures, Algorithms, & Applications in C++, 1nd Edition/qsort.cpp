
#include <iostream.h>
#include "qsort.h"

void main(void)
{
   int i, y[16] = {15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 30};
   //int i, y[16] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,30};
   int n = 15;
   QuickSort(y,n);
   for (i = 0; i < n; i++)
      cout << y[i] << ' ';
   cout << endl;
}
