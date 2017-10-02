// generate infix from expression tree

#include <iostream>
#include "binaryTreeNode.h"

using namespace std;

template <class T>
void infix(binaryTreeNode<T> *t)
{// Output infix form of expression.
   if (t != NULL)
   {
      cout << '(';
      infix(t->leftChild);   // left operand
      cout << t->element;    // operator
      infix(t->rightChild);  // right operand
      cout << ')';
   }
}

int main(void)
{
   binaryTreeNode<int> x,y,z;
   x.element = 1; y.element = 2; z.element = 3;
   x.leftChild = &y; x.rightChild = &z;
   y.leftChild = y.rightChild = z.leftChild = z.rightChild = 0;
   infix(&x);
   cout << endl;
}
