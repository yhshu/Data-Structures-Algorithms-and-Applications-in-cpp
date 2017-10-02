// place signal boosters in a tree represented
// as a binary tree

#include <iostream.h>
#include "tbooster.h"
#include "booster.h"


void main(void)
{// construct tree of Figure 8.14(b)
   TreeBooster T, U, V, W, X, Y;
   Booster a, b;
   a.d = 2; a.D = 0; a.boost = 0;
   b.d = 3; b.D = 0; b.boost = 0;
   U.MakeTree(a,X,X);
   Y.MakeTree(b,X,U);
   W.MakeTree(b,X,X);
   V.MakeTree(a,X,W);
   W.MakeTree(a,X,V);
   T.MakeTree(a,X,X);
   V.MakeTree(b,W,T);
   T.MakeTree(b,X,V);
   U.MakeTree(a,Y,T);
   b.d = 0;
   V.MakeTree(b,U,X);
   V.PlaceBoosters(3);
   V.PostOutput();
}
