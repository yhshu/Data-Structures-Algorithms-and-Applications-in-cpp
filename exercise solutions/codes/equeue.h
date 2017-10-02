
// linked queue extended to include
// Size, >>, and <<

#ifndef LinkedQueue_
#define LinkedQueue_
#include "node.h"
#include "xcept.h"

template<class T>
class LinkedQueue {
   friend ostream& operator<<
          (ostream&, const LinkedQueue<T>&);
   friend istream& operator>>
          (istream&, LinkedQueue<T>&);
   public:
      LinkedQueue() {front = rear = 0;} // constructor
      ~LinkedQueue() {Erase();}
      bool IsEmpty() const
           {return ((front) ? false : true);}
      bool IsFull() const;
      T First() const; // return first element
      T Last() const; // return last element
      LinkedQueue<T>& Add(const T& x);
      LinkedQueue<T>& Delete(T& x);
      int Size() const;
   private:
      Node<T> *front;  // pointer to first node
      Node<T> *rear;   // pointer to last node
      void Erase();    // delete all nodes
};

template<class T>
void LinkedQueue<T>::Erase()
{// Delete all nodes.
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
LinkedQueue<T>& LinkedQueue<T>::Add(const T& x)
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
LinkedQueue<T>& LinkedQueue<T>::Delete(T& x)
{// Delete first element and return in x.  Throw
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

template<class T>
int LinkedQueue<T>::Size() const
{// Return number of elements in the queue.
   int size = 0;
   Node<T> *current = front;
   while (current) {
      size++;
      current = current->link;
      }
   return size;
}

// overload >>
template<class T>
istream& operator>>(istream& in, LinkedQueue<T>& q)
{// Input queue q from front to rear.
   // first delete all elements from q
   q.Erase();

   // determine size of input queue
   int size;
   cout << "Enter size of queue" << endl;
   in >> size;

   if (!size) // no elements
      return in;

   // at least one element to input
   // input the queue elements and link together
   cout << "Enter the elements from front to rear"
        << endl;

   // get first element
   q.rear = q.front = new Node<T>;
   in >> q.front->data;

   // get remaining elements
   for (int i = 2; i <= size ; i++) {
      q.rear->link = new Node<T>;
      q.rear = q.rear->link;
      in >> q.rear->data;
      }

   // set pointer in rear node
   q.rear->link = 0;

   return in;
}

// overload <<
template <class T>
ostream& operator<<(ostream& out,
                    const LinkedQueue<T>& q)
{// Output the queue q from front to rear

   // output queue size
   int size = q.Size();
   out << "The queue has " << size
       << " element(s)" << endl;

   // output queue elements
   out << "The element(s) from front to rear are"
       << endl;
   Node<T> *current = q.front;
   for (int i = 1; i <= size ; i++) {
      out << current->data << ' ';
      current = current->link;
      }
   out << endl;

   return out;
}

#endif
