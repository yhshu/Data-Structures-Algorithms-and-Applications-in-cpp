// extension of binarySearchTree to include method to insert with visit

#ifndef binarySearchTreeWithVisit_
#define binarySearchTreeWithVisit_



#include "binarySearchTree.h"

using namespace std;

template<class K, class E>
class binarySearchTreeWithVisit : public binarySearchTree<K,E>
{
   public:
      void insert(const pair<const K, E>&, void(*visit)(E& u));
};

template<class K, class E>
void binarySearchTreeWithVisit<K,E>::insert
           (const pair<const K, E>& thePair, void(*visit)(E& u))
{// Insert thePair into the tree if no matching pair present.
 // Visit existing pair, if any, with same key.

   // search for a matching element
   binaryTreeNode<pair<const K, E> > *p = root, // search pointer
                                     *pp = 0;   // parent of p
   while (p != NULL)
   {// examine p->element
      pp = p;
      // move p to a child
      if (thePair.first < p->element.first)
         p = p->leftChild;
      else
         if (thePair.first > p->element.first)
            p = p->rightChild;
         else
         {// visit the element
            visit(p->element.second);
            return;
         }
   }

   // get a node for thePair and attach to pp
   binaryTreeNode<pair<const K, E> > *newNode
                 = new binaryTreeNode<pair<const K, E> > (thePair);
   if (root != NULL) // the tree is not empty
      if (thePair.first < pp->element.first)
         pp->leftChild = newNode;
      else
         pp->rightChild = newNode;
   else
      root = newNode; // insertion into empty tree
   treeSize++;
}
#endif
