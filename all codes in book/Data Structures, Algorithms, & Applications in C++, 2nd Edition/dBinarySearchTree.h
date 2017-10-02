// linked binary tree implementation of a binary search tree with
// duplicates
// implements all dictionary and bsTree methods

#ifndef dBinarySearchTree_
#define dBinarySearchTree_



#include "binarySearchTree.h"

using namespace std;

template<class K, class E>
class dBinarySearchTree : public binarySearchTree<K,E>
{
   public:
      // override insert method of binarySearchTree
      void insert(const pair<const K, E>&);
};

template<class K, class E>
void dBinarySearchTree<K,E>::insert(const pair<const K, E>& thePair)
{// Insert thePair into the tree. Duplicate keys permitted.
   // find place to insert
   binaryTreeNode<pair<const K, E> > *p = root,
                                     *pp = NULL;
   while (p != NULL)
   {// examine p->element
      pp = p;
      // move p to a child
      if (thePair.first <= p->element.first)
         p = p->leftChild;
      else
         p = p->rightChild;
   }

   // get a node for thePair and attach to pp
   binaryTreeNode<pair<const K, E> > *newNode
                 = new binaryTreeNode<pair<const K, E> > (thePair);
   if (root != NULL) // the tree is not empty
      if (thePair.first <= pp->element.first)
         pp->leftChild = newNode;
      else
         pp->rightChild = newNode;
   else
      root = newNode; // insertion into empty tree
   treeSize++;
}
#endif
