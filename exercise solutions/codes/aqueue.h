
// formual based queue
// includes Size, <<, and >>

#ifndef Queue_
#define Queue_

#include <stdlib.h>
#include <iostream.h>
#include "xcept.h"

template<class T>
class Queue {
   friend ostream& operator<<
          (ostream&, const Queue<T>&);
   friend istream& operator>>
          (istream&, Queue<T>&);
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
      int Size() const
          {return (MaxSize + rear - front) % MaxSize;}
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
{// Delete first element and put it in x.  Throw
 // OutOfBounds exception if the queue is empty.
   if (IsEmpty()) throw OutOfBounds();
   front = (front + 1) % MaxSize;
   x = queue[front];
   return *this;
}

// overload >>
template<class T>
istream& operator>>(istream& in, Queue<T>& q)
{// Input queue q from front to rear.
   // input and verify queue size
   int size;
   cout << "Enter size of queue" << endl;
   in >> size;
   if (size >= q.MaxSize) throw NoMem(); // fail

   // we shall put the elements in queue[0:size-1]
   q.front = q.MaxSize - 1;  // one counter clockwise
   q.rear = size - 1;        // at last element

   // input the queue elements and store in array
   cout << "Enter the elements from front to rear"
        << endl;
   for (int i = 0; i <= q.rear ; i++)
      in >> q.queue[i];

   return in;
}

// overload <<
template <class T>
ostream& operator<<(ostream& out,
                    const Queue<T>& q)
{// Output the queue q from front to rear

   // output queue size
   int size = q.Size();
   out << "The queue has " << size
       << " element(s)" << endl;

   // output queue elements
   out << "The element(s) from front to rear are"
       << endl;
   int current = (q.front + 1) % q.MaxSize;
   for (int i = 1; i <= size ; i++) {
      out << q.queue[current] << ' ';
      current = (current + 1) % q.MaxSize;
      }
   out << endl;

   return out;
}

#endif
