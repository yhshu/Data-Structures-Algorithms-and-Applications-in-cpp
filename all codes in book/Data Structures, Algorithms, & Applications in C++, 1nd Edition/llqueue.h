// header file llqueue.h

#ifndef LinkedQueue_
#define LinkedQueue_
#include "node.h"

template<class type>
class LinkedQueue {
// FIFO objects
   public:
      LinkedQueue() {front = rear = 0;}; // constructor
      ~LinkedQueue(); // destructor
      int IsEmpty()
         {return ((front) ? 0 : 1);}
      int IsFull();
      int First(type& x); // return first element of queue in x
      int Last(type& x); // return last element of queue in x
      int operator +(type x); // add x to queue
      int operator -(type& x); // delete x from queue
      // First, + and - return 0 on failure and 1 on success
   private:
      Node<type> *front, *rear;
};

template<class type>
LinkedQueue<type>::~LinkedQueue()
{
Node<type> *i;
while (front) {i = front->link; delete front; front = i;}
}

template<class type>
int LinkedQueue<type>::IsFull()
{
Node<type> *i;
i = new Node<type>;
if (i) {delete i; return 0;};
return 1;
}

template<class type>
int LinkedQueue<type>::First(type& x)
//set x to first element
{
if (IsEmpty()) return 0; //First fails
x = front->data;
return 1;
}

template<class type>
int LinkedQueue<type>::Last(type& x)
//set x to last element
{
if (IsEmpty()) return 0; //Last fails
x = rear->data;
return 1;
}

template<class type>
int LinkedQueue<type>::operator+(type x)
//add x to queue
{
Node<type> *i;
i = new Node<type>;
if (i) {
     i->data = x; i->link = 0;
     if (front) rear->link = i;
     else front = i;
     rear = i; return 1;
        };
return 0; // add fails 
}

template<class type>
int LinkedQueue<type>::operator-(type& x)
//delete first element and return in x
{
if (IsEmpty()) return 0; //delete fails
x = front->data;
Node<type> *i = front;
front = front->link;
delete i;
return 1;
}

#endif
