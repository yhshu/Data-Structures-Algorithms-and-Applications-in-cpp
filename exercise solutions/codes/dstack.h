// file dstack.h

#ifndef Stack_
#define Stack_

#include "llista.h"
#include "xcept.h"


template<class T>
class Stack : private LinearList <T> {
// LIFO objects
   public:
      Stack(int MaxStackSize = 10)
        : LinearList<T> (MaxStackSize) {}
      bool IsEmpty() const
           {return LinearList<T>::IsEmpty();}
      bool IsFull() const
         {return (Length() == GetMaxSize());}
      T Top() const
         {if (IsEmpty()) throw OutOfBounds();
          T x; Find(Length(), x); return x;}
      Stack<T>& Add(const T& x)
         {Insert(Length(), x); return *this;}
      Stack<T>& Delete(T& x)
         {LinearList<T>::Delete(Length(), x);
          return *this;}
};

#endif
