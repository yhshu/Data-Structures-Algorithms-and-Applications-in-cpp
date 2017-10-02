
// preorder traversal
// nonrecursive code

#include <iostream.h>
#include "lstack.h"
#include "btnode1.h"
#include "xcept.h"


template <class T>
void Visit(BinaryTreeNode<T> *x)
{// Visit node *x, just output data field.
   cout << x->data << ' ';
}

template <class T>
void PreOrder(BinaryTreeNode<T> *t)
{// Preorder traversal of *t.
   LinkedStack<BinaryTreeNode<T> *> S;
   BinaryTreeNode<T> *current = t;
   while (true) {
      // traverse subtree rooted at current
      // in preorder
  
      // is subtree empty?
      if (!current) {// yes it is
         // get a subtree to traverse from
         // the stack
         try {S.Delete(current);}
         catch (OutOfBounds)
            {// no untraversed subtrees left
             return;
            }
         }

      // first visit the root
      Visit(current);

      // save pointer to right subtree for
      // future traversal
      if (current->RightChild)
         S.Add(current->RightChild);

      // move into left subtree
      current = current->LeftChild;
      }
}


void main(void)
{
   BinaryTreeNode<int> u, v, w, x, y, z;
   u.data = 1;
   v.data = 2;
   w.data = 3;
   x.data = 4;
   y.data = 5;
   z.data = 6;
   x.LeftChild = &y;
   x.RightChild = &z;
   u.LeftChild = &x;
   u.RightChild = &v;
   v.LeftChild = v.RightChild = 0;
   w.LeftChild = w.RightChild = 0;
   y.LeftChild = y.RightChild = z.RightChild = 0;
   z.LeftChild = &w;

   // traverse u
   cout << "Preorder sequence is ";
   PreOrder(&u);
   cout << endl;
}
