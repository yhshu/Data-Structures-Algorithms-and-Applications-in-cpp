
// min priority queue derived from
// LinearList
#ifndef MinPQ_
#define MinPQ_

#include <stdlib.h>
#include <iostream.h>
#include "xcept.h"
#include "llist.h"

template<class T>
class MinPQ : private LinearList<T> {
   public:
      MinPQ(int MinPQSize = 10) :
         LinearList<T> (MinPQSize) {}
      int Size() {return Length();}
      T Min();
      MinPQ<T>& Insert(const T& x)
         {LinearList<T>::Insert(Length(), x);
          return *this;}
      MinPQ<T>& DeleteMin(T& x);
      void Output(ostream& out) const
         {LinearList<T>::Output(out);}
};

template<class T>
T MinPQ<T>::Min()
{// Return min element.
   int len = Length();             // size of queue
   if (!len) throw OutOfBounds();  // queue is empty

   // find min element by examining all
   // elements in queue
   T CurrentMin, x;
   Find(1, CurrentMin);
   for (int i = 2; i <= len; i++) {
      Find(i,x);
      if (x < CurrentMin) CurrentMin = x;
      }

   return CurrentMin;
}
      
template<class T>
MinPQ<T>& MinPQ<T>::DeleteMin(T& x)
{// Set x to min element and delete
 // min element from priority queue.
   // check if queue is empty
   int len = Length();
   if (len == 0)
      throw OutOfBounds(); // empty

   // find min element and its index
   // we could replace next two lines by code
   // to find IndexOfMin by making a single
   // pass over the queue elements
   x = Min();
   int IndexOfMin = Search(x);

   // delete min element
   Delete(IndexOfMin, x);

   return *this;
}

// overload <<
template <class T>
ostream& operator<<(ostream& out, const MinPQ<T>& x)
   {x.Output(out); return out;}

#endif
