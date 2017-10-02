// array stack derived from arrayList
// derives from abstract class stack just to make sure
// all methods of the ADT are implemented

#ifndef derivedArrayStack_
#define derivedArrayStack_

#include "arrayList.h"
#include "stack.h"
#include "myExceptions.h"

using namespace std;

template<class T>
class derivedArrayStack : private arrayList<T>,
                          public stack<T>
{
   public:
      derivedArrayStack(int initialCapacity = 10)
        : arrayList<T> (initialCapacity) {}
      bool empty() const
           {return arrayList<T>::empty();}
      int size() const
          {return arrayList<T>::size();}
      T& top()
         {
            if (arrayList<T>::empty())
               throw stackEmpty();
            return get(arrayList<T>::size() - 1);
         }
      void pop()
           {
              if (arrayList<T>::empty())
                 throw stackEmpty();
              erase(arrayList<T>::size() - 1);
           }
      void push(const T& theElement)
           {insert(arrayList<T>::size(), theElement);}
};

#endif
