
// linked stack extended to include
// size and overloading of << and >>

#ifndef LinkedStack_
#define LinkedStack_

#include "node.h"
#include "xcept.h"

template<class T>
class LinkedStack {
   friend ostream& operator<<
          (ostream&, const LinkedStack<T>&);
   friend istream& operator>>
          (istream&, LinkedStack<T>&);
   public:
      LinkedStack() {top = 0;}
      ~LinkedStack();
      bool IsEmpty() const {return top == 0;}
      bool IsFull() const;
      T Top() const;
      LinkedStack<T>& Add(const T& x);
      LinkedStack<T>& Delete(T& x);
      int Size() const;
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

template<class T>
int LinkedStack<T>::Size() const
{// Return the number of elements in the stack.
   Node<T> *current = top;
   int size = 0;
   while (current) {// go down stack
      size++;
      current = current->link;
      }

   return size;
}

// overload >>
template<class T>
istream& operator>>(istream& in,
                    LinkedStack<T>& s)
{// Input stack s from top to bottom.
   // empty out current stack
   while (s.top) {// delete nodes one by one
      Node<T> *next;
      next = s.top->link;
      delete s.top;
      s.top = next;
      }

   // input stack size
   int size;
   cout << "Enter size of stack" << endl;
   in >> size;

   if (!size) // empty stack
      return in;

   // nonempty stack
   cout << "Enter the elements from top to bottom"
        << endl;

   // get top element
   s.top = new Node<T>;
   cin >> s.top->data;
  
   // set up for remaining elements
   Node<T> *last = s.top;  // pointer to bottom
                           // node in stack

   // get remaining stack elements
   // and link into chain
   for (int i = 2; i <= size ; i++) {
      Node<T> *x = new Node<T>;  // create node
      in >> x->data;             // set data field
      last->link = x;            // link into chain
      last = x;
      }
   last->link = 0;

   return in;
}

// overload <<
template <class T>
ostream& operator<<(ostream& out,
                    const LinkedStack<T>& s)
{// Output the stack s from top to bottom

   // output stack size
   out << "The stack has " << s.Size()
       << " element(s)" << endl;

   // output stack elements
   out << "The element(s) from top to bottom are"
       << endl;
   Node<T> *current = s.top;
   while (current) {
      out << current->data << ' ';
      current = current->link;
      }
   out << endl;

   return out;
}

#endif;
