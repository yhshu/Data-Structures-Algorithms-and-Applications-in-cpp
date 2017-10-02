 
#ifndef BinaryTreeNode_
#define BinaryTreeNode_

template <class T> class BinaryTree;
template <class T> class IndexedBinaryTree;
template <class E, class K> class BSTree;
template <class E, class K> class DBSTree;
template <class E, class K> class IndexedBSTree;
template <class E, class K> class DIndexedBSTree;

template <class T>
class BinaryTreeNode {
   friend BinaryTree<T>;
   friend IndexedBinaryTree<T>;
   friend void PlaceBoosters(BinaryTreeNode<T> *);
   friend BSTree<T,int>;
   friend DBSTree<T,int>;
   friend IndexedBSTree<T,int>;
   friend DIndexedBSTree<T,int>;
   public:
      BinaryTreeNode() {LeftChild = RightChild = 0;}
      BinaryTreeNode(const T& e)
            {data = e; LeftChild = RightChild = 0;}
      BinaryTreeNode(const T& e, BinaryTreeNode *l,
                     BinaryTreeNode *r)
       {data = e; LeftChild = l; RightChild = r;}
//   private:
      T data;
      BinaryTreeNode<T> *LeftChild,  // left subtree
                        *RightChild; // right subtree
};

#endif
