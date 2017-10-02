

// max heap with ChangeMax,
// IsFull, and IsEmpty
#ifndef MaxHeap_
#define MaxHeap_

#include<stdlib.h>
#include <iostream.h>
#include "xcept.h"

template<class T>
class MaxHeap {
   public:
      MaxHeap(int MaxHeapSize = 10);
      ~MaxHeap() {delete [] heap;}
      int Size() const {return CurrentSize;}
      bool IsEmpty() {return CurrentSize == 0;}
      bool IsFull() {return CurrentSize == MaxSize;}
      T Max() {if (CurrentSize == 0)
                  throw OutOfBounds();
               return heap[1];}
      MaxHeap<T>& Insert(const T& x);
      MaxHeap<T>& DeleteMax(T& x);
      MaxHeap<T>& ChangeMax(const T& x);
      void Initialize(T a[], int size, int ArraySize);
      void Deactivate() {heap = 0;}
      void Output() const;
   private:
      int CurrentSize, MaxSize;
      T *heap;  // element array
};

template<class T>
MaxHeap<T>::MaxHeap(int MaxHeapSize)
{// Max heap constructor.
   MaxSize = MaxHeapSize;
   heap = new T[MaxSize+1];
   CurrentSize = 0;
}

template<class T>
MaxHeap<T>& MaxHeap<T>::Insert(const T& x)
{// Insert x into the max heap.
   if (CurrentSize == MaxSize)
      throw NoMem(); // no space

   // find place for x
   // i starts at new leaf and moves up tree
   int i = ++CurrentSize;
   while (i != 1 && x > heap[i/2]) {
      // cannot put x in heap[i]
      heap[i] = heap[i/2]; // move element down
      i /= 2;              // move to parent
      }

   heap[i] = x;
   return *this;
}

template<class T>
MaxHeap<T>& MaxHeap<T>::DeleteMax(T& x)
{// Set x to max element and delete
 // max element from heap.
   // check if heap is empty
   if (CurrentSize == 0)
      throw OutOfBounds(); // empty

   x = heap[1]; // max element

   // restructure heap
   T y = heap[CurrentSize--]; // last element

   // find place for y starting at root
   int i = 1,  // current node of heap
       ci = 2; // child of i
   while (ci <= CurrentSize) {
      // heap[ci] should be larger child of i
      if (ci < CurrentSize &&
          heap[ci] < heap[ci+1]) ci++;

      // can we put y in heap[i]?
      if (y >= heap[ci]) break;   // yes

      // no
      heap[i] = heap[ci]; // move child up
      i = ci;             // move down a level
      ci *= 2;
      }
   heap[i] = y;

   return *this;
}

template<class T>
MaxHeap<T>& MaxHeap<T>::ChangeMax(const T& x)
{// Change the max element to x.
   // check if heap is empty
   if (CurrentSize == 0)
      throw OutOfBounds(); // empty

   // restucture heap
   T y = x;

   // find place for y starting at root
   int i = 1,  // current node of heap
       ci = 2; // child of i
   while (ci <= CurrentSize) {
      // heap[ci] should be larger child of i
      if (ci < CurrentSize &&
          heap[ci] < heap[ci+1]) ci++;

      // can we put y in heap[i]?
      if (y >= heap[ci]) break;   // yes

      // no
      heap[i] = heap[ci]; // move child up
      i = ci;             // move down a level
      ci *= 2;
      }
   heap[i] = y;

   return *this;
}

template<class T>
void MaxHeap<T>::Initialize(T a[], int size,
                               int ArraySize)
{// Initialize max heap to array a.
   delete [] heap;
   heap = a;
   CurrentSize = size;
   MaxSize = ArraySize;

   // make into a max heap
   for (int i = CurrentSize/2; i >= 1; i--) {
      T y = heap[i]; // root of subtree

      // find place to put y
      int c = 2*i; // parent of c is target
                   // location for y
      while (c <= CurrentSize) {
         // heap[c] should be larger sibling
         if (c < CurrentSize &&
             heap[c] < heap[c+1]) c++;

         // can we put y in heap[c/2]?
         if (y >= heap[c]) break;  // yes

         // no
         heap[c/2] = heap[c]; // move child up
         c *= 2; // move down a level
         }
      heap[c/2] = y;
      }
}

template<class T>
void MaxHeap<T>::Output() const
{
   cout << "The " << CurrentSize 
        << " elements are"<< endl;
   for (int i = 1; i <= CurrentSize; i++)
       cout << heap[i] << ' ';
   cout << endl;
}

#endif
