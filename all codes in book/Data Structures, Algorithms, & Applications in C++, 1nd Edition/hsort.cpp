// heap sort

#include <iostream.h>
#include "hsort.h"

void main(void)
{
   int a[11], i, n = 10;
   // initialize descending data
   for (i = 1; i <= 10; i++)
      a[i] = n - i + 1;

   HeapSort(a,10);

   // output sorted data
   for (i = 1; i <= n; i++) 
      cout << a[i] << ' ';
   cout << endl;
}
