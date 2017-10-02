// file hsort.h 
//heap sort
#ifndef HeapSort_
#define HeapSort_

#include "maxheap.h"

template <class type>
void HeapSort(type a[], int n)
{// sort a using the heap sort method
MaxHeap<type> H(1);
type x;
H.Initialize(a,n,n);
for (int i = n-1; i >= 1; i--) {
   H.DeleteMax(x);
   a[i+1] = x;}
H.Deactivate();
}

#endif
