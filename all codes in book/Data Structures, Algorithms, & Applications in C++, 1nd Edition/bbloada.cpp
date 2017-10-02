// FIFO branch-and-bound for two ship loading
// code finds weight of best loading for first ship only

#include <iostream.h>
#include "lqueue.h"

template<class T>
void AddLiveNode(LinkedQueue<T> &Q, T wt,
                    T& bestw, int i, int n)
{// Add node weight wt to queue Q if not leaf.
   if (i == n) {// feasible leaf
      if (wt > bestw) bestw = wt;}
   else Q.Add(wt); // not a leaf
}

template<class T>
T MaxLoading(T w[], T c, int n)
{// Return value of best loading.
 // Use FIFO branch and bound.
   // initialize for level 1 start
   LinkedQueue<T> Q;  // live-node queue
   Q.Add(-1);         // end-of-level marker
   int i = 1;         // level of E-node
   T Ew = 0,          // weight of E-node
     bestw = 0;       // best weight so far

   // search subset space tree
   while (true) {
      // check left child of E-node
      if (Ew + w[i] <= c) // x[i] = 1
         AddLiveNode(Q, Ew + w[i], bestw, i, n);

      // right child is always feasible
      AddLiveNode(Q, Ew, bestw, i, n); // x[i] = 0

      Q.Delete(Ew);     // get next E-node
      if (Ew == -1) {   // end of level
         if (Q.IsEmpty()) return bestw;
         Q.Add(-1);     // end-of-level marker
         Q.Delete(Ew);  // get next E-node
         i++;}          // level number of Ew
      }
}

void main(void)
{
   int w[6] = {0, 2, 2, 6, 5, 5};
   int n = 5;
   int c = 16;
   cout << "Max loading is " << MaxLoading(w,c,n) << endl;
}
