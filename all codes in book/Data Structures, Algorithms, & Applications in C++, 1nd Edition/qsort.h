// file qsort.h
// quick sort

#ifndef QuickSort_
#define QuickSort_

#include "swap.h"

template<class T>
void quickSort(T a[], int l, int r)
{// Sort a[l:r], a[r+1] has large value.
   if (l >= r) return;
   int i = l,      // left-to-right cursor
       j = r + 1;  // right-to-left cursor
   T pivot = a[l];

   // swap elements >= pivot on left side
   // with elements <= pivot on right side
   while (true) {
      do {// find >= element on left side
         i = i + 1;
         } while (a[i] < pivot);
      do {// find <= element on right side
         j = j - 1;
         } while (a[j] > pivot);
      if (i >= j) break;  // swap pair not found
      Swap(a[i], a[j]);
      }

   // place pivot
   a[l] = a[j];
   a[j] = pivot;

   quickSort(a, l, j-1); // sort left segment
   quickSort(a, j+1, r); // sort right segment
}


template<class T>
void QuickSort(T *a, int n)
{// Sort a[0:n-1] using quick sort.
 // Requires a[n] must have largest key.
   quickSort(a, 0, n-1);
}

#endif
