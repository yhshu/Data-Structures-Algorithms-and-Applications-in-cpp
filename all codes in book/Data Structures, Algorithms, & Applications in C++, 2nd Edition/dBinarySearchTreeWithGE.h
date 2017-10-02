// extension of binary search tree with duplicates
// includes findGE

#ifndef dBinarySearchTreeWithGE_
#define dBinarySearchTreeWithGE_



#include "dBinarySearchTree.h"

using namespace std;

template<class K, class E>
class dBinarySearchTreeWithGE : public dBinarySearchTree<K,E>
{
   public:
      pair<const K, E>* findGE(const K& theKey) const;
};

template<class K, class E>
pair<const K, E>* dBinarySearchTreeWithGE<K,E>::findGE(const K& theKey) const
{// Return pointer to pair with smallest key >= theKey.
 // Return NULL if no element has key >= theKey.
   binaryTreeNode<pair<const K, E> > *currentNode = root;
   pair<const K, E> *bestElement = NULL; // element with smallest key
                                         // >= theKey found so far
   // search the tree
   while (currentNode != NULL)
      // is currentNode->element a candidate?
      if (currentNode->element.first >= theKey)
      {// yes, currentNode->element is
       // a better candidate than bestElement
         bestElement = &currentNode->element;
         // smaller keys in left subtree only
         currentNode = currentNode->leftChild;
      }
      else
         // no, currentNode->element.first is too small
         // try right subtree
         currentNode = currentNode->rightChild;

   return bestElement;
}
#endif
