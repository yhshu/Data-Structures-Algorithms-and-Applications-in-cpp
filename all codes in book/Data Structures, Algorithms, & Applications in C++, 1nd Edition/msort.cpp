// test merge sort

#include <iostream.h>
#include "msort.h" 

void main(void)
{
   int y[10] = {10,7,8,9,4, 2, 3, 6, 5,1};
   MergeSort(y,10);
   for (int i=0; i< 10; i++) cout << y[i] << ' ';
   cout << endl;
}
