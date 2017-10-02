// file lstack.h
// linked stack
#ifndef LinkedStack_
#define LinkedStack_

#include "node.h"
#include "xcept.h"

template<class T>
class LinkedStack {
   public:
      LinkedStack() {top = 0;}
      ~LinkedStack();
      bool IsEmpty() const {return top == 0;}
      bool IsFull() const;
      T Top() const;
      LinkedStack<T>& Add(const T& x);
      LinkedStack<T>& Delete(T& x);
   private:
      Node<T> *top; // pointer to top node
};

template<class T>
LinkedStack<T>::~LinkedStack()
{// Stack destructor..
   Node<T> *next;
   while (top) {
      next = top->link;
      delete top;
      top = next;
      }
}

template<class T>
bool LinkedStack<T>::IsFull() const
{// Is the stack full?
   try {Node<T> *p = new Node<T>;
        delete p;
        return false;}
   catch (NoMem) {return true;}
}

template<class T>
T LinkedStack<T>::Top() const
{// Return top element.
   if (IsEmpty()) throw OutOfBounds();
   return top->data;
}

template<class T>
LinkedStack<T>& LinkedStack<T>::Add(const T& x)
{// Add x to stack.
   Node<T> *p = new Node<T>;
   p->data = x;
   p->link = top;
   top = p;
   return *this;
}

template<class T>
LinkedStack<T>& LinkedStack<T>::Delete(T& x)
{// Delete top element and put it in x.
   if (IsEmpty()) throw OutOfBounds();
   x = top->data;
   Node<T> *p = top;
   top = top->link;
   delete p;
   return *this;
}

#endif;
