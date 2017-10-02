// array stack derived from arrayList
// derives from abstract class stack just to make sure
// all methods of the ADT are implemented
// catches exception thrown by base-class method and throws
// own exception instead

#ifndef derivedArrayStackWithCatch_
#define derivedArrayStackWithCatch_

#include "arrayList.h"
#include "stack.h"
#include "myExceptions.h"

using namespace std;

template<class T>
class derivedArrayStackWithCatch : private arrayList<T>,
                                   public stack<T>
{
   public:
      derivedArrayStackWithCatch(int initialCapacity = 10)
        : arrayList<T> (initialCapacity) {}
      bool empty() const
           {return arrayList<T>::empty();}
      int size() const
          {return arrayList<T>::size();}
      T& top()
         {
            try {return get(arrayList<T>::size() - 1);}
            catch (illegalIndex)
               {throw stackEmpty();}
         }
      void pop()
           {
              try {erase(arrayList<T>::size() - 1);}
              catch (illegalIndex)
                 {throw stackEmpty();}
           }
      void push(const T& theElement)
           {insert(arrayList<T>::size(), theElement);}
};

#endif
