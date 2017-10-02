#ifndef DoubleNode_
#define DoubleNode_

template <class T> class Double;
template <class T> class DoubleCircular;
template <class T> class DoubleCircularIterator;
template <class T> class HDoubleCircular;
template <class T> class HDoubleCircularIterator;

template <class T>
class DoubleNode {
   friend Double<T>;
   friend DoubleCircular<T>;
   friend DoubleCircularIterator<T>;
   friend HDoubleCircular<T>;
   friend HDoubleCircularIterator<T>;
//   private:
   public:
      T data;
      DoubleNode<T> *left, *right;
};

#endif
