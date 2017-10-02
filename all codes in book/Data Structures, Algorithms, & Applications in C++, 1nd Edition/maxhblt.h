// height balanced leftist trees
#ifndef MaxHBLT_
#define MaxHBLT_

#include <stdlib.h>
#include <iostream.h>
#include "xcept.h"
#include "swap.h"
#include "queue.h"
#include "hbltnode.h"

template<class T>
class MaxHBLT {
   public:
      MaxHBLT() {root = 0;}
      ~MaxHBLT() {Free(root);}
      T Max() {if (!root) throw OutOfBounds();
               return root->data;}
      MaxHBLT<T>& Insert(const T& x);
      MaxHBLT<T>& DeleteMax(T& x);
      MaxHBLT<T>& Meld(MaxHBLT<T>& x) {
                Meld(root,x.root);
                x.root = 0;
                return *this;}
      void Initialize(T a[], int n);
      void Output() const {Output(root); cout << endl;}
   private:
      void Free(HBLTNode<T> *t);
      void Meld(HBLTNode<T>* &x, HBLTNode<T>* y);
      void Output(HBLTNode<T> *t) const;
      HBLTNode<T> *root;  // pointer to tree root
};

template<class T>
void MaxHBLT<T>::Free(HBLTNode<T> *t)
{// Delete all nodes in tree rooted at t.
 // Use a postorder traversal.
   if (t) {Free(t->LeftChild);
           Free(t->RightChild);
           delete t;}
}

template<class T>
void MaxHBLT<T>::Meld(HBLTNode<T>* &x, HBLTNode<T>* y)
{// Meld leftist trees with roots *x and *y.
 // Return pointer to new root in x.
   if (!y) return; // y is empty
   if (!x) // x is empty
      {x = y;
       return;}

   // neither is empty
   if (x->data < y->data) Swap(x,y);
   // now x->data >= y->data
   Meld(x->RightChild,y);
   if (!x->LeftChild) {// left subtree empty
         // swap subtrees
         x->LeftChild = x->RightChild;
         x->RightChild = 0;
         x->s = 1;}
   else {// see if subtrees to be swapped
         if (x->LeftChild->s < x->RightChild->s)
            Swap(x->LeftChild,x->RightChild);
         x->s = x->RightChild->s + 1;}
}

template<class T>
MaxHBLT<T>& MaxHBLT<T>::Insert(const T& x)
{// Insert x into the leftist tree.
 // Create tree with one node.
   HBLTNode<T> *q = new HBLTNode<T> (x,1);
   // meld q and original tree
   Meld(root,q);
   return *this;
}

template<class T>
MaxHBLT<T>& MaxHBLT<T>::DeleteMax(T& x)
{// Delete max element and put it in x.
   if (!root) throw OutOfBounds();

   // tree not empty
   x = root->data;  // max element
   HBLTNode<T> *L = root->LeftChild;
   HBLTNode<T> *R = root->RightChild;
   delete root;
   root = L;
   Meld(root,R);
   return *this;
}

template<class T>
void MaxHBLT<T>::Initialize(T a[], int n)
{// Initialize hblt with n elements.
   Queue<HBLTNode<T> *> Q(n);
   Free(root);  // delete old nodes
   // initialize queue of trees
   for (int i = 1; i <= n; i++) {
      // create trees with one node each
      HBLTNode<T> *q = new HBLTNode<T> (a[i],1);
      Q.Add(q);
      }

   // repeatedly meld from queue
   HBLTNode<T> *b, *c;
   for (i = 1; i <= n - 1; i++) {
      // delete and meld two trees
      Q.Delete(b).Delete(c);
      Meld(b,c);
      // put melded tree on queue
      Q.Add(b);
      }

   if (n) Q.Delete(root);
}

template<class T>
void MaxHBLT<T>::Output(HBLTNode<T> *t) const
{
   if (t) {Output(t->LeftChild);
           Output(t->RightChild);
           cout << t->data << "  ";
          }
}

#endif
