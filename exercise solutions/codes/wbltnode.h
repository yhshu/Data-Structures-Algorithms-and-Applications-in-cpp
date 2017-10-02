

#ifndef WBLTNode_
#define WBLTNode_

template <class T> class MaxWBLT;

template <class T>
class WBLTNode {
   friend MaxWBLT<T>;
   public:
      WBLTNode(const T& e, const int wt)
       {data = e;
        w = wt;
        LeftChild = RightChild = 0;}
   private:
      int w; // weight of node
      T data;
      WBLTNode<T> *LeftChild, *RightChild;
};

#endif
