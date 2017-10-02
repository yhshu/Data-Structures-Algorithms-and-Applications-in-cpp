// array implementation of a stack
// derives from the ADT stack

#ifndef arrayStack_
#define arrayStack_

#include "stack.h"
#include "myExceptions.h"
#include "changeLength1D.h"
#include <sstream>


template<class T>
class arrayStack : public stack<T>
{
   public:
      arrayStack(int initialCapacity = 10);
      ~arrayStack() {delete [] stack;}
      bool empty() const {return stackTop == -1;}
      int size() const
          {return stackTop + 1;}
      T& top()
         {
            if (stackTop == -1)
               throw stackEmpty();
            return stack[stackTop];
         }
      void pop()
           {
              if (stackTop == -1)
                 throw stackEmpty();
              stack[stackTop--].~T();  // destructor for T
           }
      void push(const T& theElement);
   private:
      int stackTop;         // current top of stack
      int arrayLength;      // stack capacity
      T *stack;           // element array
};

template<class T>
arrayStack<T>::arrayStack(int initialCapacity)
{// Constructor.
   if (initialCapacity < 1)
   {ostringstream s;
    s << "Initial capacity = " << initialCapacity << " Must be > 0";
    throw illegalParameterValue(s.str());
   }
   arrayLength = initialCapacity;
   stack = new T[arrayLength];
   stackTop = -1;
}

template<class T>
void arrayStack<T>::push(const T& theElement)
{// Add theElement to stack.
   if (stackTop == arrayLength - 1)
      {// no space, double capacity
         changeLength1D(stack, arrayLength, 2 * arrayLength);
         arrayLength *= 2;
      }

   // add at stack top
   stack[++stackTop] = theElement;
}
#endif
