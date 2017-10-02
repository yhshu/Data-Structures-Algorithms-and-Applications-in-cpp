
// header file deque.h
// formula-based deque derived from the class Queue
// data members of Queue are protected (not private)
#ifndef Deque_
#define Deque_

#include<stdlib.h>
#include<iostream.h>
#include "cqueue.h"
#include "xcept.h"

template<class T>
class Deque : protected Queue<T>
{
    friend ostream& operator<<
          (ostream&, const Deque<T>&);
    friend istream& operator>>
          (istream&, Deque<T>&);
   public:
      Deque(int MaxDequeSize = 10)
         : Queue<T> (MaxDequeSize) {}
      bool IsEmpty() const
           {return Queue<T>::IsEmpty();}
      bool IsFull() const
           {return Queue<T>::IsFull();}
      T Left() const
        {return First();}
      T Right() const
        {return Last();}
      Deque<T>& AddLeft(const T& x);
      Deque<T>& AddRight(const T& x)
                {Add(x); return *this;}
      Deque<T>& DeleteLeft(T& x)
                {Delete(x); return *this;}
      Deque<T>& DeleteRight(T& x);
};

template<class T>
Deque<T>& Deque<T>::AddLeft(const T& x)
{// Add x to left end of deque.
   // first see if there is space
   if (IsFull()) throw NoMem();

   // put x counterclockwise from current
   // leftmost element
   queue[front] = x;

   // move front counterclockwise
   if (front == 0) front = MaxSize - 1;
   else front--;

   return *this;
}

template<class T>
Deque<T>& Deque<T>::DeleteRight(T& x)
{// Delete rightmost element and put in x.

   // first make sure there is a last element
   if (IsEmpty()) throw OutOfBounds();

   // save last element in x
   x = queue[rear];

   // move rear counterclockwise
   if (rear == 0) rear = MaxSize - 1;
   else rear--;

   return *this;
}

// overload <<
template <class T>
ostream& operator<<(ostream& out,
                    const Deque<T>& q)
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
// overload >>
template<class T>
istream& operator>>(istream& in, Deque<T>& q)
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

#endif
