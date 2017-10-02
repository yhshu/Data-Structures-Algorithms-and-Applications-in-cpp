
// max heap with double the space

#ifndef MaxHeap_
#define MaxHeap_

#include <stdlib.h>
#include <iostream.h>
#include "xcept.h"

template<class T>
class MaxHeap {
   public:
      MaxHeap(int MaxHeapSize, T maxElement,
              T minElement);
      ~MaxHeap() {delete [] heap;}
      int Size() const {return CurrentSize;}
      T Max() {if (CurrentSize == 0)
                  throw OutOfBounds();
               return heap[1];}
      MaxHeap<T>& Insert(const T& x);
      MaxHeap<T>& DeleteMax(T& x);
      void Initialize(T a[], int size, int ArraySize,
           int minElement, int maxElement);
      void Deactivate() {heap = 0;}
      void Output() const;
   private:
      int CurrentSize,
          MaxSize;
      T MaxElement,  // all must be <= MaxElement
        MinElement;  // all must be >= MinElement
      T *heap;  // element array
};

template<class T>
MaxHeap<T>::MaxHeap(int MaxHeapSize,
            T maxElement, T minElement)
{// Max heap constructor.
   MaxSize = MaxHeapSize;
   MaxElement = maxElement;
   MinElement = minElement;
   heap = new T[2*(MaxSize+1)];

   // put MaxElement in heap[0]
   heap[0] = MaxElement;

   // put MinElement in all other positions
   for (int i = 1; i <= 2*MaxSize + 1; i++)
      heap[i] = MinElement;

   CurrentSize = 0;
}

template<class T>
MaxHeap<T>& MaxHeap<T>::Insert(const T& x)
{// Insert x into the max heap.
   if (CurrentSize == MaxSize)
      throw NoMem(); // no space
   if (x < MinElement || x > MaxElement)
      throw BadInput();

   // find place for x
   // i starts at new leaf and moves up tree
   int i = ++CurrentSize;
  
   // no need to check if root reached
   // because heap[0] = MaxElement
   while (x > heap[i/2]) {
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
   T y = heap[CurrentSize]; // last element
   // replace with MinElement
   heap[CurrentSize--] = MinElement;

   // first propagate vacancy to a leaf
   int i = 1,  // current node of heap
       ci = 2; // child of i
   while (ci <= CurrentSize) {
      // heap[ci] should be larger child of i
      // no need to check if ci < CurrentSize
      // because heap[CurrentSize] has MinElement
      if (heap[ci] < heap[ci+1]) ci++;

      // move larger child to heap[i]
      heap[i] = heap[ci]; // move child up
      i = ci;             // move down a level
      ci *= 2;
      }

   i = ci/2;
   // vacancy at heap[i], start from here
   // and insert y
   // no need to check if root reached
   // because heap[0] = MaxElement
   while (y > heap[i/2]) {
      // cannot put y in heap[i]
      heap[i] = heap[i/2]; // move element down
      i /= 2;              // move to parent
      }

   heap[i] = y;

   return *this;
}

template<class T>
void MaxHeap<T>::Initialize(T a[], int size,
                 int ArraySize, int minElement, int maxElement)
{// Initialize max heap to array a[0:ArraySize].
   if (ArraySize < 2*size + 1)
      throw BadInput();  // not enough space for
                         // MinElement children of
                         // leaves
   // set private data members of MaxHeap
   delete [] heap;
   heap = a;
   CurrentSize = size;
   MaxElement = maxElement;
   MinElement = minElement;
   heap[0] = MaxElement;
   // fill rest of array with MinElement
   for (int i = size + 1; i <= ArraySize; i++)
      heap[i] = MinElement;
   MaxSize = (ArraySize - 1)/2;

   // make into a max heap
   // by running old method as we do not
   // expect to propagate all the way down
   for (i = CurrentSize/2; i >= 1; i--) {
      T y = heap[i]; // root of subtree

      // find place to put y
      int c = 2*i; // parent of c is target
                   // location for y
      while (c <= CurrentSize) {
         // heap[c] should be larger sibling
         // no need to check if c < CurrentSize as
         // all unused spots have MinElement
         if (heap[c] < heap[c+1]) c++;

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
