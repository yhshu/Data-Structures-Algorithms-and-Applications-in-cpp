
#ifndef Node_
#define Node_

template <class T> class LinkedStack;
template <class T> class LinkedQueue;

template <class T>
class Node {
   friend LinkedStack<T>;
   friend LinkedQueue<T>;
   friend ostream& operator<<
          (ostream&, const LinkedStack<T>&);
   friend istream& operator>>
          (istream&, LinkedStack<T>&);
   friend ostream& operator<<
          (ostream&, const LinkedQueue<T>&);
   friend istream& operator>>
          (istream&, LinkedQueue<T>&);
   private:
      T data;
      Node<T> *link;
};

#endif
