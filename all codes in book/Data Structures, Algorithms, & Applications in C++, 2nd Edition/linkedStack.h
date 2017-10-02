// linked implementation of a stack
// derives from the ADT stack

#ifndef linkedStack_
#define linkedStack_

#include "stack.h"
#include "chainNode.h"
#include "myExceptions.h"
#include <sstream>

using namespace std;

template<class T>
class linkedStack : public stack<T>
{
   public:
      linkedStack(int initialCapacity = 10)
            {stackTop = NULL; stackSize = 0;}
      ~linkedStack();
      bool empty() const
           {return stackSize == 0;}
      int size() const
          {return stackSize;}
      T& top()
         {
            if (stackSize == 0)
               throw stackEmpty();
            return stackTop->element;
         }
      void pop();
      void push(const T& theElement)
           {
              stackTop = new chainNode<T>(theElement, stackTop);
              stackSize++;
           }
   private:
      chainNode<T>* stackTop;  // pointer to stack top
      int stackSize;           // number of elements in stack
};

template<class T>
linkedStack<T>::~linkedStack()
{// Destructor.
   while (stackTop != NULL)
   {// delete top node
      chainNode<T>* nextNode = stackTop->next;
      delete stackTop;
      stackTop = nextNode;
   }
}

template<class T>
void linkedStack<T>::pop()
{// Delete top element.
   if (stackSize == 0)
      throw stackEmpty();

   chainNode<T>* nextNode = stackTop->next;
   delete stackTop;
   stackTop = nextNode;
   stackSize--;
}
#endif
