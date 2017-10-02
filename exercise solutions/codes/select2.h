
// find the k'th smallest element
// no recursive calls

#ifndef Select_
#define Select_

#include "xcept.h"
#include "swap.h"

template<class T>
T Select(T a[], int n, int k)
{// Return k'th smallest element in a[0:n-1].
 // Assume a[n] is a dummy largest element.
   if (k < 1 || k > n) throw OutOfBounds();

   // define left and right ends of segment to be searched
   int l = 0;
   int r = n - 1;

   while (l < r) {
      // segment has > 1 element
      // partition the segment
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
   
      // only one segment is to be serached further
      if (j - l + 1 < k) {// look in right segment
         k -= j - l + 1;  // subtract size of left segment
                          // and pivot
         l = j + 1;
         }
      else // look in left segment
         r = j - 1;
      }

   return a[l];
}

#endif
