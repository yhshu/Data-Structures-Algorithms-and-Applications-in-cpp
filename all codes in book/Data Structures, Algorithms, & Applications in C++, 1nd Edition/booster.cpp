// place signal boosters

#include <iostream.h>
#include "booster.h"
#include "abinary.h"

BinaryTree<Booster> T, U, V, W, X, Y;
int tolerance = 3;

void PlaceBoosters(BinaryTreeNode<Booster> *x)
{// Compute degradation at *x.  Place booster
 // here if degradation exceeds tolerance.
   BinaryTreeNode<Booster> *y = x->LeftChild;
   int degradation;
   x->data.D = 0;  // initialize degradation at x
   if (y) {// compute from left child
           degradation = y->data.D + y->data.d;
           if (degradation > tolerance)
              {y->data.boost = true;
               x->data.D = y->data.d;}
           else x->data.D = degradation;
          }
   y = x->RightChild;
   if (y) {// compute from right child
           degradation = y->data.D + y->data.d;
           if (degradation > tolerance)
              {y->data.boost = true;
               degradation = y->data.d;}
           if (x->data.D < degradation)
              x->data.D = degradation;
          }
}

void main(void)
{
   Booster a, b;
   a.d = 2; a.D =0; a.boost = 0;
   b.d=1; b.D=0; b.boost = 0;
   U.MakeTree(a,X,X);
   V.MakeTree(b,U,X);
   U.MakeTree(a,X,X);
   W.MakeTree(a,U,X);
   b.d=3;
   U.MakeTree(b,V,W);
   V.MakeTree(a,X,X);
   b.d=3;
   W.MakeTree(b,X,X);
   Y.MakeTree(a,V,W);
   W.MakeTree(a,X,X);
   T.MakeTree(b,Y,W);
   b.d=0;
   V.MakeTree(b,T,U);
   V.PostOrder(PlaceBoosters);
   V.PostOutput();
}
