#ifndef binaryTreeNode_
#define binaryTreeNode_

using namespace std;

template <class T>
struct binaryTreeNode
{
   T element;
   binaryTreeNode<T> *leftChild,   // left subtree
                     *rightChild;  // right subtree

   binaryTreeNode() {leftChild = rightChild = NULL;}
   binaryTreeNode(const T& theElement):element(theElement)
   {
      leftChild = rightChild = NULL;
   }
   binaryTreeNode(const T& theElement,
                  binaryTreeNode *theLeftChild,
                  binaryTreeNode *theRightChild)
                  :element(theElement)
   {
      leftChild = theLeftChild;
      rightChild = theRightChild;
   }
};

#endif
