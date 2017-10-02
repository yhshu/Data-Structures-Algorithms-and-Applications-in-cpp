// FIFO branch-and-bound loading
// improved version, finds best value only

#include<iostream.h>
#include "lqueue.h"

template<class T>
T MaxLoading(T w[], T c, int n)
{// Return value of best loading.
 // Use FIFO branch and bound.
   // initialize for level 1 start
   LinkedQueue<T> Q;  // live-node queue
   Q.Add(-1);         // end-of-level marker
   int i = 1;         // level of E-node
   T Ew = 0,          // weight of E-node
     bestw = 0,       // best weight so far
     r = 0;           // remaining weight at E-node
   for (int j = 2; j <= n; j++)
      r += w[i];

   // search subset space tree
   while (true) {
      // check left child of E-node
      T wt = Ew + w[i];  // weight of left child
      if (wt <= c) {     // feasible left child
         if (wt > bestw) bestw = wt;
         // add to queue unless leaf
         if (i < n) Q.Add(wt);}

      // check right child
      if (Ew + r > bestw && i < n)
          Q.Add(Ew);   // may have a better leaf

      Q.Delete(Ew);     // get next E-node
      if (Ew == -1) {   // end of level
          if (Q.IsEmpty()) return bestw;
          Q.Add(-1);     // end-of-level marker
          Q.Delete(Ew);  // get next E-node
          i++;           // level of E-node
          r -= w[i];}    // remaining weight at E-node
      }
}

void main(void)
{
   int w[6] = {0, 2, 2, 6, 5, 5};
   int n = 5;
   int c = 16;
   cout << "Max loading is " << MaxLoading(w,c,n) << endl;
}
