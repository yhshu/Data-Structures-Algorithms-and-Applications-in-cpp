
// greedy 0/1 knapsack solution

#include <iostream.h>
#include "hsort.h"
#include "object2.h"

template<class Tw, class Tp>
float Knapsack(Tp p[], Tw w[], Tw c, int n, int x[])
{// Return value of greedy knapsack filling. 
 // Set x[i] = 1 iff object i included in knapsack,
 // 1 <= i <= n.
   float P = 0;  // will be sum of profits

   // define an object array to be sorted by
   // profit density
   Object *Q = new Object [n+1];

   for (int i = 1; i <= n; i++) {
      // array of profit densities
      Q[i].ID = i;
      Q[i].d = 1.0*p[i]/w[i];
      }

   // sort by density
   HeapSort(Q,n);

   // load in nonincreasing order of density
   for (i = n; i > 0; i--) {
      int id = Q[i].ID;
      if (w[id] <= c ) {// object id fits
         x[id] = 1;
         c -= w[id];
         P += p[id];
         }
      else // object id does not fit
         x[id] = 0;
      }

   delete [] Q;
   return P;
}

void main(void)
{
   int p[6] = {0, 6, 3, 5, 4, 6};
   int w[6] = {0, 2, 2, 6, 5, 4};
   int x[6];
   int n = 5;
   int c = 10;
   cout << "Optimal value is" << endl;
   cout << Knapsack(p,w,c,n,x) << endl;
   cout << "x vector is" << endl;
   for (int i = 1; i <= 5; i++)
      cout << x[i] << "  ";
   cout << endl;
}
