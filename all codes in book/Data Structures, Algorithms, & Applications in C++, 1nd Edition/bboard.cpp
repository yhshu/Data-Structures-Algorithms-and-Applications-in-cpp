// backtracking board arrangement

#include <iostream.h>
#include "swap.h"
#include "make2db.h"

class Board {
   friend ArrangeBoards(int**, int, int, int []);
   private:
      void BestOrder(int i, int cd);
      int *x,      // path to current node
          *bestx,  // best arrangement found so far
          *total,  // total[j] = number of boards
                   // with net j
          *now,    // now[j] = number of boards in
                   // partial arrangement with net j
          bestd,   // density of bestx
          n,       // number of boards
          m,       // number of nets
          **B;     // 2D board array
};

void Board::BestOrder(int i, int cd)
{// Backtracking search of permutation tree.
   if (i == n) {// all boards placed
      for (int j = 1; j <= n; j++)
         bestx[j] = x[j];
      bestd = cd;}
   else // try out subtrees
      for (int j = i; j <= n; j++) {
         // try child with board x[j] as next one

         // update now & compute density at last slot
         int ld = 0;
         for (int k = 1; k <= m; k++) {
            now[k] += B[x[j]][k];
            if (now[k] > 0 && total[k] != now[k])
               ld++;
            }

         // update ld to be overall density of
         // partial arrangement
         if (cd > ld) ld = cd;

         // search subtree only if it may
         // contain a better arrangement
         if (ld < bestd) {// move to child
            Swap(x[i], x[j]);
            BestOrder(i+1, ld);
            Swap(x[i], x[j]);}

         // reset now
         for (k = 1; k <= m; k++)
            now[k] -= B[x[j]][k];
         }
}

int ArrangeBoards(int **B, int n, int m, int bestx[])
{// Return best density.
 // Return best arrangement in bestx.
   Board X;
   // initialize X
   X.x = new int [n+1];
   X.total = new int [m+1];
   X.now = new int [m+1];
   X.B = B;
   X.n = n;
   X.m = m;
   X.bestx = bestx;
   X.bestd = m + 1;

   // initialize total and now
   for (int i = 1; i <= m; i++) {
      X.total[i] = 0;
      X.now[i] = 0;
      }

   // initialize x to identity permutation
   // and compute total
   for (i = 1; i <= n; i++) {
      X.x[i] = i;
      for (int j = 1; j <= m; j++)
         X.total[j] += B[i][j];
      }

   // find best arrangement
   X.BestOrder(1,0);

   delete [] X.x;
   delete [] X.total;
   delete [] X.now;
   return X.bestd;
}

void main(void)
{
   int n = 8, m = 5, p[9];
   int **B;
   Make2DArray(B,n+1,m+1);
   
   cout << "Enter 8 x 5 net matrix" << endl;
   for (int i =1; i <= n; i++) 
      for (int j = 1; j <= m; j++)
         cin >> B[i][j];

   cout << "Minimum density is ";
   cout << ArrangeBoards(B, n, m, p) << endl;
   cout << "Optimal arrangement is" << endl;
   for (i = 1; i <= n; i++)
      cout << p[i] << ' ';
   cout << endl;
}
