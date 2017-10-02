
// heap sort using double the space
#ifndef HeapSort_
#define HeapSort_

#include "maxheap6.h"

template <class T>
void HeapSort(T a[], int n)
{// Sort a using the heap sort method.
 // Elements are in a[1:n] and array has
 // positions a[0:2n + 1].
   if (n < 2) return;
   // first find min and max elements
   T Min = a[1];
   for (int i = 2; i <= n; i++)
      if (Min > a[i]) Min = a[i];

   T Max = a[1];
   for (i = 2; i <= n; i++)
      if (Max < a[i]) Max = a[i];

   // create a max heap of the elements
   MaxHeap<T> H(1,0,1);
   H.Initialize(a,n,2*n+1,Min,Max);

   // extract one by one from the max heap
   T x;
   for (i = n-1; i >= 1; i--) {
      H.DeleteMax(x);
      a[i+1] = x;
      }

   // save array a from heap destructor
   H.Deactivate();
}

#endif
