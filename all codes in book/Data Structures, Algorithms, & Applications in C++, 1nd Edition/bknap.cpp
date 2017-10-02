// backtracking knapsack solution

#include <iostream.h>
#include "msort.h"
#include "object.h"

template<class Tw, class Tp>
class Knap {
   friend Tp Knapsack(Tp *, Tw *, Tw, int);
   private:
      Tp Bound(int i);
      void Knapsack(int i);
      Tw c;      // knapsack capacity
      int n;     // number of objects
      Tw *w;     // array of object weights
      Tp *p;     // array of object profits
      Tw cw;     // weight of current packing
      Tp cp;     // profit of current packing
      Tp bestp;  // max profit so far
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
   
template<class Tw, class Tp>
void Knap<Tw, Tp>::Knapsack(int i)
{// Search from level i node.
   if (i > n) {// at a leaf
      bestp = cp;
      return;}
   // check subtrees
   if (cw + w[i] <= c) {// try x[i] = 1
      cw += w[i];
      cp += p[i];
      Knapsack(i+1);
      cw -= w[i];
      cp -= p[i];}
   if (Bound(i+1) > bestp) // try x[i] = 0
      Knapsack(i+1);
}


template<class Tw, class Tp>
Tp Knapsack(Tp p[], Tw w[], Tw c, int n)
{// Return value of best knapsack filling. 
   // initialize for Knap::Knapsack
   Tw W = 0;  // will be sum of weights
   Tp P = 0;  // will be sum of profits
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
   Knap<Tw, Tp> K;
   K.p = new Tp [n+1];
   K.w = new Tw [n+1];
   for (i = 1; i <= n; i++) {
      // Ps and Ws in density order
      K.p[i] = p[Q[i-1].ID];
      K.w[i] = w[Q[i-1].ID];
      }
   K.cp = 0;
   K.cw = 0;
   K.c = c;
   K.n = n;
   K.bestp = 0;

   // find best profit
   K.Knapsack(1);

   delete [] Q;
   delete [] K.w;
   delete [] K.p;
   return K.bestp;
}

void main(void)
{
   int p[6] = {0, 6, 3, 5, 4, 6};
   int w[6] = {0, 2, 2, 6, 5, 4};
   int n = 5;
   int c = 10;
   cout << "Optimal value is" << endl;
   cout << Knapsack(p,w,c,n) << endl;
}
