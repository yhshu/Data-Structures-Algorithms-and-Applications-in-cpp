// branch-and-bound knapsack

// AddLiveNode and Knapsack give compiler errors
// (unable to resolve function overload or ambiguous
// call to overloaded function) when they
// are template functions.  They have been changed to
// integer functions.

#include "maxheap.h"
#include "msort.h"
#include "object2.h"
#include "bbnode2.h"
#include <iostream.h>

template<class Tw, class Tp>
class Knap {
   friend Tp Knapsack(Tp *, Tw *, Tw, int, int *);
   public:
      Tp MaxProfitKnapsack();
   private:
      MaxHeap<HeapNode<Tp, Tw> > *H;
      Tp Bound(int i);
      void AddLiveNode(Tp up, Tp cp, Tw cw,
                                bool ch, int level);
      bbnode *E;   // pointer to E-node
      Tw c;        // knapsack capacity
      int n;       // number of objects
      Tw *w;       // array of object weights
      Tp *p;       // array of object profits
      Tw cw;       // weight of current packing
      Tp cp;       // profit of current packing
      int *bestx;  // best packing
};

template<class Tw, class Tp>
Tp Knap<Tw, Tp>::Bound(int i)
{// Return upper bound on value of
 // best leaf in subtree.
   Tw cleft = c - cw;  // remaining capacity
   Tp b = cp;          // profit bound
   // fill remaining capacity
   // in order of profit density
   while (i <= n && w[i] <= cleft) {
      cleft -= w[i];
      b += p[i];
      i++;
      }

   // take fraction of next object
   if (i <= n) b += p[i]/w[i] * cleft;
   return b;
}
   
// template<class Tp, class Tw>
// void Knap<Tp, Tw>::AddLiveNode(Tp up,
//               Tp cp, Tw cw, bool ch, int lev)
void Knap<int, int>::AddLiveNode(int up,
              int cp, int cw, bool ch, int lev)
{// Add live node to max heap H.
   bbnode *b = new bbnode;
   b->parent = E;
   b->LChild = ch;
   HeapNode<Tp, Tw> N;
   N.uprofit = up;
   N.profit = cp;
   N.weight = cw;
   N.level = lev;
   N.ptr = b;
   H->Insert(N);
}

template<class Tw, class Tp>
Tp Knap<Tw, Tp>::MaxProfitKnapsack()
{// Return profit of best knapsack filling.
 // Set bestx[i] = 1 iff object i is in knapsack in
 // best filling.  Use max-profit branch and bound.
   // define a max heap for up to
   // 1000 live nodes
   H = new MaxHeap<HeapNode<Tp, Tw> > (1000);

   // allocate space for bestx
   bestx = new int [n+1];

   // initialize for level 1 start
   int i = 1;
   E = 0;
   cw = cp = 0;
   Tp bestp = 0;      // best profit so far
   Tp up = Bound(1);  // maximum possible profit
                      // in subtree with root E

   // search subset space tree
   while (i != n+1) {// not at leaf
      // check left child
      Tw wt = cw + w[i];
      if (wt <= c) {// feasible left child
         if (cp+p[i] > bestp) bestp = cp+p[i];
         AddLiveNode(up, cp+p[i], cw+w[i], true, i+1);}
         up = Bound(i+1);

      // check right child
      if (up >= bestp) // right child has prospects
           AddLiveNode(up, cp, cw, false, i+1);

      // get next E-node
      HeapNode<Tp, Tw> N;
      H->DeleteMax(N); // cannot be empty
      E = N.ptr;
      cw = N.weight;
      cp = N.profit;
      up = N.uprofit;
      i = N.level;
      }

   // construct bestx[] by following path
   // from E-node E to the root
   for (int j = n; j > 0; j--) {
      bestx[j] = E->LChild;
      E = E->parent;
      }

   return cp;
}

// template<class Tw, class Tp>
// Tp Knapsack(Tp p[], Tw w[], Tw c,
//                int n, int bestx[])
int Knapsack(int p[], int w[], int c,
                int n, int bestx[])
{// Return value of best knapsack filling. 
 // Return object selection in bestx.
   // initialize for Knap::Knapsack
   int W = 0;  // will be sum of weights
   int P = 0;  // will be sum of profits
   // define an object array to be sorted by
   // profit density
   Object *Q = new Object [n];

   for (int i = 1; i <= n; i++) {
      // array of profit densities
      Q[i-1].ID = i;
      Q[i-1].d = 1.0*p[i]/w[i];
      P += p[i];
      W += w[i];
      }

   if (W <= c) return P;  // all objects fit

   // sort by density
   MergeSort(Q,n);

   // create member of Knap
   Knap<int, int> K;
   K.p = new int [n+1];
   K.w = new int [n+1];
   for (i = 1; i <= n; i++) {
      // Ps and Ws in density order
      K.p[i] = p[Q[i-1].ID];
      K.w[i] = w[Q[i-1].ID];
      }
   K.cp = 0;
   K.cw = 0;
   K.c = c;
   K.n = n;

   // find best profit and construct packing
   int bestp = K.MaxProfitKnapsack();
   for (int j =1 ; j <= n; j++)
      bestx[Q[j-1].ID] = K.bestx[j];

   delete [] Q;
   delete [] K.w;
   delete [] K.p;
   delete [] K.bestx;
   return bestp;
}

void main(void)
{
   int p[6] = {0, 6, 3, 5, 4, 6};
   int w[6] = {0, 2, 2, 6, 5, 4};
   int bestx[6];
   int n = 5;
   int c = 10;
   cout << "Optimal profit is " << Knapsack(p,w,c,n,bestx) << endl;
   cout << "Packing vector is" << endl;
   for (int i=1; i <= n; i++)
      cout << bestx[i] << ' ';
   cout << endl;
}
