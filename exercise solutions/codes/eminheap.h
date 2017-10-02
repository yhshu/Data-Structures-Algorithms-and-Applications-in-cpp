
// file eminheap.h
// min heap extended to include a function to
// increase the key of the min elemnt

#ifndef ExtendedMinHeap_
#define ExtendedMinHeap_

#include "minheap2.h" 

template<class E, class K>
class ExtendedMinHeap : public MinHeap<E>
{
   public:
      ExtendedMinHeap(int ExtendedMinHeapSize = 10)
          : MinHeap<E> (ExtendedMinHeapSize) {}
      void IncreaseMinKey(K& x, E& e);
};

template<class E, class K>
void ExtendedMinHeap<E,K>::IncreaseMinKey(K& x, E& e)
{// Increase the key of the min element by x.
 // Put original min element in e.
   // make sure there is a min element
   if (CurrentSize == 0)
      throw OutOfBounds();

   // save min element in e and y
   E y = e = heap[1];

   y += x; // increase key of min element

   // put updated min element back into the heap
   int i = 1,
       ci = 2; // ci is child of i
   while (ci <= CurrentSize) {// find place to put y
      if (ci < CurrentSize && heap[ci] > heap[ci+1]) ci++;
      // now ci points to smaller child of i

      // can we put y in heap[i]?
      if (y <= heap[ci]) break;  // yes

      // no
      heap[i] = heap[ci]; // move child up
 
      // move i and ci one level down
      i = ci;
      ci *= 2;
      }

   heap[i] = y;
}

#endif
