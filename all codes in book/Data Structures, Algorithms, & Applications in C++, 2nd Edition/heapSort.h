// heap sort a[1:n]
#ifndef heapSort_
#define heapSort_

#include "maxHeap.h"

using namespace std;

template <class T>
void heapSort(T a[], int n)
{// Sort a[1:n] using the heap sort method.
   // create a max heap of the elements
   maxHeap<T> heap(1);
   heap.initialize(a, n);

   // extract one by one from the max heap
   for (int i = n - 1; i >= 1; i--)
   {
      T x = heap.top();
      heap.pop();
      a[i+1] = x;
   }

   // save array a from heap destructor
   heap.deactivateArray();
}

#endif
