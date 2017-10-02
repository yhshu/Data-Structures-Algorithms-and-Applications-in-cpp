// max priority queue derived from
// SortedList
#ifndef MaxPQ_
#define MaxPQ_

#include<stdlib.h>
#include <iostream.h>
#include "xcept.h"
#include "solist2.h"

template<class E, class K>
class MaxPQ : private SortedList<E,K> {
   public:
      MaxPQ(int MaxPQSize = 10) :
         SortedList<E,K> (MaxPQSize) {}
      int Size() {return Length();}
      E Max();
      MaxPQ<E,K>& Insert(const E& x)
         {SortedList<E,K>::Insert(x);
          return *this;}
      MaxPQ<E,K>& DeleteMax(E& x);
      void Output(ostream& out) const
         {SortedList<E,K>::Output(out);}
};

template<class E, class K>
E MaxPQ<E,K>::Max()
{// Return max element.
   int len = Length();             // size of queue
   if (!len) throw OutOfBounds();  // queue is empty

   // max element is last one
   E x;
   Find(len,x);
   return x;
}
      
template<class E, class K>
MaxPQ<E,K>& MaxPQ<E,K>::DeleteMax(E& x)
{// Set x to max element and delete
 // max element from priority queue.
   // check if queue is empty
   int len = Length();
   if (len == 0)
      throw OutOfBounds(); // empty

   // max element is last one
   Delete(len, x);

   return *this;
}

// overload <<
template <class E, class K>
ostream& operator<<(ostream& out, const MaxPQ<E,K>& x)
   {x.Output(out); return out;}

#endif
