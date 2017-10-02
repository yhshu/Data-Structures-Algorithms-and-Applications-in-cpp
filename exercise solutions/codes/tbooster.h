// booster plavement function for tree distribution
// networks represented as binary trees

#ifndef TreeBooster_
#define TreeBooster_

#include <iostream.h>
#include "dbinary.h"
#include "xcept.h"
#include "booster.h"
#include "dosmax.h"

class TreeBooster : public BinaryTree<Booster> {
   public:
      void PlaceBoosters(int tol)
           {tolerance = tol;
            PlaceBoosters(root);}
   private:
      int PlaceBoosters(BinaryTreeNode<Booster> *);
      int tolerance;
};


int TreeBooster::PlaceBoosters
                 (BinaryTreeNode<Booster> *t)
{// Place boosters in the subtree with root t.
 // Return max of delays from parent of t to nearest
 // booster or leaf in each right sibling
 // subtree of parent in
 // original distribution tree.
   if (!t) return 0;  // t is empty, parent is
                      // a leaf
   t->data.D = PlaceBoosters(t->LeftChild);
   // compute max delay from parent of t
   // to nearest booster or leaf in each
   // subtree of t in original distribution tree
   int del = t->data.D + t->data.d;

   // see if we need a booster at t
   if (del > tolerance) {
      t->data.boost = true;
      del = t->data.d;}

   // compute max delay for remaining
   // children of parent of t in original
   // distribution tree; the max of this value
   // and del is the delay value for parent of t
   return max(del, PlaceBoosters(t->RightChild));
   
}

#endif
