// branch-and-bound board arrangement

#include <iostream.h>
#include "minheap.h"
#include "bdnode.h"
#include "make2db.h"
#include "xcept.h"
#include "dosmax.h"

int BBArrangeBoards(int **B, int n, int m,
                                    int* &bestx)
{// Least-cost branch and bound, m nets, n boards.
   MinHeap<BoardNode> H(1000);  // for live nodes
   // Initialize first E-node, total, and bestd.
   BoardNode E;
   E.x = new int [n+1];
   E.s = 0;   // partial permutation is E.x[1:s]
   E.cd = 0;  // density of E.x[1:s]
   E.now = new int [m+1];
   int *total = new int [m+1];
   // now[i] = number of boards in x[1:s] with net i
   // total[i] = number of boards with net i
   for (int i = 1; i <= m; i++) {
      total[i] = 0;
      E.now[i] = 0;
      }
   for (i = 1; i <= n; i++) {
      E.x[i] = i; // permutation is 12345...n
      for (int j = 1; j <= m; j++)
         total[j] += B[i][j]; // boards with net j
      }
   int bestd = m + 1;  // best density found so far
   bestx = 0;          // null pointer
   
   do {// expand E-node
      if (E.s == n - 1) {// one child only
         int ld = 0; // local density at last board
         for (int j = 1; j <= m; j++)
            ld += B[E.x[n]][j];
         if (ld < bestd) {// better permutation
            delete [] bestx;
            bestx = E.x;
            bestd = max(ld, E.cd);
            }
         else delete [] E.x;
         delete [] E.now;}

      else {// generate children of E-node
      for (int i = E.s + 1; i <= n; i++) {
         BoardNode N;
         N.now = new int [m+1];
         for (int j = 1; j <= m; j++)
            // acccount for nets in new board
            N.now[j] = E.now[j] + B[E.x[i]][j];
         int ld = 0; // local density at new board
         for (j = 1; j <= m; j++)
            if (N.now[j] > 0 && total[j] != N.now[j])
               ld++;
         N.cd = max(ld, E.cd);
         if (N.cd < bestd) {// may lead to better leaf
            N.x = new int [n+1];
            N.s = E.s + 1;
            for (int j = 1; j <= n; j++)
               N.x[j] = E.x[j];
            N.x[N.s] = E.x[i];
            N.x[i] = E.x[N.s];
            H.Insert(N);}
         else delete [] N.now;}

         delete [] E.x;} // done with E-node

      try {H.DeleteMin(E);} // next E-node
      catch (OutOfBounds) {return bestd;}  // no E-node
      } while (E.cd < bestd);
   
   // free all nodes in min heap
   do {delete [] E.x;
       delete [] E.now;
       try {H.DeleteMin(E);}
       catch (...) {break;}
      } while (true);

   return bestd;
}

void main(void)
{
   int i, j, n = 8, m = 5, *p;
   int **B;
   Make2DArray(B,n+1,m+1);
   cout << "Enter net matrix" << endl;
   for (i =1; i <= n; i++) 
      for (j = 1; j <= m; j++)
         cin >> B[i][j];

   cout << "Min density is ";
   cout << BBArrangeBoards(B, n, m, p) << endl;
   cout << "Optimal arrangement is" << endl;
   for (i = 1; i <= n; i++)
      cout << p[i] << ' ';
   cout << endl;
}
