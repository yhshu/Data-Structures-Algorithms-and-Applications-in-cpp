
#ifndef HBLTNode_
#define HBLTNode_

template <class T> class MaxHBLT;

template <class T>
class HBLTNode {
   friend MaxHBLT<T>;
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
