// selection sort

#include <iostream.h>
#include "swap.h"
#include "max.h" // max of n elements

template<class T>
void SelectionSort(T a[], int n)
{// Sort the n elements a[0:n-1].
   for (int size = n; size > 1; size--) {
      int j = Max(a, size);
      Swap(a[j], a[size - 1]);
      }
}

void main(void)
{
   int y[10] = {3, 2, 4, 1, 6, 9, 8, 7, 5, 0};
   SelectionSort(y,10);
   for (int i=0; i<10; i++)
      cout << y[i] << ' ';
   cout << endl;
}
