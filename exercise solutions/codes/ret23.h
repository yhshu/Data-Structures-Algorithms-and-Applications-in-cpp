


#ifndef ReturnPair23_
#define ReturnPair23_

template <class E, class K> class TwoThree;

template <class E, class K>
class ReturnPair23 {
   friend TwoThree<E, K>;
   private:
      E element;             
      Node23<E,K> *NodePtr;  // pointer to associated subtree
};

#endif
