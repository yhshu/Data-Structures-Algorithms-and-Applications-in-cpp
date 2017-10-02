// file select.h
// find the k'th smallest element

#ifndef Select_
#define Select_

#include "xcept.h"
#include "swap.h"

template<class T>
T select(T a[], int l, int r, int k)
{// Return k'th smallest in a[l:r].
   if (l >= r) return a[l];
   int i = l,      // left to right cursor
       j = r + 1;  // right to left cursor
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

   if (j - l + 1 == k) return pivot;

   // place pivot
   a[l] = a[j];
   a[j] = pivot;

   // recursive call on one segment
   if (j - l + 1 < k)
      return select(a, j+1, r, k-j+l-1);
   else return select(a, l, j-1, k);
}


template<class T>
T Select(T a[], int n, int k)
{// Return k'th smallest element in a[0:n-1].
 // Assume a[n] is a dummy largest element.
   if (k < 1 || k > n) throw OutOfBounds();
   return select(a, 0, n-1, k);
}

#endif
