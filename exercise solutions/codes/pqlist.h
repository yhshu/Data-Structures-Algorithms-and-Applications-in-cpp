
// max priority queue derived from
// LinearList
#ifndef MaxPQ_
#define MaxPQ_

#include <stdlib.h>
#include <iostream.h>
#include "xcept.h"
#include "llist.h"

template<class T>
class MaxPQ : private LinearList<T> {
   public:
      MaxPQ(int MaxPQSize = 10) :
         LinearList<T> (MaxPQSize) {}
      int Size() {return Length();}
      T Max();
      MaxPQ<T>& Insert(const T& x)
         {LinearList<T>::Insert(Length(), x);
          return *this;}
      MaxPQ<T>& DeleteMax(T& x);
      void Output(ostream& out) const
         {LinearList<T>::Output(out);}
};

template<class T>
T MaxPQ<T>::Max()
{// Return max element.
   int len = Length();             // size of queue
   if (!len) throw OutOfBounds();  // queue is empty

   // find max element by examining all
   // elements in queue
   T CurrentMax, x;
   Find(1, CurrentMax);
   for (int i = 2; i <= len; i++) {
      Find(i, x);
      if (x > CurrentMax) CurrentMax = x;
      }

   return CurrentMax;
}
      
template<class T>
MaxPQ<T>& MaxPQ<T>::DeleteMax(T& x)
{// Set x to max element and delete
 // max element from priority queue.
   // check if queue is empty
   int len = Length();
   if (len == 0)
      throw OutOfBounds(); // empty

   // find max element and its index
   // we could replace next two lines by code
   // to find IndexOfMax by making a single
   // pass over the queue elements
   x = Max();
   int IndexOfMax = Search(x);

   // delete max element
   Delete(IndexOfMax, x);

   return *this;
}

// overload <<
template <class T>
ostream& operator<<(ostream& out, const MaxPQ<T>& x)
   {x.Output(out); return out;}

#endif
