

#ifndef Node23_
#define Node23_

template <class E, class K> class TwoThree;

template <class E, class K>
class Node23 {
   friend TwoThree<E, K>;
   private:
      E LData,  // place for first element
        RData;  // place for possible second element
      Node23<E,K> *LChild,  // pointer to left child
                  *MChild,  // pointer to middle child
                  *RChild;  // pointer to possible right child
};

#endif
