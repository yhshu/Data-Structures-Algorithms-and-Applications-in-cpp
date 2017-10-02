
// heap implementation of a max priority queue
// derives from the ADT maxPriorityQueue

#ifndef maxHeap_
#define maxHeap_

#include "maxPriorityQueue.h"
#include "myExceptions.h"
#include "changeLength1D.h"
#include <sstream>
#include <algorithm>

using namespace std;

template<class T>
class maxHeap : public maxPriorityQueue<T>
{
   public:
      maxHeap(int initialCapacity = 10);
      ~maxHeap() {delete [] heap;}
      bool empty() const {return heapSize == 0;}
      int size() const
          {return heapSize;}
      const T& top()
         {// return max element
            if (heapSize == 0)
               throw queueEmpty();
            return heap[1];
         }
      void pop();
      void push(const T&);
      void initialize(T *, int);
      void deactivateArray()
         {heap = NULL; arrayLength = heapSize = 0;}
      void output(ostream& out) const;
   private:
      int heapSize;       // number of elements in queue
      int arrayLength;    // queue capacity + 1
      T *heap;            // element array
};

template<class T>
maxHeap<T>::maxHeap(int initialCapacity)
{// Constructor.
   if (initialCapacity < 1)
   {ostringstream s;
    s << "Initial capacity = " << initialCapacity << " Must be > 0";
    throw illegalParameterValue(s.str());
   }
   arrayLength = initialCapacity + 1;
   heap = new T[arrayLength];
   heapSize = 0;
}

template<class T>
void maxHeap<T>::push(const T& theElement)
{// Add theElement to heap.

   // increase array length if necessary
   if (heapSize == arrayLength - 1)
   {// double array length
      changeLength1D(heap, arrayLength, 2 * arrayLength);
      arrayLength *= 2;
   }

   // find place for theElement
   // currentNode starts at new leaf and moves up tree
   int currentNode = ++heapSize;
   while (currentNode != 1 && heap[currentNode / 2] < theElement)
   {
      // cannot put theElement in heap[currentNode]
      heap[currentNode] = heap[currentNode / 2]; // move element down
      currentNode /= 2;                          // move to parent
   }

   heap[currentNode] = theElement;
}

template<class T>
void maxHeap<T>::pop()
{// Remove max element.
   // if heap is empty return null
   if (heapSize == 0)   // heap empty
      throw queueEmpty();

   // Delete max element
   heap[1].~T();

   // Remove last element and reheapify
   T lastElement = heap[heapSize--];

   // find place for lastElement starting at root
   int currentNode = 1,
       child = 2;     // child of currentNode
   while (child <= heapSize)
   {
      // heap[child] should be larger child of currentNode
      if (child < heapSize && heap[child] < heap[child + 1])
         child++;

      // can we put lastElement in heap[currentNode]?
      if (lastElement >= heap[child])
         break;   // yes

      // no
      heap[currentNode] = heap[child]; // move child up
      currentNode = child;             // move down a level
      child *= 2;
   }
   heap[currentNode] = lastElement;
}

template<class T>
void maxHeap<T>::initialize(T *theHeap, int theSize)
{// Initialize max heap to element array theHeap[1:theSize].
   delete [] heap;
   heap = theHeap;
   heapSize = theSize;

   // heapify
   for (int root = heapSize / 2; root >= 1; root--)
   {
      T rootElement = heap[root];

      // find place to put rootElement
      int child = 2 * root; // parent of child is target
                            // location for rootElement
      while (child <= heapSize)
      {
         // heap[child] should be larger sibling
         if (child < heapSize && heap[child] < heap[child + 1])
            child++;

         // can we put rootElement in heap[child/2]?
         if (rootElement >= heap[child])
            break;  // yes

         // no
         heap[child / 2] = heap[child]; // move child up
         child *= 2;                    // move down a level
      }
      heap[child / 2] = rootElement;
   }
}

template<class T>
void maxHeap<T>::output(ostream& out) const
{// Put the list into the stream out.
   copy(heap + 1, heap + heapSize + 1, ostream_iterator<T>(cout, "  "));
}

// overload <<
template <class T>
ostream& operator<<(ostream& out, const maxHeap<T>& x)
   {x.output(out); return out;}

#endif
