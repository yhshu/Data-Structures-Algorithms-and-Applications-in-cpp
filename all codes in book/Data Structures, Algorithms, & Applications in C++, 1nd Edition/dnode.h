#ifndef DoubleNode_
#define DoubleNode_

template <class T> class Double;

template <class T>
class DoubleNode {
   friend Double<T>;
   private:
      T data;
      DoubleNode<T> *left, *right;
};

#endif
