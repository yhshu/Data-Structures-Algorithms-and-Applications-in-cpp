
// functions to delete/erase and copy a binary tree

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
void Erase(BinaryTreeNode<T> * &t)
{// Postorder deletion of *t.
   if (t) {
      Erase(t->LeftChild);   // delete left subtree
      Erase(t->RightChild);  // delete right subtree
      delete t;               // delete root
      t = 0;
      }
}

template <class T>
BinaryTreeNode<T>* PostCopy(BinaryTreeNode<T> *t)
{// Copy the subtree t using a postorder traversal.
 // Return a pointer to the root of the new tree.
   if (!t) // t is empty
      return 0;

   // first make copies of left and right subtrees
   BinaryTreeNode<T> *left, *right, *root;
    left = PostCopy(t->LeftChild);
   try {right = PostCopy(t->RightChild);}
   catch (...) {
      // copy failed, free nodes in left subtree
      Erase(left);
      throw;}  // rethrow exception

   // successful copy of left and right subtrees
   // copy root
   try {root = new BinaryTreeNode<T>
                   (t->data, left, right);}
   catch (...) {
      // failed to get a node for root
      // free nodes in left and right subtrees
      Erase(left);
      Erase(right);
      throw;}

   return root;
}

template <class T>
BinaryTreeNode<T>* PreCopy(BinaryTreeNode<T> *t)
{// Copy the subtree t using a postorder traversal.
 // Return a pointer to the root of the new tree.
   if (!t) // t is empty
      return 0;

   // first make a copy of the root
   BinaryTreeNode<T> *root;
   root = new BinaryTreeNode<T> (t->data);
   
   // now make a copy of the left subtree
   try {root->LeftChild = PreCopy(t->LeftChild);}
   catch (...) {
      // copy failed, free root node
      delete root;
      throw;}  // rethrow exception

   // now make a copy of the right subtree
   try {root->RightChild = PreCopy(t->RightChild);}
   catch (...) {
      // copy failed, free nodes in left subtree
      // and the root
      Erase(root->LeftChild);
      delete root;
      throw;}  // rethrow exception

   return root;
}

void main(void)
{
   // construct a binary tree
   BinaryTreeNode<int> x, y, z;
   x.data = 1;
   y.data = 2;
   z.data = 3;
   x.LeftChild = &y;
   x.RightChild = &z;
   y.LeftChild = y.RightChild = z.LeftChild = z.RightChild = 0;
   cout << "Inorder sequence is ";
   InOrder(&x);
   cout << endl;
   cout << "Preorder sequence is ";
   PreOrder(&x);
   cout << endl;

   BinaryTreeNode<int> *u, *v;
   // make a copy and output
   u = PostCopy(&x);
   cout << "Copied the tree using a postorder copy function"
        << endl;
   cout << "Inorder sequence is ";
   InOrder(u);
   cout << endl;
   cout << "Preorder sequence is ";
   PreOrder(u);
   cout << endl;

   // make another copy and output
   v = PreCopy(u);
   cout << "Copied the tree using a preorder copy function"
        << endl;
   cout << "Inorder sequence is ";
   InOrder(v);
   cout << endl;
   cout << "Preorder sequence is ";
   PreOrder(v);
   cout << endl;
}
