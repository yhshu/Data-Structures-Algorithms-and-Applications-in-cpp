

#ifndef AVLNode_
#define AVLNode_

template <class E, class K> class AVLtree;
template <class E, class K> class DAVLtree;

template <class E, class K>
class AVLNode {
   friend AVLtree<E,K>;
   friend DAVLtree<E,K>;
   public:
      AVLNode() {LeftChild = RightChild = 0;}
      AVLNode(const E& e)
            {data = e; bf = 0; LeftChild = RightChild = 0;}
   private:
      E data;
      int bf;                   // balance factor
      AVLNode<E,K> *LeftChild,  // left subtree
                   *RightChild; // right subtree
};

#endif
