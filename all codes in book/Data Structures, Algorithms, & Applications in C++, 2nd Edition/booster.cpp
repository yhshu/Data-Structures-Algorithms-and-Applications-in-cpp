// place signal boosters

#include <iostream>
#include "booster.h"
#include "linkedBinaryTree.h"

using namespace std;

int tolerance = 3;

void placeBoosters(binaryTreeNode<booster> *x)
{// Compute degradation at *x. Place booster
 // here if degradation exceeds tolerance.

   x->element.degradeToLeaf = 0;  // initialize degradation at x
  
   // compute degradation from left subtree of x and
   // place a booster at the left child of x if needed
   binaryTreeNode<booster> *y = x->leftChild;
   if (y != NULL)
   {// x has a nonempty left subtree
       int degradation = y->element.degradeToLeaf + 
                         y->element.degradeFromParent;
       if (degradation > tolerance)
       {// place a booster at y
          y->element.boosterHere = true;  
          x->element.degradeToLeaf = y->element.degradeFromParent;
       }
       else  // no booster needed at y
          x->element.degradeToLeaf = degradation;
   }

   // compute degradation from right subtree of x and
   // place a booster at the right child of x if needed
   y = x->rightChild;
   if (y != NULL)
   {// x has a nonempty right subtree
      int degradation = y->element.degradeToLeaf +
                        y->element.degradeFromParent;
      if (degradation > tolerance)
      {// place booster at y
         y->element.boosterHere = true;
         degradation = y->element.degradeFromParent;
      }
      if (x->element.degradeToLeaf < degradation)
         x->element.degradeToLeaf = degradation;
   } 
}

int main(void)
{
   booster a, b;
   a.degradeFromParent = 2;
   a.degradeToLeaf =0;
   a.boosterHere = 0;
   b.degradeFromParent=1;
   b.degradeToLeaf=0;
   b.boosterHere = 0;

   linkedBinaryTree<booster> t, u, v, w, x, y;
   u.makeTree(a,x,x);
   v.makeTree(b,u,x);
   u.makeTree(a,x,x);
   w.makeTree(a,u,x);

   b.degradeFromParent=3;
   u.makeTree(b,v,w);
   v.makeTree(a,x,x);

   b.degradeFromParent=3;
   w.makeTree(b,x,x);
   y.makeTree(a,v,w);
   w.makeTree(a,x,x);
   t.makeTree(b,y,w);

   b.degradeFromParent=0;
   v.makeTree(b,t,u);

   v.postOrder(placeBoosters);
   v.postOrderOutput();

   return 0;
}
