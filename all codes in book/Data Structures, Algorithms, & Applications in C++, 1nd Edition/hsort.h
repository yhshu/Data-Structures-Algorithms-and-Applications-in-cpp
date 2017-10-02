// file hsort.h 
//heap sort
#ifndef HeapSort_
#define HeapSort_

#include "maxheap.h"

template <class T>
void HeapSort(T a[], int n)
{// Sort a[1:n] using the heap sort method.
   // create a max heap of the elements
   MaxHeap<T> H(1);
   H.Initialize(a,n,n);

   // extract one by one from the max heap
   T x;
   for (int i = n-1; i >= 1; i--) {
      H.DeleteMax(x);
      a[i+1] = x;
      }

   // save array a from heap destructor
   H.Deactivate();
}

#endif
