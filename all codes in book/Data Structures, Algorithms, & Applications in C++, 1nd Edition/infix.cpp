// generate infix from expression tree

#include <iostream.h>

template <class type>
class BinaryTreeNode {
   friend void Infix(BinaryTreeNode<type>*);
   friend void main(void);
   private:
      type data;
       BinaryTreeNode *LeftChild, *RightChild;
};


#include "infix.h"

void main(void)
{
   BinaryTreeNode<int> x,y,z;
   x.data = 1; y.data = 2; z.data = 3;
   x.LeftChild = &y; x.RightChild = &z;
   y.LeftChild = y.RightChild = z.LeftChild = z.RightChild = 0;
   Infix(&x);
   cout << endl;
}
