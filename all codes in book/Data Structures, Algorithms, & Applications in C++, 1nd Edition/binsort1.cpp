// bin sort

#include <iostream.h>
#include "binnode2.h"
#include "chain.h"
#include "xcept.h"

void BinSort(Chain<Node>& X, int range)
{// Sort by score.
   int len = X.Length();
   Node x;
   Chain<Node> *bin;
   bin = new Chain<Node> [range + 1];

   // distribute to bins
   for (int i = 1; i <= len; i++) {
      X.Delete(1,x);
      bin[x.score].Insert(0,x);
      }

   // collect from bins
   for (int j = range; j >= 0; j--)
      while (!bin[j].IsEmpty()) {
         bin[j].Delete(1,x);
         X.Insert(0,x);
         }

   delete [] bin;
}

void main(void)
{
   Node x;
   Chain<Node> L;
   for(int i = 1; i <= 20; i++) {
   x.score = i/2;
   L.Insert(0,x); }
   BinSort(L,10);
   cout << L << endl;
}
