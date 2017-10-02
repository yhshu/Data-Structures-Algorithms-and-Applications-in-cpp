
// find an element by rank

#ifndef select_
#define select_

#include "indexOfMax.h"
#include "myExceptions.h"

using namespace std;

template <class T>
T select(T a[], int n, int k)
{// Return k'th smallest element in a[0 : n - 1].
   if (k < 1 || k > n)
      throw illegalParameterValue("k must be between 1 and n");

   // move largest element to right end
   int max = indexOfMax(a, n);
   swap(a[n-1], a[max]);
   return select(a, 0, n - 1, k);
}

template <class T>
T select(T a[], int leftEnd, int rightEnd, int k)
{// Return k'th element in a[leftEnd:rightEnd].
   if (leftEnd >= rightEnd)
      return a[leftEnd];
   int leftCursor = leftEnd,        // left-to-right cursor
       rightCursor = rightEnd + 1;  // right-to-left cursor
   T pivot = a[leftEnd];

   // swap elements >= pivot on left side
   // with elements <= pivot on right side
   while (true)
   {
      do
      {// find >= element on left side
         leftCursor++;
      } while (a[leftCursor] < pivot);

      do
      {// find <= element on right side
         rightCursor--;
      } while (a[rightCursor] > pivot);

      if (leftCursor >= rightCursor) break;  // swap pair not found
      swap(a[leftCursor], a[rightCursor]);
   }

   if (rightCursor - leftEnd + 1 == k)
      return pivot;

   // place pivot
   a[leftEnd] = a[rightCursor];
   a[rightCursor] = pivot;

   // recursive call on one segment
   if (rightCursor - leftEnd + 1 < k)
      return select(a, rightCursor + 1, rightEnd,
                    k - rightCursor + leftEnd - 1);
   else return select(a, leftEnd, rightCursor - 1, k);
}
#endif
