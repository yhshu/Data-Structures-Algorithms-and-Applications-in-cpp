
#ifndef IAVLNode_
#define IAVLNode_

template <class E, class K> class IndexedAVLtree;
template <class E, class K> class IndexedDAVLtree;
template <class T> class IndexedAVLList;

template <class E, class K>
class IAVLNode {
   friend IndexedAVLtree<E,K>;
   friend IndexedDAVLtree<E,K>;
   friend IndexedAVLList<E>;
   public:
      IAVLNode() {LeftChild = RightChild = 0;}
      IAVLNode(const E& e)
            {data = e; bf = 0; 
             LeftSize = 1;
             LeftChild = RightChild = 0;}
   private:
      E data;
      int bf;                    // balance factor
      int LeftSize;              // size of left subtree
                                 // plus one
      IAVLNode<E,K> *LeftChild,  // left subtree
                    *RightChild; // right subtree
};

#endif
