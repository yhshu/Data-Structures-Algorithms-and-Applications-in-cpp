
#ifndef HBLTNode_
#define HBLTNode_

template <class T> class MaxHBLT;
template <class T> class MinHBLT;

template <class T>
class HBLTNode {
   friend MaxHBLT<T>;
   friend MinHBLT<T>;
   public:
      HBLTNode(const T& e, const int sh)
       {data = e;
        s = sh;
        LeftChild = RightChild = 0;}
   private:
      int s; // s value of node
      T data;
      HBLTNode<T> *LeftChild, *RightChild;
};

#endif
