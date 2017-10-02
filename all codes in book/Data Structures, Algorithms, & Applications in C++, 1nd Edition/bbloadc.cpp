// FIFO branch-and-bound loading
// code to find best loading and its value

#include <iostream.h>
#include "lqueue.h"
#include "qnode.h"

template<class T>
void AddLiveNode(LinkedQueue<QNode<T>*> &Q, T wt,
     int i, int n, T bestw, QNode<T> *E,
     QNode<T> *&bestE, int bestx[], bool ch)
{// Add a level i weight wt live node to the
 // queue Q if not leaf.  New node is a child
 // of E.  ch is true iff new node is the left
 // child.  If feasible leaf set bestx[n] to ch.
   if (i == n) {// feasible leaf
      if (wt == bestw) {
         // best so far
         bestE = E;
         bestx[n] = ch;}
      return;}

   // not a leaf, add to queue
   QNode<T> *b;
   b = new QNode<T>;
   b->weight = wt;
   b->parent = E;
   b->LChild = ch;
   Q.Add(b);
}

template<class T>
T MaxLoading(T w[], T c, int n, int bestx[])
{// Return value of best loading.  Return best
 // loading in bestx.  Use FIFO branch and bound.
   // initialize for level 1 start
   LinkedQueue<QNode<T>*> Q;  // live-node queue
   Q.Add(0);          // 0 is end-of-level pointer
   int i = 1;         // level of E-node
   T Ew = 0,          // weight of E-node
     bestw = 0,       // best weight so far
     r = 0;           // remaining weight at E-node
   for (int j = 2; j <= n; j++)
      r += w[i];
   QNode<T> *E = 0,   // current E-node
            *bestE;   // best E-node so far

   // search subset space tree
   while (true) {
      // check left child of E-node
      T wt = Ew + w[i];
      if (wt <= c) {// feasible left child
         if (wt > bestw) bestw = wt;
         AddLiveNode(Q, wt, i, n, bestw, E, 
                            bestE, bestx, true);}

      // check right child
      if (Ew + r > bestw) AddLiveNode(Q, Ew, i, n,
                      bestw, E, bestE, bestx, false);

      Q.Delete(E);     // next E-node
      if (!E) {        // end of level
         if (Q.IsEmpty()) break;
         Q.Add(0);     // end-of-level pointer
         Q.Delete(E);  // next E-node
         i++;          // level of E-node
         r -= w[i];}   // remaining weight at E-node

      Ew = E->weight;  // weight of new E-node
      }

   // construct x[] by following path from
   // bestE to root, x[n] set by AddLiveNode
   for (j = n - 1; j > 0; j--) {
      bestx[j] = bestE->LChild;  // bool to int
      bestE = bestE->parent;
      }

   return bestw;
}

void main(void)
{
   int w[6] = {0, 2, 2, 6, 5, 5};
   int x[6];
   int n = 5;
   int c = 16;
   cout << "Max loading is " << MaxLoading(w,c,n,x) << endl;
   cout << "Loading vector is" << endl;
   for (int i = 1; i <= n; i++)
      cout << x[i] << ' ';
   cout << endl;
}
