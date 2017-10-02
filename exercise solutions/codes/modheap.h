
// modified min heap
// has an additional external array VN1 that keeps track
// of location of each element in the heap
// this location is used to locate elements whose key is to
// be reduced
// elements have IDs 1 through MinHeapSize

#ifndef ModifiedMinHeap_
#define ModifiedMinHeap_

#include <stdlib.h>
#include <iostream.h>
#include "xcept.h"
#include "vnode.h"

template <class T>
class ModifiedMinHeap {
   public:
      ModifiedMinHeap(int MinHeapSize = 10);
      ~ModifiedMinHeap() {delete [] heap;}
      int Size() const {return CurrentSize;}
      T Min() {if (CurrentSize == 0)
                  throw OutOfBounds();
               return heap[1];}
      ModifiedMinHeap<T>& Insert(const VertexNode2<T>& x);
      ModifiedMinHeap<T>& DeleteMin(VertexNode2<T>& x);
      ModifiedMinHeap<T>& Decrease(const VertexNode2<T>& x);
   private:
      int CurrentSize, MaxSize;
      VertexNode2<T> *heap; // element array
      int *location;        // location array
};

template<class T>
ModifiedMinHeap<T>::
        ModifiedMinHeap(int MinHeapSize)
{// Min heap constructor.
   MaxSize = MinHeapSize;
   heap = new VertexNode2<T> [MaxSize+1];
   location = new int [MaxSize+1];
   // initially, no element has a location
   for (int i = 1; i <= MinHeapSize; i++)
      location[i] = 0;
   CurrentSize = 0;
}

template<class T>
ModifiedMinHeap<T>& ModifiedMinHeap<T>::Insert
                    (const VertexNode2<T>& x)
{// Insert x into the min heap.
   if (CurrentSize == MaxSize)
      throw NoMem(); // no space
   if (x.ID < 1 || x.ID > MaxSize)
      throw BadInput();

   // find place for x
   // i starts at new leaf and moves up tree
   int i = ++CurrentSize;
   while (i != 1 && x < heap[i/2]) {
      // cannot put x in heap[i]
      heap[i] = heap[i/2]; // move element down
      location[heap[i].ID] = i;
      i /= 2; // move to parent
      }
   heap[i] = x;
   location[x.ID] = i;

   return *this;
}

template<class T>
ModifiedMinHeap<T>& ModifiedMinHeap<T>::DeleteMin
                    (VertexNode2<T>& x)
{// Set x to min element and delete
 // min element from heap.
   // check if heap is empty
   if (CurrentSize == 0)
      throw OutOfBounds(); // empty

   x = heap[1]; // min element
   location[x.ID] = 0;

   // restructure heap
   VertexNode2<T> y = heap[CurrentSize--]; // last element

   // find place for y starting at root
   int i = 1,  // current node of heap
       ci = 2; // child of i
   while (ci <= CurrentSize) {// find place to put y
      // heap[ci] should be larger child of i
      if (ci < CurrentSize &&
          heap[ci] > heap[ci+1]) ci++;

      // can we put y in heap[i]?
      if (y <= heap[ci]) break;  // yes

      // no
      heap[i] = heap[ci]; // move child up
      location[heap[i].ID] = i;
      i = ci;  // move down a level
      ci *= 2;
      }
   heap[i] = y;
   location[y.ID] = i;

   return *this;
}

template<class T>
ModifiedMinHeap<T>& ModifiedMinHeap<T>::Decrease
                    (const VertexNode2<T>& x)
{// Decrease distance of x.ID to x.distance.
   // check if x.ID in heap
   if (!location[x.ID])
      throw BadInput();

   // make sure new distance is smaller
   if (x.distance >= heap[location[x.ID]].distance)
      throw BadInput();

   // find new place for x
   // i starts at old location of x and moves up tree
   int i = location[x.ID];
   while (i != 1 && x < heap[i/2]) {
      // cannot put x in heap[i]
      heap[i] = heap[i/2]; // move element down
      location[heap[i].ID] = i;
      i /= 2; // move to parent
      }
   heap[i] = x;
   location[x.ID] = i;

   return *this;
}


#endif
