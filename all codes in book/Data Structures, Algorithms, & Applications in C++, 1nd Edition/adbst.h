
// dbst.h
// binary search tree with duplicate values
#ifndef DBSTree_
#define DBSTree_

#include "dbinary.h"
#include "xcept.h"

template<class E, class K>
class DBSTree : public BinaryTree<E> {
   public:
      bool Search(const K& k, E& e) const;
      bool FindGE(const K& k, K& Kout) const;
      DBSTree<E,K>& Insert(const E& e);
      DBSTree<E,K>& Delete(const K& k, E& e);
      void Ascend() {InOutput();}
};

template<class E, class K>
bool DBSTree<E,K>::
           Search(const K& k, E& e) const
{// Search for element that matches k.
   // pointer p starts at the root and moves through
   // the tree looking for an element with key k
   BinaryTreeNode<E> *p = root;
   while (p) {// examine p->data
      if (k < p->data) p = p->LeftChild;
      else if (k > p->data) p = p->RightChild;
           else {// found element
                 e = p->data;
                 return true;}}
   return false;
}

template<class E, class K>
DBSTree<E,K>& DBSTree<E,K>::Insert(const E& e)
{// Insert e.
   BinaryTreeNode<E> *p = root,  // search pointer
                     *pp = 0;    // parent of p
   // find place to insert
   while (p) {// examine p->data
      pp = p;
      // move p to a child
      if (e <= p->data) p = p->LeftChild;
      else p = p->RightChild;
      }

   // get a node for e and attach to pp
   BinaryTreeNode<E> *r = new BinaryTreeNode<E> (e);
   if (root) {// tree not empty
      if (e < pp->data) pp->LeftChild = r;
      else pp->RightChild = r;}
   else // insertion into empty tree
        root = r;

   return *this;
}

template<class E, class K>
DBSTree<E,K>& DBSTree<E,K>::
           Delete(const K& k, E& e)
{// Delete element with key k and put it in e.

   // set p to point to node with key k
   BinaryTreeNode<E> *p = root, // search pointer
                     *pp = 0;   // parent of p
   while (p && p->data != k){// move to a child of p
      pp = p;
      if (k < p->data) p = p->LeftChild;
      else p = p->RightChild;
      }
   if (!p) throw BadInput(); // no element with key k

   e = p->data;  // save element to delete

   // restructure tree
   // handle case when p has two children
   if (p->LeftChild && p->RightChild) {// two children
      // convert to zero or one child case
      // find largest element in left subtree of p
      BinaryTreeNode<E> *s = p->LeftChild,
                        *ps = p;  // parent of s
      while (s->RightChild) {// move to larger element
         ps = s;
         s = s->RightChild;}

      // move largest from s to p
      p->data = s->data;
      p = s;
      pp = ps;}

   // p has at most one child
   // save child pointer in c
   BinaryTreeNode<E> *c;
   if (p->LeftChild) c = p->LeftChild;
   else c = p->RightChild;

   // delete p
   if (p == root) root = c;
   else {// is p left or right child of pp?
         if (p == pp->LeftChild)
              pp->LeftChild = c;
         else pp->RightChild = c;}
   delete p;

   return *this;
}

template<class E, class K>
bool DBSTree<E,K>::FindGE(const K& k, K& Kout) const
{// Find smallest element with value >= k.
   BinaryTreeNode<E> *p = root,  // search pointer
                     *s = 0;     // pointer to smallest
                                 // >= k found so far
   // search the tree
   while (p) {
      // is p a candidate?
      if (k <= p->data) {// yes
          s = p;  // p is a better candidate than s
          // smaller elements in left subtree only
          p = p->LeftChild;}
      else  // no, p->data too small, try right subtree
          p = p->RightChild;
      }

   if (!s) return false; // not found
   Kout = s->data;
   return true;
}

#endif
