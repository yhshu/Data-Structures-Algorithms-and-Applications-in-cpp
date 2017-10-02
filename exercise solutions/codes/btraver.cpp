
// binary tree traversal methods
// formula-based representation

#include <iostream.h>
#include "lqueue.h"
#include "xcept.h"



template <class T>
void Visit(T a[], int i)
{// Visit a[i], just output.
   cout << a[i] << ' ';
}


template <class T>
void InOrder(T a[], int last, int i)
{// Inorder traversal of binary tree with root a[i].
   if (i <= last && a[i]) {
      InOrder(a, last, 2*i);    // do left subtree
      Visit(a, i);              // visit tree root
      InOrder(a, last, 2*i+1);  // do right subtree
      }
}

template <class T>
void LevelOrder(T a[], int last)
{// Level-order traversal of a binary tree.
   LinkedQueue<int> Q;
   if (!last) return; // empty tree
   int i = 1; // start at root
   while (true) {
      Visit(a, i);  

      // put children on queue
      if (2*i <= last && a[2*i])
         Q.Add(2*i);       // add left child to queue
      if (2*i+1 <= last && a[2*i+1])
         Q.Add(2*i+1);  // add right child to queue

      // get next node to visit
      try {Q.Delete(i);}
      catch (OutOfBounds) {return;}
      }
}


void main(void)
{
   // create a binary tree
   int *tree = new int [20];
   int last = 13;
   tree[1] = 1; tree[2] = 2; tree[3] = 3;
   tree[4] = 0;
   tree[5] = 4; tree[6] = 5; tree[7] = 6;
   tree[8] = tree[9] = tree[10] = tree[11] = 0;
   tree[12] = 0;
   tree[13] = 7;
  
   cout << "Inorder sequence is ";
   InOrder(tree, last, 1);
   cout << endl;
   cout << "Level order sequence is ";
   LevelOrder(tree, last);
   cout << endl;

}
