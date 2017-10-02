// binary tree traversal methods

#include <iostream.h>
#include "lqueue.h"
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
   if (t) {
      Visit(t);                 // visit tree root
      PreOrder(t->LeftChild);   // do left subtree
      PreOrder(t->RightChild);  // do right subtree
      }
}

template <class T>
void InOrder(BinaryTreeNode<T> *t)
{// Inorder traversal of *t.
   if (t) {
      InOrder(t->LeftChild);   // do left subtree
      Visit(t);                // visit tree root
      InOrder(t->RightChild);  // do right subtree
      }
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
void LevelOrder(BinaryTreeNode<T> *t)
{// Level-order traversal of *t.
   LinkedQueue<BinaryTreeNode<T>*> Q;
   while (t) {
      Visit(t);  // visit t

      // put t's children on queue
      if (t->LeftChild) Q.Add(t->LeftChild);
      if (t->RightChild) Q.Add(t->RightChild);

      // get next node to visit
      try {Q.Delete(t);}
      catch (OutOfBounds) {return;}
      }
 }

void main(void)
{
   // create a binary tree with root x
   BinaryTreeNode<int> x, y, z;
   x.data = 1;
   y.data = 2;
   z.data = 3;
   x.LeftChild = &y;
   x.RightChild = &z;
   y.LeftChild = y.RightChild = z.LeftChild = z.RightChild = 0;

   // traverse x in all ways
   cout << "Inorder sequence is ";
   InOrder(&x);
   cout << endl;
   cout << "Preorder sequence is ";
   PreOrder(&x);
   cout << endl;
   cout << "Postorder sequence is ";
   PostOrder(&x);
   cout << endl;
   cout << "Level order sequence is ";
   LevelOrder(&x);
   cout << endl;
}
