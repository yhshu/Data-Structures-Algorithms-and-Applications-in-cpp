
// erase a binary tree using postorder traversal

#include <iostream.h>
#include "lqueue.h"
#include "btnode1.h"
#include "xcept.h"

BinaryTreeNode<int> x,y,z;

template <class T>
void Visit(BinaryTreeNode<T> *x)
{// Visit node *x, just output data field.
   cout << x->data << ' ';
}

template <class T>
void PostOrder(BinaryTreeNode<T> *t)
{// Postorder traversal of *t.
   if (t) {
      PostOrder(t->LeftChild);   // do left subtree
      PostOrder(t->RightChild);  // do right subtree
      Visit(t);                  // visit tree root
      }
}

template <class T>
void Erase(BinaryTreeNode<T> * &t)
{// Delete all nodes of *t.
 // Use a postorder traversal.
   if (t) {
      Erase(t->LeftChild);   // delete left subtree
      Erase(t->RightChild);  // delete right subtree
      delete t;              // delete tree root
      t = 0;
      }
}

void main(void)
{
   BinaryTreeNode<int> *x = new BinaryTreeNode<int>,
                       *y = new BinaryTreeNode<int>,
                       *z = new BinaryTreeNode<int>;

   x->data = 1;
   y->data = 2;
   z->data = 3;
   x->LeftChild = y;
   x->RightChild = z;
   y->LeftChild = y->RightChild = z->LeftChild = z->RightChild = 0;
   cout << "Postorder sequence is ";
   PostOrder(x);
   Erase(x);
   cout << "The tree has been erased" << endl;
   cout << "Its postorder sequence is " << endl;
   PostOrder(x);
}
