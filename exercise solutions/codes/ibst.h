// file ibst.h
// indexed binary search tree

#ifndef IndexedBSTree_
#define IndexedBSTree_

#include "bst.h" 

template<class E, class K>
class IndexedBSTree : public BSTree<E,K> {
   public:
      bool IndexedSearch(int k, E& e);
      IndexedBSTree<E,K>& Insert(const E& e);
      IndexedBSTree<E,K>& Delete(const K& k, E& e);
      IndexedBSTree<E,K>& IndexedDelete(int k, E& e);
   private:
      void iDelete(E& e);
};

template<class E, class K>
bool IndexedBSTree<E,K>::IndexedSearch(int k, E& e)
{// Put the k'th element in e.
 // Return false iff there is no k'th element
   BinaryTreeNode<E> *p = root;
   while (p)
      if (k < p->data.LeftSize) p = p->LeftChild;
      else if (k > p->data.LeftSize) {
   	      k -= p->data.LeftSize;
              p = p->RightChild;}
           else {e = p->data;
                return true;}
   return false;
}


template<class E, class K>
IndexedBSTree<E,K>& IndexedBSTree<E,K>::
                    Insert(const E& e)
{// Insert e provided it is not a duplicate.
 // Pass BadInput exception if duplicate.

   BSTree<E, K>::Insert(e);
   // if e is a duplicate, the preceding insert
   // throws an exception and we do not get to
   // the following code

   // insert has succeeded, update LeftSize
   // by following search path to e
   BinaryTreeNode<E> *p = root;
   while (true)
      if (e < p->data) {
         // e was inserted in left subtree of p
         p->data.LeftSize++;
         p = p->LeftChild;}
      else if (e > p->data) p = p->RightChild;
           else {p->data.LeftSize = 1;
                 return *this;}
}

template<class E, class K>
void IndexedBSTree<E,K>::iDelete(E& e)
{// Actual delete function.
 // Delete element that matches e, put deleted
 // element in e.
   BinaryTreeNode<E> *pp = 0,  // pp is parent of p
                     *p = root;
   // follow path to e decrementing LeftSize each time
   // we move to a left subtree
   while (p->data != e) {
      pp = p;
      if (e < p->data) {
         p->data.LeftSize--;
         p = p->LeftChild;}
      else p = p->RightChild;
      }

   if (p->LeftChild && p->RightChild) {
      // p has two children
      // find largest element in left subtree of p
      // first move into left subtree, then make as
      // many right child moves as possible
      int ls = p->data.LeftSize - 1; // save value
      BinaryTreeNode<E> *ps = p,  // parent of s
                        *s = p->LeftChild;
      while (s->RightChild) {
         ps = s;
         s = s->RightChild;
         }

      // move largest element to p
      p->data = s->data;
      p->data.LeftSize = ls;
      // set pp and p so that p is node to delete
      pp = ps;
      p = s;
      }

   // now p has at most one child
   // save pointer to single subtree of p in s
   BinaryTreeNode<E> *s;
   if (p->LeftChild) s = p->LeftChild;
   else s = p->RightChild;

   // attach s to pp unless p is root
   if (p == root) root = s;
   else if (p == pp->LeftChild)
           pp->LeftChild = s;
        else pp->RightChild = s;

   delete p;
}


template<class E, class K>
IndexedBSTree<E,K>& IndexedBSTree<E,K>::
                    Delete(const K& k, E& e)
{// Delete element that matches k.  Put deleted
 // element in e.  Throw BadInput exception if
 // no element matches k.
   if (!Search(k,e)) throw BadInput();
   iDelete(e);
   return *this;
}

template<class E, class K>
IndexedBSTree<E,K>& IndexedBSTree<E,K>::
                    IndexedDelete(int k, E& e)
{// Delete the k'th element.  Put deleted element in e.
 // Throw BadInput exception if no k'th element.
   if (!IndexedSearch(k,e)) throw BadInput();
   iDelete(e);
   return *this;
}

#endif;
