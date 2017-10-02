
// linked queue
// derives from AbstractQueue

#ifndef LinkedQueue_
#define LinkedQueue_

#include "node.h"
#include "xcept.h"
#include "absqueue.h"

template<class T>
class LinkedQueue : AbstractQueue<T> {
// FIFO objects
   public:
      LinkedQueue() {front = rear = 0;} // constructor
      ~LinkedQueue(); // destructor
      bool IsEmpty() const
           {return ((front) ? false : true);}
      bool IsFull() const;
      T First() const; // return first element
      T Last() const; // return last element
      AbstractQueue<T>& Add(const T& x);
      AbstractQueue<T>& Delete(T& x);
   private:
      Node<T> *front;  // pointer to first node
      Node<T> *rear;   // pointer to last node
};

template<class T>
LinkedQueue<T>::~LinkedQueue()
{// Queue destructor.  Delete all nodes.
   Node<T> *next;
   while (front) {
      next = front->link; 
      delete front; 
      front = next;
      }
}

template<class T>
bool LinkedQueue<T>::IsFull() const
{// Is the queue full?
   Node<T> *p;
   try {p = new Node<T>;
        delete p;
        return false;}
   catch (NoMem) {return true;}
}

template<class T>
T LinkedQueue<T>::First() const
{// Return first element of queue.  Throw
 // OutOfBounds exception if the queue is empty.
   if (IsEmpty()) throw OutOfBounds();
   return front->data;
}

template<class T>
T LinkedQueue<T>::Last() const
{// Return last element of queue.  Throw
 // OutOfBounds exception if the queue is empty.
   if (IsEmpty()) throw OutOfBounds();
   return rear->data;
}

template<class T>
AbstractQueue<T>& LinkedQueue<T>::Add(const T& x)
{// Add x to rear of queue.  Do not catch
 // possible NoMem exception thrown by new.

   // create node for new element
   Node<T> *p = new Node<T>;
   p->data = x;
   p->link = 0;

   // add new node to rear of queue
   if (front) rear->link = p;  // queue not empty
   else front = p;             // queue empty
   rear = p;

   return *this;
}

template<class T>
AbstractQueue<T>& LinkedQueue<T>::Delete(T& x)
{// Delete first element and put it in x.  Throw
 // OutOfBounds exception if the queue is empty.

   if (IsEmpty()) throw OutOfBounds();

   // save element in first node
   x = front->data;

   // delete first node
   Node<T> *p = front;
   front = front->link;
   delete p;

   return *this;
}

#endif
