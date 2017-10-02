
// indexed binary search tree with duplicates

#ifndef DIndexedBSTree_
#define DIndexedBSTree_

#include "dbst.h" 
#include "stdlib.h" 

template<class E, class K>
class DIndexedBSTree : public DBSTree<E, K> {
   public:
      bool IndexedSearch(int k, E& e);
      DIndexedBSTree<E,K>& Insert(const E& e);
      DIndexedBSTree<E,K>& Delete(const K& k, E& e);
      DIndexedBSTree<E,K>& IndexedDelete(int k, E& e);
   private:
      void Reset(int r, const K& k);
};


template<class E, class K>
bool DIndexedBSTree<E,K>::IndexedSearch(int k, E& e)
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
DIndexedBSTree<E,K>& DIndexedBSTree<E,K>::
                     Insert(const E& e)
{// Insert e even if it is a duplicate.
   BinaryTreeNode<E> *pp = 0;  // pp is parent of p
   BinaryTreeNode<E> *p = root;
   K k = e; // extract key from e
   // search for k
   while (p) {
      pp = p;
      if (k < p->data) {
         // insert will be in left subtree of p
         p->data.LeftSize++;
         p = p->LeftChild;}
      else if (e > p->data) p = p->RightChild;
           else // make a random decision
                if (rand() % 2) {
                   p->data.LeftSize++;
                   p = p->LeftChild;}
                else p = p->RightChild;
      }

   // get a node for e
   p = new BinaryTreeNode<E> (e);
   // cannot reset LeftSize fields because it is
   // hard to find proper nodes when e equals
   // some existing elements
  
   // attach node p to pp
   p->data.LeftSize = 1;
   if (root) // tree not empty
      if (e < pp->data)
         pp->LeftChild = p;
      else if (e > pp->data)
              pp->RightChild = p;
           else // equal keys, pp has at most one child
                // figure out where p belongs
                if (pp->data.LeftSize == 2 && !pp->LeftChild)
                   pp->LeftChild = p;
                else pp->RightChild = p;
   else // insertion into empty tree
        root = p;

   return *this;
}

template<class E, class K>
void DIndexedBSTree<E,K>::
       Reset(int r, const K& k)
{// Add r to LeftSize on path to k.
   BinaryTreeNode<E> *p = root;
   while (p)
      if (k < p->data) {
         p->data.LeftSize += r;
         p = p->LeftChild;}
      else if (k > p->data) p = p->RightChild;
           else return;
}


template<class E, class K>
DIndexedBSTree<E,K>& DIndexedBSTree<E,K>::
                     Delete(const K& k, E& e)
{// Delete element that matches k.
 // Put deleted element in e.
 // Throw BadInput exception if no matching element.
   // Find element to delete
   BinaryTreeNode<E> *pp = 0;  // parent of p
   BinaryTreeNode<E> *p = root;
   while (p && p->data != k) {
      pp = p;
      if (k < p->data) {
         p->data.LeftSize--;
         p = p->LeftChild;}
      else p = p->RightChild;
      }
   if (!p) {Reset(1, k);
            throw BadInput();} // not found

   e = p->data;  // save matching element

   // proceed to delete from tree
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

   return *this;
}

template<class E, class K>
DIndexedBSTree<E,K>& DIndexedBSTree<E,K>::
                     IndexedDelete(int k, E& e)
{// Delete the k'th element.  Put deleted element in e.
 // Throw BadInput exception if no k'th element.
   // find element to delete
   BinaryTreeNode<E> *pp = 0;  // parent of p
   BinaryTreeNode<E> *p = root;
   while (p && p->data.LeftSize != k) {
      pp = p;
      if (k < p->data.LeftSize) {
         p->data.LeftSize--;
         p = p->LeftChild;}
      else {k -= p->data.LeftSize;
            p = p->RightChild;}
      }
   if (!p) {// no element to delete, reset LeftSize
            p = root;
            while (p)
               if (k < p->data.LeftSize) {
                  p->data.LeftSize--;
                  p = p->LeftChild;}
               else {k -= p->data.LeftSize;
                     p = p->RightChild;}

             throw BadInput();
             }

   e = p->data;  // save matching element

   // proceed to delete from tree
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

   return *this;
}

#endif;
