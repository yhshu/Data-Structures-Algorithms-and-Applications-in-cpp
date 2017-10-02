// file queue.h
// formual based queue

#ifndef Queue_
#define Queue_

#include <stdlib.h>
#include <iostream.h>
#include "xcept.h"

template<class T>
class Queue {
// FIFO objects
   public:
      Queue(int MaxQueueSize = 10);
      ~Queue() {delete [] queue;}
      bool IsEmpty() const {return front == rear;}
      bool IsFull() const {return (
           ((rear + 1) % MaxSize == front) ? 1 : 0);}
      T First() const; // return front element
      T Last() const; // return last element
      Queue<T>& Add(const T& x);
      Queue<T>& Delete(T& x);
   private:
      int front;   // one counterclockwise from first
      int rear;    // last element
      int MaxSize; // size of array queue
      T *queue;    // element array
};

template<class T>
Queue<T>::Queue(int MaxQueueSize)
{// Create an empty queue whose capacity
 // is MaxQueueSize.
   MaxSize = MaxQueueSize + 1;
   queue = new T[MaxSize];
   front = rear = 0;
}

template<class T>
T Queue<T>::First() const
{// Return first element of queue.  Throw
 // OutOfBounds exception if the queue is empty.
   if (IsEmpty()) throw OutOfBounds();
   return queue[(front + 1) % MaxSize];
}

template<class T>
T Queue<T>::Last() const
{// Return last element of queue.  Throw
 // OutOfBounds exception if the queue is empty.
   if (IsEmpty()) throw OutOfBounds();
   return queue[rear];
}

template<class T>
Queue<T>& Queue<T>::Add(const T& x)
{// Add x to the rear of the queue.  Throw
 // NoMem exception if the queue is full.
   if (IsFull()) throw NoMem();
   rear = (rear + 1) % MaxSize;
   queue[rear] = x;
   return *this;
}

template<class T>
Queue<T>& Queue<T>::Delete(T& x)
{// Delete first element and put in x.  Throw
 // OutOfBounds exception if the queue is empty.
   if (IsEmpty()) throw OutOfBounds();
   front = (front + 1) % MaxSize;
   x = queue[front];
   return *this;
}

#endif
