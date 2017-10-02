// early terminating selection sort

#include <iostream.h>
#include "swap.h"

template<class T>
void SelectionSort(T a[], int n)
{// Early-terminating version of selection sort.
   bool sorted = false;
   for (int size = n; !sorted && (size > 1); size--) {
      int pos = 0;
      sorted = true;
      // find largest
      for (int i = 1; i < size; i++)
         if (a[pos] <= a[i]) pos = i;
         else sorted = false; // out of order
      Swap(a[pos], a[size - 1]);
      }
}

void main(void)
{
   int y[10] = {3, 2, 4, 1, 6, 9, 8, 7, 5, 0};
   SelectionSort(y,10);
   for (int i = 0; i < 10; i++)
      cout << y[i] << ' ';
}
