// binary tree traversal methods

#include <iostream>
#include "arrayQueue.h"
#include "binaryTreeNode.h"
#include "myExceptions.h"

using namespace std;

template <class T>
void visit(binaryTreeNode<T> *x)
{// visit node *x, just output element field.
   cout << x->element << ' ';
}

template <class T>
void preOrder(binaryTreeNode<T> *t)
{// Preorder traversal of *t.
   if (t != NULL)
   {
      visit(t);                 // visit tree root
      preOrder(t->leftChild);   // do left subtree
      preOrder(t->rightChild);  // do right subtree
   }
}

template <class T>
void inOrder(binaryTreeNode<T> *t)
{// Inorder traversal of *t.
   if (t != NULL)
   {
      inOrder(t->leftChild);   // do left subtree
      visit(t);                // visit tree root
      inOrder(t->rightChild);  // do right subtree
   }
}

template <class T>
void postOrder(binaryTreeNode<T> *t)
{// Postorder traversal of *t.
   if (t != NULL)
   {
      postOrder(t->leftChild);   // do left subtree
      postOrder(t->rightChild);  // do right subtree
      visit(t);                  // visit tree root
   }
}

template <class T>
void levelOrder(binaryTreeNode<T> *t)
{// Level-order traversal of *t.
   arrayQueue<binaryTreeNode<T>*> q;
   while (t != NULL)
   {
      visit(t);  // visit t

      // put t's children on queue
      if (t->leftChild != NULL)
         q.push(t->leftChild);
      if (t->rightChild != NULL)
         q.push(t->rightChild);

      // get next node to visit
      try {t = q.front();}
      catch (queueEmpty) {return;}
      q.pop();
   }
}

int main(void)
{
   // create a binary tree with root x
   binaryTreeNode<int> *x, *y, *z;
   y = new binaryTreeNode<int> (2);
   z = new binaryTreeNode<int> (3);
   x = new binaryTreeNode<int> (1, y, z);

   // traverse x in all ways
   cout << "Inorder sequence is ";
   inOrder(x);
   cout << endl;
   cout << "Preorder sequence is ";
   preOrder(x);
   cout << endl;
   cout << "Postorder sequence is ";
   postOrder(x);
   cout << endl;
   cout << "Level order sequence is ";
   levelOrder(x);
   cout << endl;

   return 0;
}
